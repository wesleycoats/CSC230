#!/bin/bash
FAIL=0

# make a fresh copy of the target programs
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  FAIL=1
fi

# Function to run wordsearch program with no command line arguments
testWordsearchNoArg() {
  TEST_NO=$1
  ESTATUS=$2

  rm -f output.txt

  echo "Wordsearch test $TEST_NO: ./wordsearch > output.txt"
  ./wordsearch > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Wordsearch test $TEST_NO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  diff -q expected_$TEST_NO.txt output.txt >/dev/null 2>&1
  if [ $? -ne 0 ]
  then
      echo "**** Wordsearch test $TEST_NO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Wordsearch test $TEST_NO PASS"
  return 0
}


# Function to run the wordsearch program against a test case and check
# its output and exit status for correct behavior
testWordsearch() {
  TEST_NO=$1
  ESTATUS=$2

  rm -f output.txt

  echo "Wordsearch test $TEST_NO: ./wordsearch ws_$TEST_NO.txt < input_$TEST_NO.txt > output.txt"
  ./wordsearch ws_$TEST_NO.txt < input_$TEST_NO.txt > output.txt
  STATUS=$?

  # Make sure the program exited with the right exit status.
  if [ $STATUS -ne $ESTATUS ]
  then
      echo "**** Wordsearch test $TEST_NO FAILED - incorrect exit status. Expected: $ESTATUS Got: $STATUS"
      FAIL=1
      return 1
  fi

  # Make sure the output matches the expected output.
  diff -q expected_$TEST_NO.txt output.txt >/dev/null 2>&1
  if [ $? -ne 0 ]
  then
      echo "**** Wordsearch test $TEST_NO FAILED - output didn't match the expected output"
      FAIL=1
      return 1
  fi

  echo "Wordsearch test $TEST_NO PASS"
  return 0
}

# Test the wordsearch program
testWordsearch 0 0
testWordsearch 1 0
testWordsearch 2 0
testWordsearch 3 0
testWordsearch 4 0
testWordsearch 5 0
testWordsearch 6 0
testWordsearch 7 0
testWordsearch 8 0
testWordsearch 9 0
testWordsearch 10 1
testWordsearch 11 1
testWordsearch 12 1
testWordsearch 13 1
testWordsearch 14 1
testWordsearch 15 1
testWordsearch 16 1
testWordsearch 17 1
testWordsearch 18 1
testWordsearchNoArg 19 1
testWordsearch 20 0

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
else 
  exit 0
fi
