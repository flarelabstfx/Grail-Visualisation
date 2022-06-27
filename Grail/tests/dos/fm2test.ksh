#!/bin/sh
#	This code copyright (c) by the Grail project.
#	No commercial use permitted without written consent.
#	June 1994

BIN=../bin
MACHINES=machines
ERRORS=errors

for i in d1 d2 d3 d4 d5 d6 d7 d8 n1 n2
do
	$BIN/$1 ${MACHINES}/$i ${MACHINES}/d1 | sort >$$.tmp
	echo "Testing	$1	on	$i"
	sort $1/$i >out
	if diff $$.tmp out
	then
		rm $$.tmp
	else
		mv $$.tmp ${ERRORS}/$1.$i
	fi
	rm out
done
