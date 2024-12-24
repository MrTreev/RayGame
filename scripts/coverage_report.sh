#!/bin/sh
set -eu

bazel coverage -s --local_test_jobs=1 --nocache_test_results //...
genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat" --output-directory "bazel-out/_coverage_report" --function-coverage --legend
