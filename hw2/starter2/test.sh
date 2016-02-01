#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Function to run the strings program against a test case and check
# its output and exit status for correct behavior
testStrings() {
  TEST_NO=$1
  ESTATUS=$2

  rm -f output.txt

  echo "Strings test $TEST_NO: ./strings < input_s$TEST_NO.txt > output.txt"
  ./strings < input_s$TEST_NO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Strings test $TEST_NO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  diff -q expected_s$TEST_NO.txt output.txt >/dev/null 2>&1
  if [ $? -ne 0 ]
  then
      echo "**** Strings test $TEST_NO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Strings test $TEST_NO PASS"
  return 0
}

# Function to run the venn program against a test case and check its
# output and exit status for correct behavior
testVenn() {
  TEST_NO=$1
  ESTATUS=$2

  # Name of the output file depends on whether this is an error test case.
  if [ $ESTATUS -eq 0 ]
  then
      EXPECTED="expected_v$TEST_NO.ppm"
      OUTPUT="output.ppm"
  else
      EXPECTED="expected_v$TEST_NO.txt"
      OUTPUT="output.txt"
  fi

  rm -f "$OUTPUT"

  echo "Venn test $TEST_NO: ./venn < input_v$TEST_NO.txt > $OUTPUT"
  ./venn < input_v$TEST_NO.txt > $OUTPUT
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Venn test $TEST_NO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  diff -q $EXPECTED $OUTPUT >/dev/null 2>&1
  if [ $? -ne 0 ]
  then
      echo "**** Venn test $TEST_NO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Venn test $TEST_NO PASS"
  return 0
}

# Test the strings program
testStrings 1 0
testStrings 2 0
testStrings 3 0
testStrings 4 0
testStrings 5 0
testStrings 6 100

# Test the venn program.
testVenn 1 0
testVenn 2 0
testVenn 3 0
testVenn 4 100
testVenn 5 100

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  exit 0
fi
