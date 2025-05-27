void setBuildStatus(String message, String state) {
  step([
      $class: "GitHubCommitStatusSetter",
      reposSource: [$class: "ManuallyEnteredRepositorySource", url: "https://github.com/MrTreev/RayGame"],
      contextSource: [$class: "ManuallyEnteredCommitContextSource", context: "ci/jenkins/build-status"],
      errorHandlers: [[$class: "ChangingBuildStatusErrorHandler", result: "UNSTABLE"]],
      statusResultSource: [ $class: "ConditionalStatusResultSource", results: [[$class: "AnyBuildResult", message: message, state: state]] ]
  ]);
}

pipeline {
    agent any
    parameters {
        string(name: 'TOOLCHAIN', defaultValue: 'linux-clang-libcxx', description: 'CMake toolchain to use')
        choice(name: 'BUILD_TYPE', choices: ['Debug', 'Release', 'RelWithDebInfo', 'MinSizeRel'], description: 'Build type')
        choice(name: 'LOG_LEVEL', choices: ['TRACE', 'DEBUG', 'INFO', 'NOTE', 'PROGRESS', 'WARNING', 'ERROR', 'FATAL'], description: 'Logging Level')
        booleanParam(name: 'TIME_FRAMES', defaultValue: false, description: 'Add frame times to logs')
        booleanParam(name: 'MATH_RANDOM_FULL', defaultValue: false, description: 'Use non-deterministic randomness')
        booleanParam(name: 'MATH_FORCE_GENERIC', defaultValue: false, description: 'Force generic implementations of mathematics')
        booleanParam(name: 'DISABLE_SOURCE_LOCATION', defaultValue: false, description: 'Disable source location in logs')
    }
    stages {
        stage('Configure') {
            steps {
                sh("""
                    cmake \\
                        -S . \\
                        -B build \\
                        -G Ninja \\
                        --toolchain cmake/presets/${TOOLCHAIN}.cmake \\
                        -DRAYGAME_ENABLE_COMPILE_COMMANDS=OFF \\
                        -DRAYGAME_BUILD_TESTS=ON \\
                        -DRAYGAME_BUILD_DOCS=ON \\
                        -DRAYGAME_BUILD_GAMES=ON \\
                        -DRAYGAME_MATH_RANDOM_FULL=${MATH_RANDOM_FULL ? 'ON' : 'OFF'} \\
                        -DRAYGAME_MATH_FORCE_GENERIC=${MATH_FORCE_GENERIC ? 'ON' : 'OFF'} \\
                        -DRAYGAME_LOG_DISABLE_SOURCE_LOCATION=${DISABLE_SOURCE_LOCATION ? 'ON' : 'OFF'} \\
                        -DRAYGAME_TIME_FRAMES=${TIME_FRAMES ? 'ON' : 'OFF'} \\
                        ;
                """)
            }
        }
        stage('Build') {
            steps {
                sh('cmake --build build')
            }
        }
        stage('Test') {
            steps {
                sh('ctest --test-dir build')
            }
        }
    }
    post {
        success {
            setBuildStatus("Build succeeded", "SUCCESS");
        }
        failure {
            setBuildStatus("Build failed", "FAILURE");
        }
    }
}
