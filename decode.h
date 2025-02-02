#pragma once
#ifndef _DECODE_H
#define _DECODE_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
void change_to_char(int byte, FILE* fp_o);
int decodef(char* in_file, char* out_file);
#endif
