#include "stack.h"


/*


A função "new_stack", é do tipo "STACK", ambas definidas no ficheiro
"stack.h", sendo que "STACK" é um tipo de estrutura que recebe um array
de inteiros, chamado "stack", com um certo comprimento e um apontador.


Esta, aloca num endereço um espaço de memória, tendo em conta o tamanho da
nossa stack.


*/




STACK *new_stack(){

	return (STACK *) malloc(sizeof(STACK));

}



/*

A função "push", já declarada no ficheiro "stack.h", é do tipo "void", pelo
que não retorna nenhum valor, recebe um apontador para a stack e um elemento
inteiro. 


Esta , coloca no topo da stack um elemento, resultante das operações 
matemáticas definidas no ficheiro "operadores.c".


*/

void push (STACK *s, int elem){

	s->sp++;
	s->stack[s->sp]=elem;

}



/*

A função "pop", já declarada no ficheiro "stack.h", é do tipo "int", pelo
que retorna um inteiro, neste caso, o valor da variável "ret", recebe um 
apontador para a stack. 


Esta função serve para "remover" da stack, o seu primeiro elemento, passando
a ser o primeiro, aquele que, originalmente, era o segundo.



*/

int pop(STACK *s) {

	int ret = s->stack[s->sp];
	s->sp--;
	return ret;

}