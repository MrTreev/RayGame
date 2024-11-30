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
                sh('bazel coverage -s --local_test_jobs=1 --nocache_test_results //...')
                sh('genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat" --output-directory "bazel-out/_coverage_report" --branch-coverage --function-coverage --legend')
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'bazel-out/_coverage_report/**', fingerprint: true
        }
    }

}
