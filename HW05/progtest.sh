	#!/bin/bash
 
# Zmente, pokud se vas binarni soubor jmenuje jinak
PROGRAM=./a.out
 
# Pro vsechny soubory s nazvem "*_in.txt"...
for TEST_FILE in CZE/*_in.txt; do
	echo -n ">>> Testing $TEST_FILE "
 
	# Zjisti rozdil mezi vystupem programu a vzorovym vystupem a uloz ho do promenne $DIFF
	DIFF=`diff ${TEST_FILE/in/out} <($PROGRAM < $TEST_FILE)`
	if [ "$DIFF" == "" ]; then
		echo "- OK"
	else
		echo "- FAILED"
 
		# Vypis obsah testovaciho vstupu (tedy data, ktera chybu zpusobila)
		echo "Input:"
		cat $TEST_FILE
		echo
 
		# Vypis rozdil mezi vystupem programu a vzorovym vystupem
		echo "Output diff:"
		echo "$DIFF"
		echo
	fi
done
