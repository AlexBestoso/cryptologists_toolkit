#define F_A 0
#define F_B 1
#define F_C 2
#define F_D 3
#define F_E 4
#define F_F 5
#define F_G 6
#define F_H 7
#define F_I 8
#define F_J 9
#define F_K 10
#define F_L 11
#define F_M 12
#define F_N 13
#define F_O 14
#define F_P 15
#define F_Q 16
#define F_R 17
#define F_S 18
#define F_T 19
#define F_U 20
#define F_V 21
#define F_W 22
#define F_X 23
#define F_Y 24
#define F_Z 25
#define F_NULL 26

#define E_FREQ_TABLE_SIZE 27
#define FILEBUFMAX 1025

const double englishFrequencyTable[E_FREQ_TABLE_SIZE] =  {
						0.0817, 0.0150, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015,
						0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.0010, 0.0599, 0.0633, 0.0906,
						0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007, '\0'
							 };

const char englishAlphabet[E_FREQ_TABLE_SIZE] = {
							'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
							'p', 'q', 'r', 's', 't', 'u',  'v', 'w', 'x', 'y', 'z', '\0'
						};

double getFrequency(char buffer[FILEBUFMAX], size_t size, char letter){
	double ret = 0.0;
	double charCount = 0.0;
	if(size > 0 && size <= FILEBUFMAX){
		for(int i=0; i<size; i++){
			if(buffer[i] == letter){
				charCount = charCount + 1;
			}
		}
	}else{
		return 0.0;
	}

	if(size != 0)
		ret = charCount / size;
	
	return ret;
}

double getRFD(double *frequencyTable, int size){
	double ret = 0.0;
	double large;
	
	if(frequencyTable == NULL || size != E_FREQ_TABLE_SIZE){
		return -1;
	}else{
		large = frequencyTable[0];
		for(int i=1; i<E_FREQ_TABLE_SIZE-1; i++){
			if(frequencyTable[i] > large){
				large = frequencyTable[i];
			}
		}
		ret = large-englishFrequencyTable[F_E];
		if(ret < 0){
			ret = ret * -1;
		}	
		printf("RFD: %lf\n", ret);
	}
	return ret;
}

void swapFreqs(double *freqBuff){
	double values[2];
	char char_posI[10];
	char char_posII[10];
	int  int_posI;
	int  posIgot = 0;
	int  int_posII;
	int posIIgot = 0;

	printf("Enter Letter 1:\n(LFA)> ");
	if(fgets(char_posI, 10, stdin) != NULL){
		
		/*consume unwanted newline*/
		fgets(char_posII, 1, stdin);

		printf("Enter letter 2:\n(LFA)> ");
		if(fgets(char_posII, 10, stdin) != NULL){
			for(int i=0; i<E_FREQ_TABLE_SIZE; i++){
				if(englishAlphabet[i] == char_posI[0]){
					int_posI = i;
					posIgot = 1;
					i = E_FREQ_TABLE_SIZE+1;
				}else if(posIgot == 0){
					int_posI = -1;
				}
			}

			for(int i=0; i<E_FREQ_TABLE_SIZE; i++){
				if(englishAlphabet[i] == char_posII[0]){
					int_posII = i;
					posIIgot = 1;
					i = E_FREQ_TABLE_SIZE+1;
				
				}else if(posIIgot == 0){
					int_posII = -1;
				}
			}

			if((int_posI >= 0 && int_posII < 27) && (int_posII >= 0 && int_posII < 27)){
				values[0] = freqBuff[int_posI];
				values[1] = freqBuff[int_posII];

				freqBuff[int_posI] = values[1];
				freqBuff[int_posII] = values[0];
			}
		}
	}
}

void calcPlaintext(char *c, char *p, const size_t maxSize){
	char cipherChar[10];
	char plainChar[10];
	
	printf("Enter Target Char\n(LFA)> ");
	if(fgets(cipherChar, 10, stdin) != NULL){
		/* handle unwanted newline*/
		fgets(plainChar, 1, stdin);

		printf("Enter Replacement Char\n(LFA)> ");
		if(fgets(plainChar, 10, stdin) != NULL){
			for(int i=0; i<maxSize; i++){
				if(c[i] == cipherChar[0]){
					p[i] = plainChar[0];

				}else if(c[i] == plainChar[0]){
					p[i] = cipherChar[0];
				}else{
					p[i] = c[i];
				}
			}
		}
	}
}

