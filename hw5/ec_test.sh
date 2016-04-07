#!/bin/bash
FAIL=0

# Make a fresh copy of the target program
make clean
make tripleCrypt
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
    KEY1="$1"
    shift
    KEY2="$1"
    shift
    INFILE="$1"
    shift
    OUTFILE="$1"
    shift
	
    echo "Test $TESTNO: ./tripleCrypt $MODE $KEY1 $KEY2 $INFILE $OUTFILE 2> stderr.txt"
    ./tripleCrypt $MODE $KEY1 $KEY2 $INFILE $OUTFILE 2> stderr.txt
    STATUS=$?
      

    # Make sure we got the expected exit status.
    if [ $STATUS -ne $EX_STATUS ]; then
	echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
	FAIL=1
	return 1
    fi

    if [ $EX_STATUS -eq 0 ]; then
	# Make sure the resulting text file looks right.
	if ! matchFile ec_e_$TESTNO $OUTFILE "text file $OUTFILE"; then
	    return 1
	fi

	if [ -s stderr.txt ]; then
	    echo "   **** Test failed - shouldn't be any output on standard error"
	    FAIL=1
	    return 1
	fi
    else
	# Make sure the program's error output looks right.
	if ! matchFile ec_estderr_$TESTNO.txt stderr.txt "error output"; then
	    return 1
	fi
    fi
    
    echo "Test $TESTNO passed"
    return 0
}

# Run each of the test cases
runtest 01 0 e password candybar ec_p_01 ec_a_01
runtest 02 0 d password candybar ec_c_02 ec_a_02
runtest 03 0 e password candybar ec_p_03 ec_a_03
runtest 04 0 d password candybar ec_c_04 ec_a_04
runtest 05 0 e password candybar ec_p_05 ec_a_05
runtest 06 0 d password candybar ec_c_06 ec_a_06
runtest 07 0 e password candybar ec_p_07 ec_a_07
runtest 08 0 d password candybar ec_c_08 ec_a_08
runtest 09 0 e candybar password ec_p_09 ec_a_09
runtest 10 0 d candybar password ec_c_10 ec_a_10
runtest 11 0 e candybar password ec_p_11 ec_a_11
runtest 12 0 d candybar password ec_c_12 ec_a_12
runtest 13 1 a candybar password ec_c_13 ec_a_13
runtest 14 1 d candyba password ec_c_14 ec_a_14
runtest 15 1 d candybars password ec_c_15 ec_a_15
runtest 16 1 d candybar password ec_c_16 ec_a_16
runtest 19 1 d candybar candybar ec_c_19 ec_a_19

# Incorrect number of command line arguments - too few
echo "Test 17: ./tripleCrypt e password 2> stderr.txt"
./tripleCrypt e password 2> stderr.txt
STATUS=$?

# Make sure we got the expected exit status.
if [ $STATUS -ne 1 ]; then
    echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
    FAIL=1
else
    if matchFile ec_estderr_17.txt stderr.txt "error output"; then
	echo "Test 17 passed"
    fi
fi

# Incorrect number of command line arguments - too many
echo "Test 18: ./tripleCrypt e password candybar ec_c_18 ec_e_18 ec_o_18 2> stderr.txt"
./tripleCrypt e password candybar ec_c_18 ec_e_18 ec_o_18 2> stderr.txt
STATUS=$?

# Make sure we got the expected exit status.
if [ $STATUS -ne 1 ]; then
    echo "   **** Test failed - incorrect exit status. Expected: $EX_STATUS Got: $STATUS"
    FAIL=1
else 
    if matchFile ec_estderr_18.txt stderr.txt "error output"; then
	echo "Test 18 passed"
    fi
fi

if [ $FAIL -ne 0 ]; then
  echo "FAILING TESTS!"
  exit 13
fi

exit 0
