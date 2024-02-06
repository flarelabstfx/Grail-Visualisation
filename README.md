# Grail-Visualisation

### Setup Process for Linux:

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
        
	Go to www.csit.upei.ca/theory/ and download latest version of grail, then extract it.

2. Install make and g++:
        
	Run this command in terminal:
                
       sudo apt install g++ make

3. Run make command to create those 'bin' files:
	
	Navigate the terminal to the directory inside the new extracted Grail folder (the one with Makefile in it) then run this command (no seriously this is it):
            
       make
                
	Now the bin files should be created (yes, key word is should).
            
4. Install texlive:
        
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
        
	When finished, save the file, then type `tlmgr --version` in terminal to test if step 4 and 5 are working, if the command is unrecognised or not found then it's not working. If it is not working, try restarting the terminal, then run the command again. If that does not help, revisit steps 4 and 5 to try and determine the issue. I would recommend checking the file paths of the export lines as a first troubleshooting step. Try putting an export line into terminal and then have terminal echo the corresponding path variable to see if it updated properly and also check if the file paths actually exist (note only the PATH varable matters for getting this to work).
        
5. Miscellanious Packages:
        
	My program I wrote makes use of evince, so in order to use it, install it with this command:
            
       sudo apt install evince
                
                
That's it! Everything is setup! You should now be able to run commands like `texdox tikz` & `pdflatex`
        
--------------------------------------------------

#### Usefull commands:

Opens up documentation about tikz. Stuff about automata (the stuff we actually care about starts at page 572):
	
	texdoc tikz
		
Run my tikz program using a test file (for some number N) containing example grail output (navigate terminal to the directory where it is first):
	
	bash Program testN.txt
		
Convert tikz code (.tex file) into a pdf (will also create a useless .aux and .log file that you can ignore):

	pdflatex PATH_OF_TEX_FILE

#### Info about files:

- testN.txt: Sample output files from grail that describe a finite automaton that can be used as the input for Program. Some test files are examples of automata that work well with the algorithm to produce a nice diagram, while others are examples of those that work less well and thus can be used to figure out improvment on the current basic algorithm (more info below).

- Program: Takes in grail file output as input (argument #1) and creates a tikz code file (result.tex) that describes how to constrct a visual representation of the finite automaton (more about the algorithm below). It then converts the tikz code into a pdf image (result.pdf) and displays the pdf (the convertion and displaying of the pdf can be easily disabled by commenting out the last two lines of the code).

    Example of how I ran Program:

    On linux ubuntu I open the terminal in the location of Program. Then run the command 
    
      bash Program testN.txt

- result.tex: Output tikz file from running Program.

- result.pdf: Output pdf file from running Program.

- Strategy Notes: Just a text file with some notes on how the algorithim for organising the arangement of states and transitions in Program can be improved.

- Examples (Folder): Just a bunch of random old files with examples of tikz code and pdf diagrams.
    
--------------------------------------------------

#### About Program's Algorithm:

The method that Program currently uses into order to decide where to put states (i.e. decide the value of each state's x and y values) is as follows:
- Each state's x value will simply be determined by which state the program saw first. For example the first state it found will get an x of 1, the second will get an x of 2 and so on.
- For the y values, create an array the size of the number of states. Initialise all values in the array and thus all the y values to 0. 
- For every transition that exists that connect state p and state q in this automaton...
	- Determine which states x-wise exist between states p and q, then find out which one of them has the highest y value. Then add 1 to that value. Then compare this value to the heights (y values) of state p and q. Out of those three numbers, the highest will be the new y value for states p and q.

This method is simple and relativly clean and easy to build on but has some issues, notes about these and ideas on how to fix them are in the 'Strategy Notes' text file.
