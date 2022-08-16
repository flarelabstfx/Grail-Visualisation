# Grail-Visualisation

Setup Process for Linux (WIP):

    WARNING:
    The current 'Grail-3.4.5' folder may have missing or corrupted files in the bin folder. This should not matter if you follow this guide as it will guide you to create your own Grail folder to make sure you have the most up to date version anyway. The Grail folder that is already contained here should be used as a last resort. It is the old folder I downloaded and set up using the step by step set up process I describe below.

    About the Grail setup process:
    The main thing you need to do is get ahold of the grail files and get them working which mainly means that you have it's 'bin' folder full of files with are different utilities that let you do various things with automata, like converting from a context free language to a regular expression for example.

    Here are the things you need to do to setup Grail:

        1. Get Grail Files
        2. Install needed packages from terminal
        3. Run a makefile command to create those 'bin' files

        Note: This process was completed in Linux Ubuntu, my understanding is that the process is significantly easier on Mac (Windows maybe but there may be complications as far as getting a linux-like terminal working), however this guide may not 100% apply to a Mac setup and you may need further help/guidance if not using Linux Ubuntu.

        Setup instrctions in detail:

        1. Get Grail Files:

            ???(NAVIGATE TO SITE, I FORGET WHAT PRBLEMS HERE WERE)

        2. Install needed packages:

            ???g++, make, texlive, and more??? test tlmgr command??? tlmgr --version

        3. Run makefile command to create those 'bin' files

            ???(RUN THIS -> make ./makefile)

        4. Install texlive

 - Install g++, makefile

 - Install grail from github

 - install texlive? + other stuff related???
 - install evince (Program makes use of evince)


Info about files:

    Grail (Folder): The Grail folder that was downloaded from Github, the setup instructions assumes that you wont be using this folder and will download the most up to date version from Gihub and then do setup for it. If all else fails, you can try using this folder instead. Otherwise ignore, rename/backup, or remove it.

    - test & test_copy: A sample output file from grail that describes a finite automaton that can be used as the input for Program. The 'test' file is an example of an automaton that works well with the algorithm to produce a nice diagram, test_copy is an example of one that works less well and thus can be used to figure out improvment on the current basic algorithm (more info below).

    - Program: Takes in grail file output as input (argument #1) and creates a tikz code file (result.tex) that describes how to constrct a visual representation of the finite automaton. It then converts the tikz code into a pdf image (result.pdf) and displays the pdf (the convertion and displaying of the pdf can be easily disabled by commenting out the last two lines of the code).

    Example of how I ran Program:

    On linux ubuntu I open the terminal in the location of Program. Then run the command `./Program ./test`

    - result.tex: Output tikz file from running Program.

    - result.pdf: Output pdf file from running Program.

    - result.aux & result.log: Useless files that are created during the process of convering the tikz code into pdf. They can be deleted safely but will be re-created when any such new process happends.

    - Strategy Notes: Just a text file with some notes on how the algorithim for organising the arangement of states and transitions in Program can be improved.

    - Random Examples (Folder): Just a bunch of random old files with examples of tikz code and pdf diagrams.
