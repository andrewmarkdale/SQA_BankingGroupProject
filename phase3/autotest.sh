#!/bin/bash

# Author: Jevon Rambarran & Andrew Dale
# Objective: Scripts for passing in test file into bank terminal

cd BankTesting

# Create array of transactions
#declare -a transactions=("login" "logout" "paybill" "transfer"
#                       "withdrawal" "changeplan" "create" "delete"
#                        "deposit" "disable")
red=`tput setab 1`
green=`tput setaf 2`
reset=`tput sgr0`
declare -i termpass=0
declare -i termc=0
declare -a transactions=("create")
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
                echo "  ${green}Test Passed${reset}";
                termpass+=1
            else
                echo "  ${red}Test Failed${reset}";
                diff $FILE output/${FILE%.*}.out
            fi
            echo "";
            termc+=1
        done

        #Compare expected transaction file with actual transaction file
        for FILE in *.etf; do echo "Comparing $FILE with ${FILE%.*}.atf";
            # Check to see if the files are identical
            if diff -q $FILE output/${FILE%.*}.atf >/dev/null
            then
                echo "  ${green}Test Passed${reset}";
                termpass+=1
            else
                echo "  ${red}Test Failed${reset}";
                diff $FILE output/${FILE%.*}.atf
            fi
            echo "";
            termc+=1
        done
    echo "";
    echo "";
    cd ../
done
current_time=$(date "+%Y.%m.%d-%H.%M.%S")
if([ $termpass -eq $termc ])
then
  echo "$current_time Success: $termpass of $termc passed"
else
  echo "$current_time: Failed: $termpass of $termc passed"
fi