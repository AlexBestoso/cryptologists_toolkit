/*
 * This Program was created by Alexander J. Bestoso
 * You, the downloader, can utilize this tool in what
 * ever way you want, assuming the use is within the
 * confines of the law. 
 *
 * This tool is NOT intended to be used as an elite hacker
 * weapon.
 *
 * This tool is NOT intended to be used as a means of 
 * securitng data of any kind.
 *
 * This tool IS intended to help advance your cryptology 
 * skills in a way that's not a direct attack on someones
 * communications.
 *
 * Abusing this tool for cracking communications or building 
 * ransomeware will leave you in the hands of law enforcement. 
 *
 * Be smart, safe, and have fun!
 *
 * Leave this notice in this file else we assume you intend to
 * break the law.
 */


#define TABLESIZE 70

/* 
 * shift table 
 */
char asciiTable[TABLESIZE] = {
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
				'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
				'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
				'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 
				'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', 
				'3', '4', '5', '6', '7', '8', '9', '!', '?', ',', '.',
				'\'', ' ', '\n', '\0'
			     };


/* 
 * returns the position of the requested char
 */
int getAsciiPosition(char buf){
	for(int i=0; i<TABLESIZE; i++){
		if(asciiTable[i] == '\0'){
			printf("Tried to encrypt unsupported char: %c, returning 1", buf);
			return 1;
		}else if(buf == asciiTable[i]){
			return i;
		}
	}
	printf("bad value, returning 1\n");
	return 1;
}

/*
 * returns the char of the requested position
 */
char getAsciiChar(int buf){
	if(buf > TABLESIZE || buf < 0){
		printf("Bad value %d[%c], returning A\n", buf, (char)buf);
		return 'A';
	}else{
		return asciiTable[buf];
	}
	printf("undefined error in getTableChar\n");
	return 'A';
}

