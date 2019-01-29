# cryptologists_toolkit

Version 2

This update made the tool nicer to look at. 
There may stil be bugs that are unaccounted for, feel free to point them out if you find them.

The next update after this will include the vigener cipher and letter frequency analysis. 

The goal of the project is to document all of the broken ciphers. 

I don't recommend using these tools for your own cryptanalysis endevours as there already exist professional tools.

Change List:
	-Added header
	-Program now has a nice terminal feel to it
	-No more using the program directly from command line via argument vectors.

Bugs:
	-After executing a cipher command, there is a double print of the input prompt.
	-There may be memory leaks as this tool is still in its early stage. I don't reccomend using
		this outside of a virtual machine.
	-This has only been tested on Ubuntu. Any other Linux operating systems may have trouble 
		compiling the code. I attempted to stay within the POSIX standards

