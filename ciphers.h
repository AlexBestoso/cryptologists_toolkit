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

/* cipher macros */
#define CAESAR 		0
#define AFFINE 		1
#define VIGENERE 	2

/* mode macros */
#define ENCRYPT  0
#define DECRYPT  1
#define CRACK    2
#define MODE_ERR 3

#include "cipherBank/caesar.h"
#include "cipherBank/vigenere.h"

#include "cipherBank/affine.h"
