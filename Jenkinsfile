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
    stages {
        stage('Build') {
            steps {
                sh('bazel build //...')
            }
        }
        stage('Test') {
            steps {
                sh('bazel test //...')
            }
        }
        stage('Coverage') {
            steps {
                sh('./scripts/coverage_report.sh')
            }
        }
        stage('Documentation') {
            steps {
                sh('bazel build //:doxygen')
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'bazel-out/_coverage_report/**', fingerprint: true
            archiveArtifacts artifacts: 'bazel-bin/html/**', fingerprint: true
        }
        success {
            setBuildStatus("Build succeeded", "SUCCESS");
        }
        failure {
            setBuildStatus("Build failed", "FAILURE");
        }
    }
}
