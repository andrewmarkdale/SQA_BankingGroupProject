#!/bin/bash

# Author: Jevon Rambarran & Andrew Dale 
# Objective: Scripts for passing in test file into bank terminal

cd BankTesting

# Create array of transactions
declare -a transactions=("login" "logout" "paybill" "transfer"
                        "withdrawal" "changeplan" "create" "delete"
                        "deposit" "disable")

# Loop throught each transaction test directory
for i in "${transactions[@]}"
    do
    echo "Testing $i transactions:";
    cd $i
        #Running test file to generate actual session transaction file and actual terminal output
        for FILE in *.inp; do echo "Running test $FILE";
            #Starting the bank terminal and generating our output files
            ../.././main ../../CurrentBankAccounts.txt output/${FILE%.*}.atf < $FILE > output/${FILE%.*}.out
        done

        #Compare expected terminal output with actual terminal output
        for FILE in *.bto; do echo "Comparing $FILE with ${FILE%.*}.out";
            # Check to see if the files are identical
            if diff -q $FILE output/${FILE%.*}.out >/dev/null
            then
                echo "  Test Passed";
            else
                echo "  Test Failed";
                diff $FILE output/${FILE%.*}.out
            fi
            echo "";
        done

        #Compare expected transaction file with actual transaction file
        for FILE in *.etf; do echo "Comparing $FILE with ${FILE%.*}.atf";
            # Check to see if the files are identical
            if diff -q $FILE output/${FILE%.*}.atf >/dev/null
            then
                echo "  Test Passed";
            else
                echo "  Test Failed";
                diff $FILE output/${FILE%.*}.atf
            fi
            echo "";
        done
    echo "";
    echo "";
    echo "";
    cd ../
done