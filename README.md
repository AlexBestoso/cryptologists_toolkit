# cryptologists_toolkit

Version 2

There is now a basic Letter Frequency Analysis tool.
I supplied an example ciphertext to test it with, taken from a book :)

Future updates will include a vigenère cipher and will remove useless LFA functions. 
The LFA command will also be given a "save progress" funtionality which will let the cracked ciphertext be saved.

bugs:
you can't do the ctrl+shift+c copy short cut (i think), last I tried, it canceled out the program. Storing the output to a file should restore the progress.

potential logic bug regarding malloc and memset. fix will include moving the memset() into the if(ptr_ != NULL) statement.
