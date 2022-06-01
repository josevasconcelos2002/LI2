#include "stack.h"
#include <stdio.h>

/**
 * 
 * @A função "new_stack", é do tipo "STACK", ambas definidas no ficheiro
"stack.h", sendo que "STACK" é um tipo de estrutura que recebe um array
de inteiros, chamado "stack", com um certo comprimento e um apontador.
 *
 *
 * @Esta, aloca num endereço um espaço de memória, tendo em conta o tamanho da
nossa stack.
 *
*/




STACK *new_stack(){

	STACK *s = (STACK *) malloc(sizeof(STACK));
	s->sp = 0;
	s->size = 100;
	s->stack = (DATA *) calloc(s->size,sizeof(DATA));
}






/**
 * 
 * @A função "push", já declarada no ficheiro "stack.h", é do tipo "void", pelo
que não retorna nenhum valor, recebe um apontador para a stack e um elemento
inteiro. 
 *
 * @Esta , coloca no topo da stack um elemento, resultante das operações 
matemáticas definidas no ficheiro "operadores.c".
 *
*/


void push (STACK *s, DATA elem){
	if(isFull(s)) {
		s->size+=100;
		s->stack = (DATA *) realloc(s->stack,s->size*sizeof(DATA));
	}
	s->stack[s->sp]= elem;
	s->sp++;
}



/**
 * 
 * @A função "pop", já declarada no ficheiro "stack.h", é do tipo "int", pelo
que retorna um inteiro, neste caso, o valor da variável "ret", recebe um 
apontador para a stack. 
 *
 * @Esta função serve para "remover" da stack, o seu primeiro elemento, passando
a ser o primeiro, aquele que, originalmente, era o segundo.
 *
*/

DATA pop(STACK *s) {

	DATA ret = s->stack[s->sp];
	s->sp--;
	return ret;

}

int isEmpty(STACK *s) {
	return (s->sp == 0);
}

int isFull(STACK *s) {
	return (s->sp == s->size);
}

void printStack(STACK *s) {
	int i=0;
	DATA elem;
	while(i<s->sp) {
		elem = s->stack[i];
		
	
		if((elem.type) == DOUBLE) {
		printf("%g",elem.value.doubleValue);
		}
		else {
			if(elem.type == LONG) {
				printf("%ld",elem.value.longValue);
			}
			else {
				if(elem.type == CHAR) {
					printf("%c",elem.value.charValue);
				}
				else {
					int j=0;
					while(elem.value.stringValue[j]) {
						printf("%c",elem.value.stringValue[j]);
						j++;
					}
				}
			}
		}
	i++;
	}
}


int has_type(DATA elem, int mask) {

	return(elem.type & mask);

}