int letterFrequencyAnalysis(char *filename){
	double encipheredFrequencyTable[E_FREQ_TABLE_SIZE];
	double new_encipheredFrequencyTable[E_FREQ_TABLE_SIZE];
		memset(new_encipheredFrequencyTable, '0', E_FREQ_TABLE_SIZE);
	struct stat st;
	const size_t max_file_size = FILEBUFMAX;
	size_t readAmount=0;
	size_t post_readAmount;
	char fileBuffer[max_file_size];
		memset(fileBuffer, '\0', max_file_size);
	char plaintext[max_file_size]; 
	char new_plaintext[max_file_size];
		memset(plaintext, '\0', max_file_size);
		memset(new_plaintext, '\0', max_file_size);
	int fd;

	char cmd[128];
	char *ptr_cmd;
	size_t cmd_char_count = 0;
	size_t old_cmd_char_count = 0;

	/* relative frequency difference */
	double rfd = 0;

	Boolean cracking = True;

	if((fd=open(filename, O_RDONLY)) == -1){
		err(EBADF, "open");
		return -1;
	}

	if(fstat(fd, &st) == -1){
		close(fd);
		err(EBADF, "fstat");
		return -1;
	}

	if(st.st_size <= 0){
		close(fd);
		printf("underflow/empty file\n");
		return -1;
	
	}else if(st.st_size >= max_file_size){
                readAmount = max_file_size-1;
		printf("File too big, some data may not be read\n");

        }else{
		readAmount = st.st_size;
	}

	post_readAmount = pread(fd, fileBuffer, readAmount, 0);
	if(post_readAmount <= 0){
		close(fd);
		err(EIO, "pread");
		return -1;
	}else if(post_readAmount < readAmount){
		printf("read semi-successful\n");
	}else{
		printf("read successful\n");
	}
	close(fd);

	for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
		if(post_readAmount > 0 && post_readAmount < max_file_size-1){
			encipheredFrequencyTable[i] = getFrequency(fileBuffer, post_readAmount, englishAlphabet[i]);
		}
	}

	rfd = getRFD(encipheredFrequencyTable, E_FREQ_TABLE_SIZE);
	if(rfd == -1){
		err(EIO, "getRFD");
		return -1;
	}

	for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
        	new_encipheredFrequencyTable[i] = encipheredFrequencyTable[i];
        }

	for(int i=0; i<max_file_size; i++){
        	plaintext[i] = fileBuffer[i];
        }

	while(cracking == True){
		printf("(LFA)> ");
		memset(cmd, '\0', 128);
		if(fgets(cmd, 128, stdin) == NULL){
			err(EIO, "fgets");
			cracking = False;
			return -1;
		}

		cmd_char_count = 0;
		for(int i=0; i<128; i++){
			if(cmd[i] == '\0'){
				i=128+1;
			}else{
				cmd_char_count++;
			}
		}

		if(cmd_char_count > 0 && cmd_char_count < 128)
			cmd[cmd_char_count] = '\0';

		ptr_cmd = malloc(cmd_char_count*sizeof(char));
		memset(ptr_cmd, '\0', cmd_char_count);

		if(ptr_cmd != NULL)
			for(int i=0; i<cmd_char_count-1; i++)
				*(ptr_cmd+i) = cmd[i];
		
		/*printf("ptr: [%s][%p]\n", ptr_cmd, ptr_cmd);*/
		if(!strcmp(ptr_cmd, "exit")){
			cracking = False;
			return 0;
		
		}else if(!strcmp(ptr_cmd, "clear")){
			system("clear");
			printf("Letter Frequency Analysis\n\n");

		}else if(!strcmp(ptr_cmd, "freq view")){
			for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
				printf("[%c]\t[%lf]\t[%lf]\n", englishAlphabet[i], encipheredFrequencyTable[i], englishFrequencyTable[i]);
			}
			printf("\n");

		}else if(!strcmp(ptr_cmd, "freq view new")){
			for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
                                printf("[%c]\t[%lf]\t[%lf]\n", englishAlphabet[i], new_encipheredFrequencyTable[i], englishFrequencyTable[i]);
                        }
                        printf("\n");

		}else if(!strcmp(ptr_cmd, "freq swap")){
			for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
                                printf("[%c]\t[%lf]\t[%lf]\n", englishAlphabet[i], new_encipheredFrequencyTable[i], englishFrequencyTable[i]);
                        }
                        printf("\n");
			swapFreqs(new_encipheredFrequencyTable);

		}else if(!strcmp(ptr_cmd, "freq calc")){
			for(int i=0; i<E_FREQ_TABLE_SIZE-1; i++){
                		if(post_readAmount > 0 && post_readAmount < max_file_size-1){
                        		new_encipheredFrequencyTable[i] = getFrequency(new_plaintext, post_readAmount, englishAlphabet[i]);
                		}
        		}

		}else if(!strcmp(ptr_cmd, "ciphertext")){
			printf("\n");
			for(int i=0; i<max_file_size; i++){
				if(fileBuffer[i] == '\0'){
					i=max_file_size+1;
				}else{
					printf("%c", fileBuffer[i]);
				}
			}
			printf("\n");
		}else if(!strcmp(ptr_cmd, "plaintext")){
			printf("\n");
			for(int i=0; i<max_file_size; i++){
                                if(new_plaintext[i] == '\0'){
                                        i=max_file_size+1;
                                }else{
                                        printf("%c", new_plaintext[i]);
                                }
                        }
                        printf("\n");

		}else if(!strcmp(ptr_cmd, "calc plaintext")){	
			printf("\n");
			for(int i=0; i<max_file_size; i++){
                                if(new_plaintext[i] == '\0'){
                                        i=max_file_size+1;
                                }else{
                                        printf("%c", new_plaintext[i]);
                                }
                        }
                        printf("\n");
			
			calcPlaintext(plaintext, new_plaintext, max_file_size);
			
			for(int i=0; i<max_file_size; i++){
				plaintext[i] = new_plaintext[i];
			}

		}else{
			printf("LFA Commands:\n");
			printf("\texit\n");
			printf("\tclear\n");
			printf("\tfreq view\n");
			printf("\tfreq view new\n");
			printf("\tfreq swap\n");
			printf("\tfreq calc\n");
			printf("\tciphertext\n");
			printf("\tplaintext\n");
			printf("\tcalc plaintext\n");
		}
		

		if(ptr_cmd)
                	free(ptr_cmd);
                ptr_cmd = NULL;	
	}

	return 0;
}
