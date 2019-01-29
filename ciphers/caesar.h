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

#define CAESAR_BUF_SIZE 1024

/*
 * Table-Based Caesar cipher shift
 */

struct Caesar_Data{
	int p_fd, c_fd;				/* plaintext and ciphertex file descriptors	*/
	off_t fileSize;
	ssize_t fileOptStatus;

	char charBuffer[CAESAR_BUF_SIZE];	/* char buffer for file data 			*/

	int p, c;				/* holds position of chars from asciiTable[TABLESIZE] */
	int offset;
	size_t f;				/* holds field size. Formated for use in bestModu()   */

};

int caesar_encrypt(char *ptr_targetFile, char *ptr_destinationFile){	
	struct Caesar_Data ces; /*caesar encrypt struct*/
	struct stat st;
	int security = 0;

	ces.p_fd = open(ptr_targetFile, O_RDONLY);
	if(ces.p_fd == -1){
		err(EBADF, "open");
		return -1;
	}
	
	/* stat file size */
	if(fstat(ces.p_fd, &st) == -1){
		err(EBADF, "stat");
		close(ces.p_fd);
		return -1;
	}
	ces.fileSize = st.st_size;
	
	if(ces.fileSize >= CAESAR_BUF_SIZE){
		ces.fileSize = CAESAR_BUF_SIZE-1;
		printf("\n[WW] file was too big, not enciphering full file.\n");
	}else if(ces.fileSize <= 0){
		err(EBADF, "Buffer underflow/empty file");
		close(ces.p_fd);
		return -1;
	}else{
		printf("%s has %ld bits\n", ptr_targetFile, (long)ces.fileSize);
	}

	/* read from fd */
	ces.fileOptStatus = pread(ces.p_fd, ces.charBuffer, (size_t)ces.fileSize, 0);
	if(ces.fileOptStatus == -1){
		err(EIO, "pread");
		close(ces.p_fd);
		return -1;
	}else if(ces.fileOptStatus < ces.fileSize){
		printf("Warning, partial read!\n");
	}else{
		printf("Read successuful!\n");
	}
	close(ces.p_fd);
	
	printf("Enter caesar offset (?)> ");
	scanf("%d", &ces.offset);
	ces.f = TABLESIZE-1;

	/* encipher */
	for(int i=0; i<ces.fileSize; i++){
		ces.c = getAsciiPosition(ces.charBuffer[i]);
		ces.c = bestModu((ces.c + ces.offset), ces.f);
		ces.charBuffer[i] = getAsciiChar(ces.c);
	}
	
	/* attempt to create outfile */
	ces.c_fd = open(ptr_destinationFile, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(ces.c_fd == -1){
		printf("File already exists.\n Are you sure you want to overwrite %s? (666)\n(?)> ", ptr_destinationFile);
		scanf("%d", &security);
		if(security != 666){
			printf("Exiting without overwriting %s\n", ptr_destinationFile);
			return -1;
		}

		ces.c_fd = open(ptr_destinationFile, O_TRUNC | O_RDWR);
		if(ces.c_fd == -1){
			err(EBADF, "open");
			return -1;
		}
	}

	ces.fileOptStatus = pwrite(ces.c_fd, ces.charBuffer, (size_t)ces.fileSize, 0);
	if(ces.fileOptStatus == -1 || ces.fileOptStatus > ces.fileSize){
		err(EIO, "pwrite");
		close(ces.c_fd);
		return -1;
	}else if(ces.fileOptStatus < ces.fileSize){
		printf("Partial write, some data may be missing.\n");
	}else{
		printf("Write Successful\n");
	}

	close(ces.c_fd);
	return 0;	
}

int caesar_decrypt(char *ptr_targetFile, char *ptr_destinationFile){
	struct Caesar_Data ces; /*caesar encrypt struct*/
        struct stat st;
        int security = 0;

        /* open ciphertext file for read */
        ces.c_fd = open(ptr_targetFile, O_RDONLY);
        if(ces.c_fd == -1){
                err(EBADF, "open");
                return -1;
        }

        /* stat file size */
        if(fstat(ces.c_fd, &st) == -1){
                err(EBADF, "stat");
                close(ces.c_fd);
                return -1;
        }
        ces.fileSize = st.st_size;

        if(ces.fileSize >= CAESAR_BUF_SIZE){
                ces.fileSize = CAESAR_BUF_SIZE-1;
                printf("\n[WW] file was too big, not enciphering full file.\n");
        }else if(ces.fileSize <= 0){
                err(EBADF, "Buffer underflow/empty file");
                close(ces.c_fd);
                return -1;
        }else{
                printf("%s has %ld bits\n", ptr_targetFile, (long)ces.fileSize);
        }

        /* read from fd */
        ces.fileOptStatus = pread(ces.c_fd, ces.charBuffer, (size_t)ces.fileSize, 0);
        if(ces.fileOptStatus == -1){
                err(EIO, "pread");
                close(ces.c_fd);
                return -1;
        }else if(ces.fileOptStatus < ces.fileSize){
                printf("Warning, partial read!\n");
        }else{
                printf("Read successuful!\n");
        }
        close(ces.c_fd);

        printf("Enter caesar offset (?)> ");
        scanf("%d", &ces.offset);
        ces.f = TABLESIZE-1;

        /* encipher */
        for(int i=0; i<ces.fileSize; i++){
                ces.p = getAsciiPosition(ces.charBuffer[i]);
                ces.p = bestModu((ces.p - ces.offset), ces.f);
                ces.charBuffer[i] = getAsciiChar(ces.p);
        }

        /* attempt to create outfile */
        ces.p_fd = open(ptr_destinationFile, O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if(ces.p_fd == -1){
                printf("File already exists.\n Are you sure you want to overwrite %s? (666)\n(?)> ", ptr_destinationFile);
                scanf("%d", &security);
                if(security != 666){
                        printf("Exiting without overwriting %s\n", ptr_destinationFile);
                        return -1;
                }

                ces.p_fd = open(ptr_destinationFile, O_TRUNC | O_RDWR);
                if(ces.p_fd == -1){
                        err(EBADF, "open");
                        return -1;
                }
        }

        ces.fileOptStatus = pwrite(ces.p_fd, ces.charBuffer, (size_t)ces.fileSize, 0);
        if(ces.fileOptStatus == -1 || ces.fileOptStatus > ces.fileSize){
                err(EIO, "pwrite");
                close(ces.p_fd);
                return -1;
        }else if(ces.fileOptStatus < ces.fileSize){
                printf("Partial write, some data may be missing.\n");
        }else{
                printf("Write Successful\n");
        }
        close(ces.p_fd);

        return 0;
}

/* You either understand or you don't */
int caesar_crack(char *ptr_targetFile){
	printf("\n~Table Based Brute Force Attack~\n");

	int done = 0;
	int count = 0;
	struct Caesar_Data ces; /*caesar encrypt struct*/
        struct stat st;
        int security = 0;

        /* open ciphertext file for read */
        ces.c_fd = open(ptr_targetFile, O_RDONLY);
        if(ces.c_fd == -1){
                err(EBADF, "open");
                return -1;
        }

        /* stat file size */
        if(fstat(ces.c_fd, &st) == -1){
                err(EBADF, "stat");
                close(ces.c_fd);
                return -1;
        }
        ces.fileSize = st.st_size;

        if(ces.fileSize >= CAESAR_BUF_SIZE){
                ces.fileSize = CAESAR_BUF_SIZE-1;
                printf("\n[WW] file was too big, not enciphering full file.\n");
        }else if(ces.fileSize <= 0){
                err(EBADF, "Buffer underflow/empty file");
                close(ces.c_fd);
                return -1;
        }else{
                printf("%s has %ld bits\n", ptr_targetFile, (long)ces.fileSize);
        }

        /* read from fd */
        ces.fileOptStatus = pread(ces.c_fd, ces.charBuffer, (size_t)ces.fileSize, 0);
        if(ces.fileOptStatus == -1){
                err(EIO, "pread");
                close(ces.c_fd);
                return -1;
        }else if(ces.fileOptStatus < ces.fileSize){
                printf("Warning, partial read!\n");
        }else{
                printf("Read successuful!\n");
        }
        close(ces.c_fd);

	ces.offset = 1;
	ces.f = TABLESIZE-1;
	printf("Total Posible Shifts [%d]\n", TABLESIZE-1);
	while(!done){
		count++;
		for(int i=0; i<ces.fileSize; i++){
                	ces.c = getAsciiPosition(ces.charBuffer[i]);
               		ces.c = bestModu((ces.c + ces.offset), ces.f);
        	        ces.charBuffer[i] = getAsciiChar(ces.c);
        	}
		printf("Text: \n\n%s\n\n", ces.charBuffer);

		printf("Was the cipher cracked(1)?\n(?)> ");
		scanf("%d", &security);
		if(security == 1){
			done = 1;
		}else if(count == TABLESIZE){
			return -1;
		}else{
			printf("round %d of %d\n", count, TABLESIZE-1);
		}
	}
	return 0;
}
