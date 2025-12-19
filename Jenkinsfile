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
        choice(name: 'SOURCE_LOCATION', choices: ['FULL', 'BASE', 'NONE'], description: 'Source location level in logs')
        booleanParam(name: 'TIME_FRAMES', defaultValue: false, description: 'Add frame times to logs')
        booleanParam(name: 'MATH_RANDOM_FULL', defaultValue: false, description: 'Use non-deterministic randomness')
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
                        -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \\
                        -DRAYGAME_ENABLE_COMPILE_COMMANDS=OFF \\
                        -DRAYGAME_BUILD_TESTS=ON \\
                        -DRAYGAME_BUILD_DOCS=ON \\
                        -DRAYGAME_BUILD_GAMES=ON \\
                        -DRAYGAME_LOG_LEVEL=${LOG_LEVEL} \\
                        -DRAYGAME_SOURCE_LOCATION=${SOURCE_LOCATION} \\
                        -DRAYGAME_MATH_RANDOM_FULL=${MATH_RANDOM_FULL ? 'ON' : 'OFF'} \\
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
