#!/bin/bash

# Author: Jevon Rambarran&Andrew
# Objective: Scripts for passing in test file into bank terminal

cd BankTesting/login
for FILE in *.inp; do echo "Testing $FILE:";
    ../.././main ../../CurrentBankAccounts.txt output/${FILE%.*}.atf < $FILE > output/${FILE%.*}.out
done

for FILE in *.bto; do echo "Comparing $FILE with ${FILE%.*}.out";
    diff $FILE output/${FILE%.*}.out
done

for FILE in *.etf; do echo "Comparing $FILE with ${FILE%.*}.atf";
    diff $FILE output/${FILE%.*}.atf
done