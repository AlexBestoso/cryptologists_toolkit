#include "headers/standardHeaders.h"
#include "headers/bestMath.h"
#include "headers/textTables.h"
#include "ciphers/caesar.h"
#include "ciphers/affine.h"

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
	int simp_input;
	char cmd[CMD_MAX];
	char *cmd_ptr;
	int cmd_size;

	char targetFile[MAX_FILE_NAME];
        char destinationFile[MAX_FILE_NAME];
        
	char *ptr_targetFile;
        char *ptr_destinationFile;

        int targetFileCount = 0;
        int destinationFileCount = 0;

	/*
	 * for the looks
	 */
	system("clear");
	printHeader();	
	
	while(fini == False){	
		printf("\n(CTK)> ");
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
		cmd[cmd_size] = '\0';

		cmd_ptr = malloc(cmd_size*sizeof(char));
		for(int i=0; i<cmd_size-1; i++){
			*(cmd_ptr+i) = cmd[i];
		}

		if(!strcmp(cmd_ptr, "exit\0")){
			fini = True;

		}else if(!strcmp(cmd_ptr, "caesar\0")){
			printf("Enter Target File:\n");
			printf("(caesar)> ");
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
				targetFile[targetFileCount] = '\0';

				ptr_targetFile = malloc(targetFileCount*sizeof(char));
				for(int i=0; i<targetFileCount-1; i++)
					*(ptr_targetFile+i) = targetFile[i];
			}

			printf("Enter Destination File(type anything if you\'re cracking the cipher):\n");
			printf("(caesar)> ");
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
				destinationFile[destinationFileCount] = '\0';

				ptr_destinationFile = malloc(destinationFileCount*sizeof(char));
				for(int i=0; i<destinationFileCount-1; i++)
					*(ptr_destinationFile+i) = destinationFile[i];
			}

			printf("Are you,\n\t (1)Encrypting\n\t (2)Decrypting\n\t (3)Cracking\n(caesar)> ");
			scanf("%d", &simp_input);
			if(simp_input == 1){
				caesar_encrypt(ptr_targetFile, ptr_destinationFile);
			}else if(simp_input == 2){
				caesar_decrypt(ptr_targetFile, ptr_destinationFile);
			}else if(simp_input == 3){
				caesar_crack(ptr_targetFile);
			}else{
				printf("invalid option\n");
			}

			ptr_targetFile = NULL;
			ptr_destinationFile = NULL;
			optionPressed = True;

		}else if(!strcmp(cmd_ptr, "affine\0")){
			printf("Enter Target File:\n");
                        printf("(affine)> ");
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
                                targetFile[targetFileCount] = '\0';

                                ptr_targetFile = malloc(targetFileCount*sizeof(char));
                                for(int i=0; i<targetFileCount-1; i++)
                                        *(ptr_targetFile+i) = targetFile[i];
                        }

			printf("Enter Destination File(type anything if you\'re cracking the cipher):\n");
                        printf("(affine)> ");
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
                                destinationFile[destinationFileCount] = '\0';

                                ptr_destinationFile = malloc(destinationFileCount*sizeof(char));
                                for(int i=0; i<destinationFileCount-1; i++)
                                        *(ptr_destinationFile+i) = destinationFile[i];
                        }

                        printf("Are you,\n\t (1)Encrypting\n\t (2)Decrypting\n\t (3)Cracking\n(affine)> ");
                        scanf("%d", &simp_input);
                        if(simp_input == 1){
                                affine_encrypt(ptr_targetFile, ptr_destinationFile);
                        }else if(simp_input == 2){
                                affine_decrypt(ptr_targetFile, ptr_destinationFile);
                        }else if(simp_input == 3){
                                affine_crack(ptr_targetFile);
                        }else{
                                printf("invalid option\n");
                        }

                        ptr_targetFile = NULL;
                        ptr_destinationFile = NULL;
                        optionPressed = True;

		}else if(!strcmp(cmd_ptr, "clear\0")){
			system("clear");
			printHeader();
		}else if(!strcmp(cmd_ptr, "help\0")){
			printf("commands:\n");
			printf("\texit\n");
			printf("\tcaesar\n");
			printf("\taffine\n");
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
	exit(EXIT_SUCCESS);
}
