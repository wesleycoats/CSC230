#!/bin/bash
FAIL=0

# Make a fresh copy of the target program
make clean
make
if [ $? -ne 0 ]; then
  echo "**** Make (compilation) FAILED"
  exit 13
fi

# Compare the content of two given filenames, fail if they differ or
# if one of them doesn't exist.  The first filename should be the
# expected file, and the second should be the one created by the
# program.  An optional third parameter says what to call the file
# that doesn't match.
matchFile() {
    if [ "$#" -eq 3 ]; then
	name="$3"
    else
	name="$2"
    fi

    if [ ! -f "$1" ]; then
	echo "   **** Something's wrong.  Expected a file named $1."
	FAIL=1
	return 1
    fi

    if [ -f "$1" ] && [ ! -f "$2" ]; then
	echo "   **** Test failed - file $2 doesn't exist, but it should."
	FAIL=1
	return 1
    fi

    
    if ! diff -q "$1" "$2" >/dev/null; then
	echo "   **** Test failed - $name doesn't match expected"
	FAIL=1
	return 1
    fi

    return 0
}


# Function to run the program against a test case, checking
# its output, exit status and error output against what's expected.
runtest() {
    TESTNO="$1"
    shift
    EX_STATUS="$1"
    shift

    # Remove any files that we want to test for.
    rm -f stderr.txt

    MODE="$1"
    shift
    KEY="$1"
    shift
    INFILE="$1"
    shift
    OUTFILE="$1"
    shift
	
    echo "Test $TESTNO: ./crypt $MODE $KEY $INFILE $OUTFILE 2> stderr.txt"
    ./crypt $MODE $KEY $INFILE $OUTFILE 2> stderr.txt
    STATUS=$?
      

    # Make sure we got the expected exit status.
    if [ $STATUS -ne $EX_STATUS ]; then
	echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
	FAIL=1
	return 1
    fi

    if [ $EX_STATUS -eq 0 ]; then
	# Make sure the resulting text file looks right.
	if ! matchFile e_$TESTNO $OUTFILE "text file $OUTFILE"; then
	    return 1
	fi

	if [ -s stderr.txt ]; then
	    echo "   **** Test failed - shouldn't be any output on standard error"
	    FAIL=1
	    return 1
	fi
    else
	# Make sure the program's error output looks right.
	if ! matchFile estderr_$TESTNO.txt stderr.txt "error output"; then
	    return 1
	fi
    fi
    
    echo "Test $TESTNO passed"
    return 0
}

# Run each of the test cases
runtest 01 0 e password p_01 a_01
runtest 02 0 d password c_02 a_02
runtest 03 0 e password p_03 a_03
runtest 04 0 d password c_04 a_04
runtest 05 0 e password p_05 a_05
runtest 06 0 d password c_06 a_06
runtest 07 0 e password p_07 a_07
runtest 08 0 d password c_08 a_08
runtest 09 0 e candybar p_09 a_09
runtest 10 0 d candybar c_10 a_10
runtest 11 0 e candybar p_11 a_11
runtest 12 0 d candybar c_12 a_12
runtest 13 1 a candybar c_13 a_13
runtest 14 1 d candyba c_14 a_14
runtest 15 1 d candybars c_15 a_15
runtest 16 1 d candybar c_16 a_16

# Incorrect number of command line arguments - too few
echo "Test 17: ./crypt e password 2> stderr.txt"
./crypt e password 2> stderr.txt
STATUS=$?

# Make sure we got the expected exit status.
if [ $STATUS -ne 1 ]; then
    echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
    FAIL=1
else
    if matchFile estderr_17.txt stderr.txt "error output"; then
	echo "Test 17 passed"
    fi
fi

# Incorrect number of command line arguments - too many
echo "Test 18: ./crypt e password c_18 e_18 o_18 2> stderr.txt"
./crypt e password c_18 e_18 o_18 2> stderr.txt
STATUS=$?

# Make sure we got the expected exit status.
if [ $STATUS -ne 1 ]; then
    echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
    FAIL=1
else 
    if matchFile estderr_18.txt stderr.txt "error output"; then
	echo "Test 18 passed"
    fi
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
fi

exit 0
