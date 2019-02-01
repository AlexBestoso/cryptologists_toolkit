#include "headers/standardHeaders.h"
#include "headers/bestMath.h"
#include "headers/textTables.h"
#include "ciphers/caesar.h"
#include "ciphers/affine.h"
#include "crackers/LetterFreq.h"

#define CMD_MAX 128
#define MAX_FILE_NAME 128
/*
 * This is here because it looks cool :)
 */
void printHeader(void){
	printf(" ___                        _           _                           _         \n");
	printf("(  _`\\                     ( )_        (_ )                _       ( )_       \n");
	printf("| ( (_) _ __  _   _  _ _   | ,_)   _    | |    _      __  (_)  ___ | ,_)  ___ \n");
	printf("| |  _ ( \'__)( ) ( )( \'_`\\ | |   /\'_`\\  | |  /\'_`\\  /\'_ `\\| |/\',__)| |  /\',__)\n");
	printf("| (_( )| |   | (_) || (_) )| |_ ( (_) ) | | ( (_) )( (_) || |\\__, \\| |_ \\__, \\\n");
	printf("(____/\'(_)   `\\__, || ,__/\'`\\__)`\\___/\'(___)`\\___/\'`\\__  |(_)(____/`\\__)(____/\n");
	printf("             ( )_| || |                            ( )_) |                    \n");
	printf("             `\\___/\'(_)                             \\___/\'                    \n");
	printf(" _____              _    _         _                                          \n");
	printf("(_   _)            (_ ) ( )     _ ( )_                                        \n");
	printf("  | |   _      _    | | | |/\') (_)| ,_)                                       \n");
	printf("  | | /\'_`\\  /\'_`\\  | | | , <  | || |                                         \n");
	printf("  | |( (_) )( (_) ) | | | |\\`\\ | || |_                                        \n");
	printf("  (_)`\\___/\'`\\___/'(___)(_) (_)(_)`\\__)                                       \n");
	printf("\n");
	printf("\n");
}

