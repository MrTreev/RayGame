#!/bin/sh
set -eu

bazel coverage -s --local_test_jobs=1 --nocache_test_results //...
# shellcheck disable=SC2086 # splitting is intentional
genhtml \
    --function-coverage \
    --branch-coverage \
    --mcdc-coverage \
    --demangle-cpp \
    --legend \
    --show-details \
    "$(bazel info output_path)/_coverage/_coverage_report.dat" \
    --output-directory "bazel-out/_coverage_report"
