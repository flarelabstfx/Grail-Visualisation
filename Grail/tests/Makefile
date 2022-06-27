#	This code copyright (c) by the Grail project.
#	No commercial use permitted without written consent.
#	January 1996

check_dos:
		@delete errors\*.* failed passed
		@sh -c ./check.ksh

checkout:
		@rm -f errors/* passed failed
		@unix/fmtest fmcment
		@unix/fmtest fmcomp
		@unix/fmtest fmenum
		@unix/fmtest fmmin
		@unix/fmtest fmminrev
		@unix/fmtest fmplus
		@unix/fmtest fmstar
		@unix/fmtest fmtofl
		@unix/fmtest fmreach
		@unix/fmtest fmrenum
		@unix/fmtest fmrevers
		@unix/fmtest fmtore
		@unix/fmtest iscomp
		@unix/fmtest isdeterm
		@unix/fmtest isuniv
		@unix/fmtest fmdeterm
		@unix/fm2test fmcat
		@unix/fm2test fmcross
		@unix/fm2test fmunion
		@unix/fm2test isomorph
		@unix/retest remin
		@unix/retest restar
		@unix/retest retofm
		@unix/retest retofl
		@unix/retest isempty
		@unix/retest isnull
		@unix/re2test recat
		@unix/re2test reunion
		@unix/fltest flrevers
		@unix/fltest fltofm
		@unix/fltest fltore
		@unix/fl2test flprod
		@unix/fl2test flunion
		@unix/fm3test fmexec
		@unix/fm4test fmorder
		@unix/fmtest fmsize
		@unix/fmtest fmstats
		@unix/fl3test flappend
		@unix/fl3test flexec
		@unix/flfmtest flfilter
		@unix/fl3test fllq
		@unix/fl3test flprepen
		@unix/fl3test flrq
		@unix/afatest afasize
#		@unix/afatest afatofm
		@unix/fcmtest fcmenum
		@unix/fcm2test fcmexec
		@unix/fcmtest fcmmin
#		@unix/fcmtest fcmtofm
		@unix/fltest fltofcm
		@unix/fmtest2 fmtofcm
		@unix/fmtest2 fmtofcm2
		@unix/fltest2 flsubclose
#		@unix/fltest fltofmmn

clean:
		@rm -f errors/* unix/*.tmp unix/core passed failed
