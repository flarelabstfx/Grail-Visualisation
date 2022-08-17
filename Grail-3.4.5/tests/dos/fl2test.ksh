#!/bin/sh
#	This code copyright (c) by the Grail project.
#	No commercial use permitted without written consent.
#	June 1994

BIN=../bin
MACHINES=machines
ERRORS=errors

for i in l1 l2 l3 l4 l5 l6
do
	$BIN/$1 ${MACHINES}/$i ${MACHINES}/l3 | sort >$$.tmp
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
