#!/bin/bash

# Ray & Sherry May/2010
# This will generate a Makefile file for current system (unix-like)
# Currently support:
#		 IBM's xlC under AIX
#		 USL's Cfront on DEC Ultrix
#		 USL's Cfront under Sun OS
#		 Delta/C++ compiler under IRIX
#		 Linux gcc

clear
echo "System information:"
echo `uname -a`

#rm old Makefile
if [ -f Makefile ]
then
 rm Makefile
fi


#cp the right Makefile to current folder
case `uname` in
Darwin)
	echo "This is Darwin"
	echo ". Enter s or S to select gcc version, any other key to use default gcc compiler."
	read option
	case "$option" in
s|S)   	echo "gcc Versions detecting"
(find /bin /usr/bin -name "*clang++*")1>gp.tmp 2>/dev/null # compiler
	# denote the symbolic links found
	while read line
	do
    		if [ -h $line ]
		then
			#echo $line
			(file $line) 1>>gppp.tmp
	                echo $line | cat >>gpp.tmp	
		else	
		  	echo $line | cat >>gpp.tmp
			echo $line | cat >>c.tmp
		fi
	done <gp.tmp
	cat gppp.tmp>>gpp.tmp
	cat cc.tmp>>c.tmp
	rm gp.tmp gppp.tmp cc.tmp

        V=`more gpp.tmp|wc -l`
	if [ "$V" = "0" ]
		 then
			echo "No gcc detected! install first!"
			exit 1
	elif [ "$V" = "1" ]
		 then
			echo "only one gcc detected, will be used"
			cc="gcc"
	else
		echo "$V gcc detected, please select"

			COUNT=1
			while read line
			do
    				echo "$COUNT. $line"
				COUNT=$((COUNT+1))
			done <gpp.tmp
			read choice     #to optimize so no choice means default
			cc=g++#`head -n$choice c.tmp|tail -n1`

fi
	rm gpp.tmp c.tmp;;
*) echo "use default"
		     cc="g++";;
esac
#test math library set
echo "math library test"
ARCH=`uname -m`
cc -lm m.c >/dev/null 2>&1

if [ "$?" = "1" ]
then
       echo "linuxCC=$cc"|cat >Makefile
       cat Makefiles/Makefile_linux_ubuntu12 >>Makefile
       echo "make-Makefile successfully"
else 
        echo "linuxCC=$cc"|cat >Makefile
        cat Makefiles/Makefile_linux >>Makefile
       echo "make-Makefile successfully"
fi;;

AIX)    echo "AIX detected"
        cp Makefiles/Makefile_aix Makefile
	echo "make-Makefile successfully";;

ULTRIX) echo "ULTRIX detected"
        cp Makefiles/Makefile_ultrix Makefile
	echo "make-Makefile successfully";;

SunOS)  echo "SunOS detected"
        cp Makefiles/Makefile_sunos Makefile
	echo "make-Makefile successfully";;

IRIX)   echo "IRIX detected"
        cp Makefiles/Makefile_irix Makefile
	echo "make-Makefile successfully";;

*) echo "Sorry, this system is not supported by this script yet, please maintain the Makefile manually !"

	;;

Linux|SunOS)	echo "Enter s or S to select gcc version, any other key to use default gcc compiler."
	read option
	case "$option" in

s|S)   	echo "gcc Versions detecting"
	(find /bin /usr/bin /usr/local /opt -executable -name "*gcc*")1>gp.tmp 2>/dev/null
	# denote the symbolic links found
	while read line
	do
    		if [ -h $line ]
		then
			#echo $line
			(file $line) 1>>gppp.tmp
			echo $line | cat >>cc.tmp
		else
		  	echo $line | cat >>gpp.tmp
			echo $line | cat >>c.tmp
		fi
	done <gp.tmp
	cat gppp.tmp>>gpp.tmp
	cat cc.tmp>>c.tmp
	rm gp.tmp gppp.tmp cc.tmp

	V=`more gpp.tmp|wc -l`

	if [ "$V" = "0" ]
		 then
			echo "No gcc detected! install first!"
			exit 1
	elif [ "$V" = "1" ]
		 then
			echo "only one gcc detected, will be used"
			cc="gcc"
	else
		echo "$V gcc detected, please select"

			COUNT=1
			while read line
			do
    				echo "$COUNT. $line"
				COUNT=$((COUNT+1))
			done <gpp.tmp
			read choice     #to optimize so no choice means default
			cc=g++#`head -n$choice c.tmp|tail -n1`

	fi
	rm gpp.tmp c.tmp;;
*) echo "use default"
		     cc="gcc";;
esac

#test math library set
echo "math library test"
ARCH=`uname -m`
cc -lm m.c >/dev/null 2>&1

if [ "$?" = "1" ]
then
       echo "linuxCC=$cc"|cat >Makefile
       cat Makefiles/Makefile_linux_ubuntu12 >>Makefile
       echo "make-Makefile successfully"
else 
        echo "linuxCC=$cc"|cat >Makefile
        cat Makefiles/Makefile_linux >>Makefile
       echo "make-Makefile successfully"
fi;;

AIX)    echo "AIX detected"
        cp Makefiles/Makefile_aix Makefile
	echo "make-Makefile successfully";;

ULTRIX) echo "ULTRIX detected"
        cp Makefiles/Makefile_ultrix Makefile
	echo "make-Makefile successfully";;

SunOS)  echo "SunOS detected"
        cp Makefiles/Makefile_sunos Makefile
	echo "make-Makefile successfully";;

IRIX)   echo "IRIX detected"
        cp Makefiles/Makefile_irix Makefile
	echo "make-Makefile successfully";;

*) echo "Sorry, this system is not supported by this script yet, please maintain the Makefile manually !"
esac
