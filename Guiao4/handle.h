#include "manipula_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

char* getToken(char *linha,char **rest);
STACK *doStack(char *line, char **rest, DATA *values);
char* doArrString (char* line, char **rest);
int pushSTR(STACK *s,char *token);
STACK *makeStack(char* line, DATA* values, STACK *s)
int val(STACK *s, char *token);
int handle(STACK *s,DATA *values, char *token);
int readinput(STACK *s,char *token);
int var(STACK* s, DATA *values, char *token);
void switchValValue(STACK *s, DATA *values, char n);
DATA *init_values(DATA values[]);
void parse(char *line);
