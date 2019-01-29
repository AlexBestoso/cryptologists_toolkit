# cryptologists_toolkit

Version 2

0) This update made the tool nicer to look at. 
There may stil be bugs that are unaccounted for, feel free to point them out if you find them.

1) The next update after this will include the vigener cipher and letter frequency analysis. 

2) The goal of the project is to document all of the broken ciphers. 

3) I don't recommend using these tools for your own cryptanalysis endevours as there already exist professional tools.

Change List:
	-Fixed memory leak by adding realloc()
	-Fixed double print of prompt, though fgets may still get called twice after selecting cipher.

I'm still looking for more bugs. After I finish more research on cryptanalysis, I'll be adding the what's mentioned in point 1)
