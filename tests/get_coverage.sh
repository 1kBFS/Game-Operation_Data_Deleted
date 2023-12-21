#!/usr/bin/bash
PATH_TO_FILES="../../cmake-build-debug/CMakeFiles/Lab3.dir"
DIRECTORY_WITH_COVERAGE="coverage_info"
UTILIT_TO_VIEW="explorer.exe"
if [ -d $DIRECTORY_WITH_COVERAGE ]; then
  echo "Directory already exits, it will be rewrite"
  rm -r coverage_info
fi
mkdir coverage_info
cd coverage_info || exit 1
lcov -c -d $PATH_TO_FILES -o coverage.info
genhtml -o report coverage.info
cd report || exit 1
$UTILIT_TO_VIEW .