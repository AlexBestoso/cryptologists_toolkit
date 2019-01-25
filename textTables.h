#define TABLESIZE 70
#define LOWERTABLESIZE 27

char asciiTable[TABLESIZE] = {
				'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
				'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
				'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
				'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 
				'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', 
				'3', '4', '5', '6', '7', '8', '9', '!', '?', ',', '.',
				'\'', ' ', '\n', '\0'
			     };

char lower_asciiTable[LOWERTABLESIZE] = {
					   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
					   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
					   'u', 'v', 'w', 'x', 'y', 'z', '\0'
					};
/*
 * Normal table functions
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

/*
 * lower case table functions
 */
int getLowerAsciiPosition(char buf){
        for(int i=0; i<LOWERTABLESIZE; i++){
                if(lower_asciiTable[i] == '\0'){
                        printf("Tried to encrypt unsupported char: %c, returning 1", buf);
                        return 1;
                }else if(buf == lower_asciiTable[i]){
                        return i;
                }
        }
        printf("bad value, returning 1\n");
        return 1;
}

char getLowerAsciiChar(int buf){
        if(buf > LOWERTABLESIZE || buf < 0){
                printf("Bad value %d[%c], returning A\n", buf, (char)buf);
                return 'A';
        }else{
                return lower_asciiTable[buf];
        }
        printf("undefined error in getLowerTableChar\n");
        return 'A';
}
