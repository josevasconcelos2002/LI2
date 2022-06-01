#include <stdlib.h>
#include <stdio.h>
#include "types.h"




/**
 * 
 * @Neste ficheiro são declaradas as funções referentes à stack
que representa uma stack de inteiros, assim como o seu sp(stack pointer) que aponta para a posição do ultimo elemento
colocado na mesma.
 *
*/



STACK *new_stack();
int has_type(DATA elem, int mask);
void push(STACK *s, DATA elem);
DATA pop(STACK *s);
int isEmpty(STACK *s);
int isFull(STACK *s);
void printStack(STACK *s);
void printArray(STACK *s);