#include "manipula_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


int val(STACK *s, char *token);
int handle(STACK *s,DATA *values, char *token);
int readinput(STACK *s,char *token);
int readinput(STACK *s,char *token);
int var(STACK* s, DATA *values, char *token);
void switchValValue(STACK *s, DATA *values, char n);
char* strndup(char const*,size_t n);