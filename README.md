# Grail-Visualisation

The Grail+ Visualizer is a software tool for visualizing finite automata produced by [Grail+](http://grail.smcs.upei.ca).

Creator: Alastair May
Supervisor: [Taylor J. Smith](https://people.stfx.ca/tjsmith/)

---

### Setup Process for Linux

#### About the setup process:
The main thing you need to do is download the Grail+ files and get them working, which mainly means that you have its 'bin' folder full of files with are different utilities that let you do various things with automata, like converting from a context free language to a regular expression for example. We'll also be installing texlive and evince.

Here are the things you need to do to be fully set up (actual details and instructions are below these 'summary' steps):

1. Get Grail+ Files
2. Install make and g++
3. Run make command to create those 'bin' files
4. Install texlive
5. Update the PATH variable (and optionally MANPATH and INFOPATH) so that texlive works

*Note:* This process was completed in Linux Ubuntu. My understanding is that the process is significantly easier on Mac (and Windows maybe, but there may be complications as far as getting a Linux-like terminal working). However, this guide may not 100% apply to other operating systems, and you may need further help/guidance if not using Linux Ubuntu.

#### Setup instructions in detail:

1. Get Grail+ Files:
        
	Go to the [UPEI Theory of Computing Software Server](http://grail.smcs.upei.ca) and download the latest version of Grail+, then extract it.

2. Install make and g++:
        
	Run this command in terminal:
                
       sudo apt install g++ make

3. Run make command to create those 'bin' files:
	
	Navigate the terminal to the directory inside the new extracted Grail folder (the one with Makefile in it) then run this command (no, seriously, this is it):
            
       make
                
	Now the bin files should be created (yes, key word is *should*).
            
4. Install texlive:
        
	Navigate to https://www.latex-project.org/get/. Then, scroll down slightly to see the TeX distributions for different operating systems. Select the 'TeX Live distribution' link that is under the Linux option. On the resulting page, near the top, there will be something that says 'All the ways to acquire TeX Live'. Click on the 'Download' option under that. On this new page, one of the first links is for 'install-tl-unx.tar.gz'. Click that, which will download the file, and extract it.
            
	Once extracted, the 'install-tl' file inside the extracted folder is the one we care about. Navigate the terminal to the location of 'install-tl' and run this command:
            
       sudo ./install-tl
            
	After a moment, it will prompt you with some options. Press 'i' (case insensitive) to select the 'start installation to hard disk' option and press enter. Afterwards, it should take quite a while to install. You will be able to see the progress and get a decent sense of how much longer until it's done; for me, it took about an hour.

5. Update the PATH variable (and optionally MANPATH and INFOPATH) so that texlive works:
        
	Navigate to your home folder and locate the '.bashrc' file ('.profile' may be an alternative file you can use instead). It is a hidden file, so if you can't see it, hit Ctrl+h to reveal hidden files. Open the file and add the text below (the 3 'export' lines) to the bottom of it; this will add texlive to your path variables. 

	*WARNING:* You may need to edit these lines of code slightly depending on your version of texlive - it's mainly the 2022 part that is most likely to change with time. Use your file explorer to navigate to the file paths shown in these three lines of code to check if they actually exist. If, for example, no 2022 folder exists but a 2023 folder exists, you would change '2022' to '2023' in all three of these lines of code.
                
       export PATH=$PATH:/usr/local/texlive/2022/bin/x86_64-linux
       export MANPATH=/usr/local/texlive/2022/texmf-dist/doc/man
       export INFOPATH=/usr/local/texlive/2022/texmf-dist/doc/info
                
	*Note:* It is likely that only the first line is needed, but texlive asks you to add the MANPATH and INFOPATH stuff, so I included it just in case.
        
	When finished, save the file, then type `tlmgr --version` in terminal to test if steps 4 and 5 are working. If the command is unrecognised or not found, then it's not working. If it is not working, try restarting the terminal, then run the command again. If that does not help, revisit steps 4 and 5 to try and determine the issue. I would recommend checking the file paths of the export lines as a first troubleshooting step. Try putting an export line into terminal and then have terminal echo the corresponding path variable to see if it updated properly, and also check if the file paths actually exist (note only the PATH variable matters for getting this to work).
        
5. Miscellaneous Packages:
        
	The program makes use of evince, so in order to use it, install it with this command:
            
       sudo apt install evince
                
                
That's it! Everything is set up! You should now be able to run commands like `texdoc tikz` & `pdflatex`.
        
---

### Useful Commands

Opens up documentation about TikZ. Stuff about automata (the stuff we actually care about) starts at page 572:
	
	texdoc tikz
		
Run the TikZ program using a test file (for some number N) containing example Grail+ output (navigate terminal to the directory where it is first):
	
	bash GrailVis testN.txt
		
Convert TikZ code (.tex file) into a pdf (will also create a useless .aux and .log file that you can ignore):

	pdflatex PATH_OF_TEX_FILE

---

### Info About Files

- GrailVis: Takes in Grail+ file output as input (argument #1) and creates a TikZ code file (result.tex) that describes how to construct a visual representation of the finite automaton (more about the algorithm below). It then converts the TikZ code into a pdf image (result.pdf) and displays the pdf (the conversion and displaying of the pdf can be easily disabled by commenting out the last two lines of the code).

    Example of how to run GrailVis:

    On Linux Ubuntu, open the terminal in the location of GrailVis. Then run the command 
    
      bash GrailVis testN.txt

- Strategy Notes: A text file with some notes on how the algorithm for organising the arrangement of states and transitions in GrailVis can be improved.

- Examples/testN.txt: Sample output files from Grail+ that describe a finite automaton that can be used as the input for GrailVis. Some test files are examples of automata that work well with the algorithm to produce a nice diagram, while others are examples of those that work less well and thus can be used to figure out improvements on the current basic algorithm (more info below).

- result.tex: Output TikZ file from running GrailVis.

- result.pdf: Output pdf file from running GrailVis.
    
---

### About the Algorithm

The method that the Grail+ Visualizer currently uses in order to decide where to put states (i.e. to decide the value of each state's x and y values) is as follows:
- Each state's x value will simply be determined by which state the program saw first. For example, the first state found will get an x of 1, the second will get an x of 2, and so on.
- For the y values, create an array with size equal to the number of states. Initialize all values in the array, and thus all the y values, to 0. 
- For every transition that exists between state p and state q in this automaton:
	- Determine which states x-wise exist between states p and q, then find out which one of them has the highest y value. Then, add 1 to that value. Then, compare this value to the heights (y values) of state p and q. Out of those three numbers, the highest will be the new y value for states p and q.

This method is simple and relatively clean and easy to build on, but has some issues. Notes about these and ideas on how to fix them are in the 'Strategy Notes' text file.
