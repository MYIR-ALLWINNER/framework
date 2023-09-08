#ifndef UNICODEANDUTF8_H
#define UNICODEANDUTF8_H
#include <stdlib.h>
#include<assert.h>
#include<stdio.h>


int enc_get_utf8_size(const unsigned char pInput);

int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);

int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,int outSize);

#endif // UNICODEANDUTF8_H
