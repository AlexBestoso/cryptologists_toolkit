# cryptologists_toolkit

Version 2

<<<<<<< HEAD
0) This update made the tool nicer to look at. 
There may stil be bugs that are unaccounted for, feel free to point them out if you find them.

1) The next update after this will include the vigener cipher and letter frequency analysis. 
=======
This update made the tool nicer to look at. 
There may still be bugs that are unaccounted for, feel free to point them out if you find them.

The next update after this will include the vigenère cipher and letter frequency analysis.
>>>>>>> 959194c7fc0e70da75fa0d2dbdf98a71b307bf38

2) The goal of the project is to document all of the broken ciphers. 

<<<<<<< HEAD
3) I don't recommend using these tools for your own cryptanalysis endevours as there already exist professional tools.

Change List:
	-Fixed memory leak by adding realloc()
	-Fixed double print of prompt, though fgets may still get called twice after selecting cipher.

I'm still looking for more bugs. After I finish more research on cryptanalysis, I'll be adding the what's mentioned in point 1)
=======
I don't recommend using these tools for your own cryptanalysis endeavours as there already exist professional tools.

Change List:
	-Added header
	-Program now has a nice terminal feel to it
	-No more using the program directly from command line via argument vectors.

Bugs:
	-After executing a cipher command, there is a double print of the input prompt.
	-There may be memory leaks as this tool is still in its early stage. I don't reccomend using
		this outside of a virtual machine.
		
Update ~ [Works outside of virtual machine]
>>>>>>> 959194c7fc0e70da75fa0d2dbdf98a71b307bf38