int main(int argc, char *argv[]){
	Boolean fini = False;
	Boolean optionPressed = False;
	Boolean targetPtrUsed = False;
	Boolean destinationPtrUsed = False;
	int simp_input;
	char cmd[CMD_MAX];
	char *cmd_ptr;
	int cmd_size;

	char targetFile[MAX_FILE_NAME];
        char destinationFile[MAX_FILE_NAME];
        
	char *ptr_targetFile;
        char *ptr_destinationFile;

        int targetFileCount=0, oldTargetFileCount=0;
        int destinationFileCount=0, oldDestinationFileCount=0;

	/*
	 * for the looks
	 */
	system("clear");
	printHeader();	
	
	while(fini == False){	
		if(optionPressed == False){	
			printf("\n(CTK)> ");
		}	
		memset(cmd, '\0', CMD_MAX);
		if(fgets(cmd, CMD_MAX, stdin) == NULL){
			err(EIO, "fgets");
			exit(EXIT_FAILURE);
		}
		cmd_size = 0;
		for(int i=0; i<CMD_MAX; i++){
			if(cmd[i] == '\0'){
				i=CMD_MAX+1;
			}else{
				cmd_size++;
			}
		}

		if(cmd_size > 0 && cmd_size < CMD_MAX)
			cmd[cmd_size] = '\0';

		cmd_ptr = malloc(cmd_size*sizeof(char));
		memset(cmd_ptr, '\0', cmd_size);
		if(cmd_ptr != NULL){
			for(int i=0; i<cmd_size-1; i++){
				*(cmd_ptr+i) = cmd[i];
			}
		}
		
		if(!strcmp(cmd_ptr, "exit\0")){
			fini = True;

		}else if(!strcmp(cmd_ptr, "caesar\0")){
			printf("Enter Target File:\n");
			printf("(caesar)> ");
			memset(targetFile, '\0', MAX_FILE_NAME);
			if(fgets(targetFile, MAX_FILE_NAME, stdin) == NULL){
				err(EIO, "fgets");
			}else{
				printf("Target File: %s\n", targetFile);
				targetFileCount = 0;
				for(int i=0; i<MAX_FILE_NAME; i++){
					if(targetFile[i] == '\0'){
						i=MAX_FILE_NAME+1;
					}else{
						targetFileCount++;
					}
				}

				if(targetFileCount < MAX_FILE_NAME && targetFileCount > 0)
					targetFile[targetFileCount] = '\0';
				

				if(targetPtrUsed == False){
					ptr_targetFile = malloc(targetFileCount*sizeof(char));
					oldTargetFileCount = targetFileCount;
					targetPtrUsed = True;

				}else if(targetFileCount != oldTargetFileCount){
					ptr_targetFile = realloc(ptr_targetFile, targetFileCount*sizeof(char));
					oldTargetFileCount = targetFileCount;
				}
				memset(ptr_targetFile, '\0', targetFileCount);
				if(ptr_targetFile != NULL)
					for(int i=0; i<targetFileCount-1; i++)
						*(ptr_targetFile+i) = targetFile[i];
			}

			printf("Enter Destination File(type anything if you\'re cracking the cipher):\n");
			printf("(caesar)> ");
			memset(destinationFile, '\0', MAX_FILE_NAME);
			if(fgets(destinationFile, MAX_FILE_NAME, stdin) == NULL){
				err(EIO, "fgets");
			}else{
				printf("Destination File: %s\n", destinationFile);
				destinationFileCount = 0;
				for(int i=0; i<MAX_FILE_NAME; i++){
					if(destinationFile[i] == '\0'){
						i=MAX_FILE_NAME+1;
					}else{
						destinationFileCount++;
					}
				}

				if(destinationFileCount < MAX_FILE_NAME && destinationFileCount > 0)
					destinationFile[destinationFileCount] = '\0';
				

				if(destinationPtrUsed == False){
					ptr_destinationFile = malloc(destinationFileCount*sizeof(char));
					oldDestinationFileCount = destinationFileCount;
					destinationPtrUsed = True;

				}else if(destinationFileCount != oldDestinationFileCount){
					ptr_destinationFile = realloc(ptr_destinationFile, destinationFileCount*sizeof(char));
					oldDestinationFileCount = destinationFileCount;
				}	
				
				memset(ptr_destinationFile, '\0', destinationFileCount);

				if(ptr_destinationFile != NULL)
					for(int i=0; i<destinationFileCount-1; i++)
						*(ptr_destinationFile+i) = destinationFile[i];
			}

			printf("Are you,\n\t (1)Encrypting\n\t (2)Decrypting\n\t (3)Cracking\n(caesar)> ");
			scanf("%d", &simp_input);
			if(simp_input == 1){
				if(ptr_targetFile == NULL || ptr_destinationFile == NULL)
					printf("Null pointer, not encrypting\n");
				else
					caesar_encrypt(ptr_targetFile, ptr_destinationFile);
			}else if(simp_input == 2){
				if(ptr_targetFile == NULL || ptr_destinationFile == NULL)
                                        printf("Null pointer, not decrypting\n");
				else
					caesar_decrypt(ptr_targetFile, ptr_destinationFile);
			}else if(simp_input == 3){
				if(ptr_targetFile == NULL)
					printf("Null pointer, not cracking\n");
				else
					caesar_crack(ptr_targetFile);
			}else{
				printf("invalid option\n");
			}

			optionPressed = True;

		}else if(!strcmp(cmd_ptr, "affine\0")){
			printf("Enter Target File:\n");
                        printf("(affine)> ");
			memset(targetFile, '\0', MAX_FILE_NAME);
                        if(fgets(targetFile, MAX_FILE_NAME, stdin) == NULL){
                                err(EIO, "fgets");
                        }else{
                                printf("Target File: %s\n", targetFile);
                                targetFileCount = 0;
                                for(int i=0; i<MAX_FILE_NAME; i++){
                                        if(targetFile[i] == '\0'){
                                                i=MAX_FILE_NAME+1;
                                        }else{
                                                targetFileCount++;
                                        }
                                }

				if(targetFileCount < MAX_FILE_NAME && targetFileCount > 0)
	                                targetFile[targetFileCount] = '\0';
				
				if(targetPtrUsed == False){
                                	ptr_targetFile = malloc(targetFileCount*sizeof(char));
					oldTargetFileCount = targetFileCount;
					targetPtrUsed = True;

				}else if(targetFileCount != oldTargetFileCount){
					ptr_targetFile = realloc(ptr_targetFile, targetFileCount*sizeof(char));
					oldTargetFileCount = targetFileCount;
				}
				
				memset(ptr_targetFile, '\0', targetFileCount);

				if(ptr_targetFile != NULL)
                                	for(int i=0; i<targetFileCount-1; i++)
                                        	*(ptr_targetFile+i) = targetFile[i];
			}

			printf("Enter Destination File(type anything if you\'re cracking the cipher):\n");
                        printf("(affine)> ");
			memset(destinationFile, '\0', MAX_FILE_NAME);
                        if(fgets(destinationFile, MAX_FILE_NAME, stdin) == NULL){
                                err(EIO, "fgets");
                        }else{
                                printf("Destination File: %s\n", destinationFile);
                                destinationFileCount = 0;
                                for(int i=0; i<MAX_FILE_NAME; i++){
                                        if(destinationFile[i] == '\0'){
                                                i=MAX_FILE_NAME+1;
                                        }else{
                                                destinationFileCount++;
                                        }
                                }

				if(destinationFileCount < MAX_FILE_NAME && destinationFileCount > 0)
	                                destinationFile[destinationFileCount] = '\0';
				
				if(destinationPtrUsed == False){
	                                ptr_destinationFile = malloc(destinationFileCount*sizeof(char));
					oldDestinationFileCount = destinationFileCount;
					destinationPtrUsed = True;

				}else if(destinationFileCount != oldDestinationFileCount){
					ptr_destinationFile = realloc(ptr_destinationFile, destinationFileCount*sizeof(char));
					oldDestinationFileCount = destinationFileCount;
				}

				memset(ptr_destinationFile, '\0', destinationFileCount);			
	
				if(ptr_destinationFile != NULL)
                                	for(int i=0; i<destinationFileCount-1; i++)
                                        	*(ptr_destinationFile+i) = destinationFile[i];
                        
			}
                        printf("Are you,\n\t (1)Encrypting\n\t (2)Decrypting\n\t (3)Cracking\n(affine)> ");
                        scanf("%d", &simp_input);
                        if(simp_input == 1){
				if(ptr_targetFile == NULL || ptr_destinationFile == NULL)
					printf("Null pointer, not encrypting\n");
				else
                                	affine_encrypt(ptr_targetFile, ptr_destinationFile);
                        }else if(simp_input == 2){
				if(ptr_targetFile == NULL || ptr_destinationFile == NULL)
                                        printf("Null pointer, not decrypting\n");
				else
                                	affine_decrypt(ptr_targetFile, ptr_destinationFile);
                        }else if(simp_input == 3){
				if(ptr_targetFile == NULL)
                                        printf("Null pointer, not cracking\n");
				else
					affine_crack(ptr_targetFile);
                        }else{
                                printf("invalid option\n");
                        }

                        optionPressed = True;

		}else if(!strcmp(cmd_ptr, "LFA\0")){
			printf("Letter Frequency analysis\n\nEnter Target File\n");
			printf("(LFA)> ");
			memset(targetFile, '\0', MAX_FILE_NAME);
			if(fgets(targetFile, MAX_FILE_NAME, stdin) == NULL){
				err(EIO, "fgets");
			}else{
				printf("target file: %s\n", targetFile);
				targetFileCount = 0;
				for(int i=0; i<MAX_FILE_NAME; i++){
					if(targetFile[i] == '\0'){
						i=MAX_FILE_NAME+1;
					}else{
						targetFileCount++;
					}
				}

				if(targetFileCount < MAX_FILE_NAME && targetFileCount > 0)
					targetFile[targetFileCount] = '\0';


				if(targetPtrUsed == False){
					ptr_targetFile = malloc(targetFileCount*sizeof(char));
					targetPtrUsed = True;
					oldTargetFileCount = targetFileCount;

				}else if(targetFileCount != oldTargetFileCount){
					ptr_targetFile = realloc(ptr_targetFile, targetFileCount*sizeof(char));
					oldTargetFileCount = targetFileCount;
				}
				
				memset(ptr_targetFile, '\0', targetFileCount);

				if(ptr_targetFile != NULL)
					for(int i=0; i<targetFileCount-1; i++)
						*(ptr_targetFile+i) = targetFile[i];
				
			}	

			letterFrequencyAnalysis(ptr_targetFile);
			//optionPressed = True;

		}else if(!strcmp(cmd_ptr, "clear\0")){
			system("clear");
			printHeader();
		
		}else if(!strcmp(cmd_ptr, "help\0")){
			printf("commands:\n");
			printf("\texit\n");
			printf("\tcaesar\n");
			printf("\taffine\n");
			printf("\tLFA\n");
			printf("\tclear\n");
			printf("\thelp\n");
		
		}else if(optionPressed == False){
			printf("Invalid command, type help\n");
			printf("%s\n", cmd_ptr);
		}else{
			optionPressed = False;
		}

		if(cmd_ptr)
			free(cmd_ptr);
		cmd_ptr = NULL;
	}

	if(targetPtrUsed == True)
		if(ptr_targetFile)
			free(ptr_targetFile);
	
	if(destinationPtrUsed == True)
		if(ptr_destinationFile)
			free(ptr_destinationFile);

	exit(EXIT_SUCCESS);
}
