#!/bin/bash

LIB_DIR="helper_files"
#LIB_DIR="helper_files"

. "$LIB_DIR"/library.sh
. "$LIB_DIR"/gtest_running_utilities.sh

CPP_FILE_NAME="Project6.cpp"
test_timeout_seconds=15

main "$@"
