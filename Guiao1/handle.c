/*

Para que este ficheiro funcione corretamente, incluímos o ficheiro "handle.h"
onde foram declaradas as funções "val" e "handle".

*/


#include "handle.h"


/* 


A função "val" é do tipo "int" e recebe um apontador para a stack e 
um token. 


É declarada uma variável "val" onde será guardado o token, através do recurso
da função "sscanf".


Por fim, coloca o inteiro "val" no topo da stack, neste caso, no endereço
s.


Como esta função, como já referimos, é do tipo "int", tem que retornar um
inteiro, neste caso, 1.


*/


int val(STACK *s, char *token) {

	int val;
	sscanf(token, "%d" , &val);
	push(s,val);
	return 1;
}




/*


A função "handle" é do tipo "void", pelo que não retorna nenhum valor, e,
tal como a função "val", recebe um apontador para a stack e um token.


Esta função vai testando cada um dos operadores matemáticos.
Se aquilo que o utilizador inseriu não foi nenhum operador, foi um inteiro.


*/


void handle(STACK *s, char *token){

	(soma(s,token) || sub(s,token) || mult(s,token)
	 || dividir(s,token) || expoente(s,token) 
	 || decrementa(s,token)|| incrementa(s,token) || e(s,token)
	 || modulo(s,token) || ou(s,token) || e(s,token) || nao(s,token) || val(s,token));
    
}