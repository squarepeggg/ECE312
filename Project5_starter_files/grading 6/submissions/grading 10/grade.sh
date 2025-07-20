#!/bin/bash

LIB_DIR="helper_files"
. "$LIB_DIR"/library.sh
. "$LIB_DIR"/zipfile_diffable_grader.sh

declare -a SAMPLE_TEST_CASES=('Test_Provided_1' 'Test_Provided_2' 'Test_Provided_3');
declare -a wanted_file_types=("*.cpp" "*.h" "*.hpp" "Makefile")
overriding_files="Makefile main.cpp"

test_timeout_seconds=3

main "$@"
