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
                sh('bazel coverage //...')
                sh('genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat" --output-directory "bazel-out/_coverage_report" --branch-coverage --highlight --legend')
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'bazel-out/_coverage_report/**', fingerprint: true
        }
    }

}
