#include "arrayStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/**
 * 
 * @Neste ficheiro, "handle.h", são declaradas as funções "val" e "handle", que são do tipo "int" e "void", respetivamente.
 * 
 * @Estas recebem o apontador para a stack e ambas são usadas no ficheiro "handle.c".
 * 
*/


int val(STACK *s, char *token);
int handle(STACK *s, DATA *values, char *token);
int readinput(STACK *s,char *token);
void parse(char *linha);
int var(STACK* s, DATA *values, char *token);
void switchValValue(STACK *s, DATA *values, char n);
STACK *doStack(char *line, char **rest, DATA *values);
STACK *makeStack(char* line, DATA *values, STACK *s);
char* doArrString (char* line, char **rest);
