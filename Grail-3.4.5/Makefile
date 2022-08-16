#/usr/bin/clang++
linuxCC=gcc

#linuxCC=c++
CC=$(linuxCC)

#SYS: this is for linux system
#SYS=linux

#linuxFL = -O2 -o grail.out
linuxFLNEW = -Wdangling-else -Wcomment -Wshift-op-parentheses  -Wno-deprecated  -O2 -o grail.out  -lm -lstdc++
#linuxFL = -std=c++0x -Wno-deprecated -lm -O2 -o grail.out
#-Wmismatched-new-delete 

linuxFL =   -Wno-deprecated  -O2 -o grail.out  -lm -lstdc++

ARCH=`uname -m`

#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/${ARCH}-linux-gnu

all:
	@$(MAKE) clean "MAKE=$(MAKE)"
	@$(MAKE) compile TYPE=char "MAKE=$(MAKE)"
#	@$(MAKE) compile TYPE=re "MAKE=$(MAKE)"
#	@$(MAKE) compile TYPE=mlychar "MAKE=$(MAKE)"
#	@$(MAKE) compile TYPE=mlyint "MAKE=$(MAKE)"
	@$(MAKE) install TYPE=char "MAKE=$(MAKE)"
#	@$(MAKE) install TYPE=re
#	@$(MAKE) install TYPE=mlychar
#	@$(MAKE) install TYPE=mlyint
	
	@echo "Everything made"



compile:
#	@echo $(LD_LIBRARY_PATH)
	@cd $(TYPE); $(MAKE) CC='$(linuxCC)' CCFLAGS='$(linuxFL)' BIN=../binaries/linux/
#	$(CC) $(linuxFL)
#	-o $../binaries/linux/char.out
	@./pmd


install:
	@cd $(TYPE); $(MAKE) install CP="ln -s" BIN=../binaries/linux/ I_BIN=../bin/
#	@cp char/GrailVersion.txt ${BIN}

checkout:
	@cd tests; $(MAKE) checkout 
	@echo "Testing complete."

clean:
	@cd char; $(MAKE) clean_UNIX
#	#@cd re; $(MAKE) clean_UNIX
#	#@cd mlychar; $(MAKE) clean_UNIX
#	#@cd mlyint; $(MAKE) clean_UNIX
	@cd tests; $(MAKE) clean
	@rm -rf bin/* mon.out core tests/errors/* profiles/core
	@echo "Everything clean."

profile:
	@cd profiles; $(MAKE)
	@echo "Profiling complete."
