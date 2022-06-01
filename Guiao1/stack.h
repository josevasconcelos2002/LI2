#define MAX_STACK 10000
#include <stdlib.h>

/*Neste ficheiro são declaradas as funções referentes à stack, assim como a declaração da estrutura de dados "STACK" em si,
que representa uma stack de inteiros, assim como o seu sp(stack pointer) que aponta para a posição do ultimo elemento
colocado na mesma.
*/


typedef struct {

	int stack[MAX_STACK];
	int sp;

} STACK;


STACK *new_stack();
void push(STACK *s, int elem);
int pop(STACK *s);