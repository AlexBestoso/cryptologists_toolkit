typedef enum {FALSE, TRUE} Boolean;

#include <errno.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include "bestMath.h"
#include "textTables.h"
#include "ciphers.h"

unsigned int cipherPicker(char *argv[]){
	if(!strcmp(argv[1], "caesar") || !strcmp(argv[1], "Caesar") || !strcmp(argv[1], "ceasar") || !strcmp(argv[1], "Ceasar")){
		return CAESAR;	
	
	}else if(!strcmp(argv[1], "affine") || !strcmp(argv[1], "Affine")){
		return AFFINE;
	
	}else if(!strcmp(argv[1], "vigenere") || !strcmp(argv[1], "Vigenere")){
		return VIGENERE;
	}

	/* defaults to caesar cipher on undefined error */
	return CAESAR;
}

unsigned int modePicker(char *argv[]){
	if(!strcmp(argv[2], "encrypt") || !strcmp(argv[2], "e") || !strcmp(argv[2], "Encrypt") || !strcmp(argv[2], "encipher")){
		return ENCRYPT;
	}else if(!strcmp(argv[2], "decrypt") || !strcmp(argv[2], "d") || !strcmp(argv[2], "Decrypt") || !strcmp(argv[2], "decipher")){
		return DECRYPT;
	}else if(!strcmp(argv[2], "crack") || !strcmp(argv[2], "c") || !strcmp(argv[2], "Crack")){
		return CRACK;
	}
	return MODE_ERR;
}

int main(int argc, char *argv[]){
	if(argc == 4 && !strcmp(argv[2], "crack")){
		asm("nop");	
	}else if(argc == 2 && !strcmp(argv[1], "--list-ciphers")){
                        printf("Available ciphers:\n");
			printf("caesar\n");
			printf("affine\n");
                        exit(EXIT_FAILURE);

        }else if(argc != 5 || !strcmp(argv[1], "-help")){
		err(EINVAL, "Proper Usage: %s [cipher name] [encrypt/decrypt/crack] [in file] [outfile]\n\t--list-ciphers\n\t-help\n", argv[0]);	
		exit(EXIT_FAILURE);
	}
	
	switch(cipherPicker(argv)){
		case CAESAR:
			if(modePicker(argv) == ENCRYPT){
				printf("Caesar Cipher ~ Encryption\n");
				if(caesar_encrypt(argv) == -1){
					printf("Encryption Failed >:(\n");
					exit(EXIT_FAILURE);
				}else{
					printf("Encryption Success c:\n");
					exit(EXIT_SUCCESS);
				}
			}else if(modePicker(argv) == DECRYPT){
				printf("Caesar Cipher ~ Decryption\n");
				if(caesar_decrypt(argv) == -1){
					printf("Decryption Failed >:(\n");
					exit(EXIT_FAILURE);
				}else{
					printf("Decryption Success c:\n");
					exit(EXIT_SUCCESS);
				}
			}else if(modePicker(argv) == CRACK){
				printf("Caesar Cipher ~ Cracker\n");
				if(caesar_crack(argv) == -1){
					printf("Crack Failed :p\n");
					exit(EXIT_FAILURE);
				}else{
					printf("Crack Success :o\n");
					exit(EXIT_SUCCESS);
				}
			}else{	
				err(EINVAL, "modePicker returned an invalid value, bad argument");
				exit(EXIT_FAILURE);
			}
			break;
			
		case AFFINE:
			if(modePicker(argv) == ENCRYPT){
				printf("Affine Cipher ~ Encryption\n");
				if(affine_encrypt(argv) == -1){
					printf("Encryption Failed >:(\n");
					exit(EXIT_FAILURE);

				}else{
					printf("Encryption Success c:\n");
					exit(EXIT_SUCCESS);
				}
			}else if(modePicker(argv) == DECRYPT){
				printf("Affine Cipher ~ Decryption\n");
				if(affine_decrypt(argv) == -1){
					printf("Decryption Failed >:(\n");
					exit(EXIT_FAILURE);
				}else{
					printf("Decryption Success c:\n");
					exit(EXIT_SUCCESS);
				}
			}else if(modePicker(argv) == CRACK){
				printf("Affine Cipher ~ Cracker");
				if(affine_crack(argv) == -1){
					printf("Crack Failed :p\n");
					exit(EXIT_FAILURE);
				}else{
					printf("Crack Success :o\n");
					exit(EXIT_SUCCESS);
				}
			}else{
				err(EINVAL, "modePicker returned an invalid value, bad argument");
                                exit(EXIT_FAILURE);
			}
			printf("This Cipher is broken, as in, you can't decrypt with the current setup\n");
			break;	

		case VIGENERE:
			printf("do it\n");
			break;	
		default:
			err(EDOM, "cipherPicker");	
			exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
