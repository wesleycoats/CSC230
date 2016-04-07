/**
  @file des.h
  @author Wesley Coats wrcoats
  
  The header file for des.c
*/

/**
  Encrypts an 8 byte block using the 8 byte key given as the second parameter
  When it is done it stores the result in the 8 byte block given as the first parameter
  
  @param unsigned char *block the 8 byte block to be encrypted
  @param const unsigned char *key the key used for encryption
*/
void encrypt_block(unsigned char *block, const unsigned char *key);

/**
  Decrypts an 8 byte block using the 8 byte key given as the second parameter
  When it is done it stores the result in the 8 block byte given as the first parameter
  
  @param unsigned char *block the 8 byte block to be decrypted
  @param const unsigned char *key the key used for decryption
*/
void decrypt_block(unsigned char *block, const unsigned char *key);