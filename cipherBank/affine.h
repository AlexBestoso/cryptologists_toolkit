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


#define AFFINE_BUF_SIZE 1024

struct Affine_Data{
	int p_fd, c_fd;
	int p, c, offset, coprime;
	
	char fileBuffer[AFFINE_BUF_SIZE];
	char stateBuffer[AFFINE_BUF_SIZE];

	ssize_t fileOptStatus;
	size_t f;
	off_t fileSize;
};

int affine_encrypt(char *argv[]){
	struct Affine_Data afes;
	struct stat st;
	int security = 0;
	signed int EA_ret;      /*Euclidean algorith return*/

	/* Open from plaintext file */
	afes.p_fd = open(argv[3], O_RDONLY);
	if(afes.p_fd == -1){
		err(EBADF, "open");
		return -1;
	}

	/* get status */
	if(fstat(afes.p_fd, &st) == -1){
		close(afes.p_fd);
		err(EBADF, "fstat");
		return -1;
	}

	afes.fileSize = st.st_size;
	
	/* check for over flow */
	if(afes.fileSize >= AFFINE_BUF_SIZE){
		afes.fileSize = AFFINE_BUF_SIZE - 1;
		printf("[WW] File size was too big, some data may be missing\n");

	}else if(afes.fileSize <= 0){
		close(afes.p_fd);
		printf("Buffer underflow or empty file\n");
		return -1;

	}else{
		printf("%s has %ld bits", argv[3], (long)afes.fileSize);
	}

	/* read from file */
	afes.fileOptStatus = pread(afes.p_fd, afes.fileBuffer, (size_t)afes.fileSize, 0);
	if(afes.fileOptStatus == -1){
		close(afes.p_fd);
		err(EIO, "pread");
		return -1;
	
	}else if(afes.fileOptStatus < afes.fileSize){
		printf("Partial read, some data may be missing\n");
	}else{
		printf("Read Success\n");
	}
	close(afes.p_fd);
	
	/* get user input*/
	printf("Enter an offset\n(?)> ");
	scanf("%d", &afes.offset);

	printf("Select coprime value:\n");
        for(int i=0; i<TABLESIZE-1; i++){
                EA_ret  = bestEuclideanAlgo(TABLESIZE-1, i);
		if(EA_ret == 1)
			printf("\tcoprime: %d\n", i);
        }
	printf("(?)> ");
	scanf("%d", &afes.coprime);

	/* encipher buffer*/
	for(int i=0; i<afes.fileSize; i++){
		afes.c = getAsciiPosition(afes.fileBuffer[i]);
		afes.c = bestModu((afes.coprime * afes.c) + afes.offset, (size_t)(TABLESIZE-1));
		afes.fileBuffer[i] = getAsciiChar(afes.c);
	}
	
	/*create else open and trunc ciphertext file*/
	afes.c_fd = open(argv[4], O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(afes.c_fd == -1){
		printf("%s will be emptied, are you sure you want to continue? (666)\n(?)> ", argv[4]);
		scanf("%d", &security);
		if(security != 666){
			printf("Your data is safe\n");
			return -1;
		}

		afes.c_fd = open(argv[4], O_RDWR | O_TRUNC);
		if(afes.c_fd == -1){
			err(EBADF, "open");
			return -1;
		}
		
	}
	
	/*write to file*/
	afes.fileOptStatus = pwrite(afes.c_fd, afes.fileBuffer, (size_t)afes.fileSize, 0);
	if(afes.fileOptStatus == -1 || afes.fileOptStatus > afes.fileSize){
		close(afes.c_fd);
		err(EIO, "pwrite [%ld]", (long)afes.fileOptStatus);
		return -1;
	
	}else if(afes.fileOptStatus < afes.fileSize){
		printf("Partial write, some data may be missing\n");
	}else{
		printf("Write Successful\n");
	}

	close(afes.c_fd);

	return 0;
}

int affine_decrypt(char *argv[]){
	struct Affine_Data afes;
        struct stat st;
        int security = 0;
        signed int MI_ret;      /*Multiplacitve Inverse return*/

	/* Open ciphertext file */
	afes.c_fd = open(argv[3], O_RDONLY);
        if(afes.c_fd == -1){
                err(EBADF, "open");
                return -1;
        }

	/* get status */
	if(fstat(afes.c_fd, &st) == -1){
                close(afes.c_fd);
                err(EBADF, "fstat");
                return -1;
        }

        afes.fileSize = st.st_size;

	/* check for overflow */
	if(afes.fileSize >= AFFINE_BUF_SIZE){
                afes.fileSize = AFFINE_BUF_SIZE - 1;
                printf("[WW] File size was too big, some data may be missing\n");

        }else if(afes.fileSize <= 0){
                close(afes.c_fd);
                printf("Buffer underflow or empty file\n");
                return -1;

        }else{
                printf("%s has %ld bits", argv[3], (long)afes.fileSize);
        }

	/* read from file*/
	afes.fileOptStatus = pread(afes.c_fd, afes.fileBuffer, (size_t)afes.fileSize, 0);
        if(afes.fileOptStatus == -1){
                close(afes.c_fd);
                err(EIO, "pread");
                return -1;

        }else if(afes.fileOptStatus < afes.fileSize){
                printf("Partial read, some data may be missing\n");

        }else{
                printf("Read Success\n");
        }
        close(afes.c_fd);

	/* get user input*/
	printf("Enter an offset\n(?)> ");
        scanf("%d", &afes.offset);

        printf("Select coprime value:\n(?)> ");
        scanf("%d", &afes.coprime);

	/* decipher */
	afes.coprime = bestMultiInvers(TABLESIZE-1, afes.coprime);
	if(afes.coprime == -1){
		err(EIO, "bestMultiInverse");
		return -1;
	}
	for(int i=0; i<afes.fileSize; i++){
                afes.p = getAsciiPosition(afes.fileBuffer[i]);
                afes.p = bestModu(afes.coprime * (afes.p - afes.offset), (size_t)(TABLESIZE-1));
                afes.fileBuffer[i] = getAsciiChar(afes.p);
        }

	/* create/truncate out file*/
	afes.p_fd = open(argv[4], O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(afes.p_fd == -1){
                printf("%s will be emptied, are you sure you want to continue? (666)\n(?)> ", argv[4]);
                scanf("%d", &security);
                if(security != 666){
                        printf("Your data is safe\n");
                        return -1;
                }

                afes.p_fd = open(argv[4], O_RDWR | O_TRUNC);
                if(afes.p_fd == -1){
                        err(EBADF, "open");
                        return -1;
                }

        }
	/* write to file */
	afes.fileOptStatus = pwrite(afes.p_fd, afes.fileBuffer, (size_t)afes.fileSize, 0);
        if(afes.fileOptStatus == -1 || afes.fileOptStatus > afes.fileSize){
                close(afes.p_fd);
                err(EIO, "pwrite [%ld]", (long)afes.fileOptStatus);
                return -1;

        }else if(afes.fileOptStatus < afes.fileSize){
                printf("Partial write, some data may be missing\n");
        }else{
                printf("Write Successful\n");
        }

        close(afes.p_fd);

	/* done */
	return 0;
}

int affine_crack(char *argv[]){
	struct Affine_Data afes;
        struct stat st;
	int option = 0, incrementI=0, incrementII=0;
	int input = 1;
	int done = 1;
	size_t coeff_count = 0;
	int EA_ret;
	int *coeffArray_ptr;
	int totalRounds, round=0;

	/* Open ciphertext file */
        afes.c_fd = open(argv[3], O_RDONLY);
        if(afes.c_fd == -1){
                err(EBADF, "open");
                return -1;
        }

        /* get status */
        if(fstat(afes.c_fd, &st) == -1){
                close(afes.c_fd);
                err(EBADF, "fstat");
                return -1;
        }

        afes.fileSize = st.st_size;

        /* check for overflow */
        if(afes.fileSize >= AFFINE_BUF_SIZE){
                afes.fileSize = AFFINE_BUF_SIZE - 1;
                printf("[WW] File size was too big, some data may be missing\n");

        }else if(afes.fileSize <= 0){
                close(afes.c_fd);
                printf("Buffer underflow or empty file\n");
                return -1;

        }else{
                printf("%s has %ld bits", argv[3], (long)afes.fileSize);
        }

        /* read from file*/
        afes.fileOptStatus = pread(afes.c_fd, afes.fileBuffer, (size_t)afes.fileSize, 0);
        if(afes.fileOptStatus == -1){
                close(afes.c_fd);
                err(EIO, "pread");
                return -1;

        }else if(afes.fileOptStatus < afes.fileSize){
                printf("Partial read, some data may be missing\n");

        }else{
                printf("Read Success\n");
        }
        close(afes.c_fd);
	
/*Cracking starts here*/
	printf("Select Crack Option\n\tBrute Force(1)\n\tLetter Frequency Analysis(not finneshed yet)\n(?)> ");
	scanf("%d", &option);
	
	switch(option){
		case 0:/* letter frequency*/ 
			return -1;
			break;

		case 1: /* brute force*/	
			printf("Affine - Table Based Brute Forece Attack\n\n");

			/* get coprime count*/
			for(int i=0; i<TABLESIZE-1; i++){
         		        EA_ret = bestEuclideanAlgo(TABLESIZE-1, i);
                		if(EA_ret == 1)
					coeff_count++;	
        		}

			/* fill array with all coprime values*/

			if(coeff_count == 0){
                                return -1;
                        }

			totalRounds = (TABLESIZE-1)*coeff_count;
			
			coeffArray_ptr = malloc(coeff_count+1);

			for(int i=0; i<TABLESIZE-1; i++){
				EA_ret = bestEuclideanAlgo(TABLESIZE-1, i);
				if(EA_ret == 1 && (incrementI <= coeff_count && incrementI >= 0)){
					coeffArray_ptr[incrementI] = i;
					incrementI++;
				}	
			}
			
			coeffArray_ptr[coeff_count] = '\0';
			
			/* print coprimes*/
			printf("possible coprime values:\n");
			for(int i=0; i<coeff_count; i++){
				if((i%5) == 0)
					printf("\n");

				/* ensure no buffer over/underflows */
				if(i <= coeff_count && i >= 0)
					printf("%d ", coeffArray_ptr[i]);
			}
			
			printf("Text file, pre-crack:\n%s\n\n", afes.fileBuffer);		
	
			incrementI = 0; /* used to increment through multiplicative inverse*/
			incrementII = 1; /* used to increment through offsets*/
			afes.offset = incrementII;
			afes.coprime = coeffArray_ptr[incrementI];
			afes.coprime = bestMultiInvers(TABLESIZE-1, afes.coprime);

			while(done != 0){
				printf("\n\tround %d of %d\n", round, totalRounds);
				printf("\tkeys: coprime inverse(%d) | offset(%d)\n", afes.coprime, afes.offset);

				/*decipher*/
				for(int i=0; i<afes.fileSize; i++)
					afes.stateBuffer[i] = afes.fileBuffer[i];

				for(int i=0; i<afes.fileSize; i++){
                			afes.p = getAsciiPosition(afes.stateBuffer[i]);
                			afes.p = bestModu(afes.coprime * (afes.p - afes.offset), (size_t)(TABLESIZE-1));
                			afes.stateBuffer[i] = getAsciiChar(afes.p);
        			}

				/*print results and get user feed back*/
				printf("Result:\n\n%s\n\nIs this correct?\n(1) yes\n(2) no\n(3) exit\n(?)> ", afes.stateBuffer);
				scanf("%d", &input);

				/*operate relative to input*/

				if(input == 1){/*yes*/
					done = 0;

				}else if(input == 3){
					printf("Exiting...\n");
                                        done = 0;
				}else{/*no*/
					done = 1;
					incrementII++; /*increment offset*/
					if(incrementII >= TABLESIZE){/*if offset is out of table range*/
						incrementII=1;	/*set offset to 1*/
						incrementI++;	/*increment coprime array position*/
						if(incrementI >= coeff_count+1){/* if position exceeds amount of coprimes*/
							printf("Code cracking failed\n");
							free(coeffArray_ptr);
							done=0;
							return -1;
						}
					}
					afes.offset = incrementII;/*set next offset - linear*/
					afes.coprime = coeffArray_ptr[incrementI];/*set next coprime - may be the same*/
					afes.coprime = bestMultiInvers(TABLESIZE-1, afes.coprime);
				}
				round++;
			}

			free(coeffArray_ptr);
			
			break;	
		default:

			break;
	}
	if(input != 1){
		return -1;
	}else{
		return 0;
	}
}
