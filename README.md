# Grail-Visualisation

### Setup Process for Linux:

#### WARNING:
The current 'Grail-3.4.5' folder may have missing or corrupted files in the bin folder. This should not matter if you follow this guide as it will guide you to download and generate your own Grail folder to make sure you have the most up to date version anyway. The Grail folder that is already contained in this repo should be used as a last resort (you can also re-extract from the tar.gz file for extra caution). Even if you do, you will need to follow all the steps after step 1 (assuming the files in the bin folder are missing or corrupted, if they are corrupted, delete them before regenerating them using the below steps).

#### About the setup process:
The main thing you need to do is download the grail files and get them working which mainly means that you have it's 'bin' folder full of files with are different utilities that let you do various things with automata, like converting from a context free language to a regular expression for example. We'll also be installing texlive and evince.

Here are the things you need to do to be fully setup (actual details and instructions are below these 'summary' steps):

1. Get Grail Files
2. Install make and g++
3. Run make command to create those 'bin' files
4. Install texlive
5. Update the PATH variable (and optionally MANPATH and INFOPATH) so that texlive works

Note: This process was completed in Linux Ubuntu, my understanding is that the process is significantly easier on Mac (Windows maybe but there may be complications as far as getting a linux-like terminal working), however this guide may not 100% apply to other operating systems and you may need further help/guidance if not using Linux Ubuntu.

#### Setup instrctions in detail:

1. Get Grail Files:
        
	Go to www.csit.upei.ca/theory/ and download latest version of grail, then extract it. If you cannot download it, you can use the 'Grail-3.4.5.tar.gz' file included in this git repo (which may be out of date so use only if needed).

2. Install make and g++:
        
	Run this command in terminal:
                
       sudo apt install g++ make

3. Run make command to create those 'bin' files:
	
	Navigate the terminal to the directory inside the new extracted Grail folder (the one with Makefile in it) then run this command (no seriously this is it):
            
       make
                
	Now the bin files should be created (yes, key word is should).
            
4. Install texlive:
        
	(If you cannot get or download the file using the below instructions, use the 'install-tl-unx.tar.gz' file already included in this repo, again, it might be out of date, so use only if needed)
            
	Navigate to https://www.latex-project.org/get/ . Then, scroll down slightly to see the tex distributions for different operating systems. Select 'TeX Live distribution' link that is under the Linux option. On the resulting page, near the top, there will be something that says 'All the ways to acquire TeX Live'. Click on the 'download' option under that. On this new page, one of the first links is for 'install-tl-unx.tar.gz' click that which will download the file, extract it.
            
	Once extracted, the 'install-tl' file inside the extracted folder is the one we care about. Navigate the terminal to the location of 'install-tl' and run this command:
            
       sudo ./install-tl
            
	After a moment, it will prompt you with some options, press 'i' (case insensitive) to select the 'start installation to hard disk' option and press enter. Afterwards it should take quite a while to install. You will be able to see the progress and get a decent sense of how much longer until it's done, for me it took about an hour.

5. Update the PATH variable (and optionally MANPATH and INFOPATH) so that texlive works:
        
	Navigate to your home folder and locate the '.bashrc' file ('.profile' may be an alternative file you can use instead). It is a hidden file, so if you can't see it, hit Ctrl+h to reveal hidden files. Open the file and add the text below (the 3 'export' lines) to the bottom of it, this will add texlive to your path variables. WARNING: You may need to edit these lines of code slightly depending on your version of texlive, it's mainly the 2022 part that is most likely to change with time. Use your file explorer to navigate to the file paths shown in these three lines of code to check if they actually exist. If for example, no 2022 folder exists but a 2023 fodler exists you would change 2022 to 2023 in all three of these lines of code.
                
       export PATH=$PATH:/usr/local/texlive/2022/bin/x86_64-linux
       export MANPATH=/usr/local/texlive/2022/texmf-dist/doc/man
       export INFOPATH=/usr/local/texlive/2022/texmf-dist/doc/info
                
	Note: It is likely that only the first line is needed but texlive asks you to add the MANPATH and INFOPATH stuff so I included it just in case.
        
	When finished, save the file, then type `tlmgr --version` in terminal to test if step 4 and 5 are working, if the command is unrecognised or not found then it's not working. If it is not working, try restarting the terminal, then run the command again. If that does not help, revisit steps 4 and 5 to try and determine the issue. I would recommend checking the file paths of the export lines as a first troubleshooting step, try putting an export line into terminal and then have terminal echo the corresponding path variable to see if it updated properly and also check if the file paths actually exist (note only the PATH varable matters for getting this to work).
        
5. Miscellanious Packages:
        
	My program I wrote makes use of evince, so in order to use it, install it with this command:
            
       sudo apt install evince
                
                
That's it! Everything is setup! You should now be able to run commands like `texdox tikz` & `pdflatex`
        
--------------------------------------------------

#### Usefull commands:

Opens up documentation about tikz. Stuff about automata (the stuff we actually care about starts at page 572):
	
	texdoc tikz
		
Run my tikz program using the test file containing example grail output (navigate terminal to the directory where it is first):
	
	./Program ./test
		
Alternativly you can run this to test the other grail output:
	
	./Program ./test_copy
	
Convert tikz code (.tex file) into a pdf (will also create a useless .aux and .log file that you can ignore):

	pdflatex PATH_OF_TEX_FILE

#### Info about files:

- Grail (Folder): The Grail folder that was downloaded from Github, the setup instructions assumes that you wont be using this folder and will download the most up to date version from Gihub and then do setup for it. If all else fails, you can try using this folder instead but will still have to do the make setup. Otherwise ignore, rename/backup, or remove it.

- test & test_copy: A sample output file from grail that describes a finite automaton that can be used as the input for Program. The 'test' file is an example of an automaton that works well with the algorithm to produce a nice diagram, test_copy is an example of one that works less well and thus can be used to figure out improvment on the current basic algorithm (more info below).

- Program: Takes in grail file output as input (argument #1) and creates a tikz code file (result.tex) that describes how to constrct a visual representation of the finite automaton. It then converts the tikz code into a pdf image (result.pdf) and displays the pdf (the convertion and displaying of the pdf can be easily disabled by commenting out the last two lines of the code).

    Example of how I ran Program:

    On linux ubuntu I open the terminal in the location of Program. Then run the command 
    
      ./Program ./test

- result.tex: Output tikz file from running Program.

- result.pdf: Output pdf file from running Program.

- result.aux & result.log: Useless files that are created during the process of convering the tikz code into pdf. They can be deleted safely but will be re-created when any such new process happends.

- Strategy Notes: Just a text file with some notes on how the algorithim for organising the arangement of states and transitions in Program can be improved.

- Random Examples (Folder): Just a bunch of random old files with examples of tikz code and pdf diagrams.
    
- Grail-3.4.5.tar.gz & install-tl-unx.tar.gz: Files I used as part of the setup process, use these only if you can't download them normally as these ones may be out of date.
