#include "operadores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * 
 * @Neste ficheiro, "handle.h", são declaradas as funções "val" e "handle", que são do tipo "int" e "void", respetivamente.
 * 
 * @Estas recebem o apontador para a stack e ambas são usadas no ficheiro "handle.c".
 * 
*/


int val(STACK *s, char *token);
int handle(STACK *s, char *token);
int readinput(STACK *s,char *token);