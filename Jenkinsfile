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
    }

}
