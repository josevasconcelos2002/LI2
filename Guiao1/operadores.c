#include "operadores.h"
#include <string.h>

/*Função que faz um bitwise not do ultimo elemento colocado na stack. 
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int nao(STACK *s, char *token) {
    if(strcmp(token,"~") == 0) {
        int Z = pop(s);
        push(s,~Z);    
    }
    else return 0;
}


/*Função que faz bitwise xor dos dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int myxor(STACK *s, char *token) {

	if(strcmp(token,"^") == 0) {
		int Z = pop(s);
		int W = pop(s);
		push(s,Z^W);
		return 1;
	}
	else return 0;
}


/*Função que faz bitwise or dos dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int ou(STACK *s, char *token){ 
	
	if(strcmp(token,"|") == 0) {

		int Z = pop(s);
		int W = pop(s);
		push(s,Z|W);	
		return 1;
	}

	else return 0;
}


/*Função que faz bitwise and dos dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int e(STACK *s, char *token){
	
	if(strcmp(token,"&") == 0) {  //?Pode ser usado o & original ou nos temos de fazer as bitwise operations

		int Z = pop(s);
		int W = pop(s);
		push(s,Z&W);
		return 1;
	}

	else return 0;
}


/*Função que calcula a exponenciação dos dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int expoente(STACK *s, char *token){
	
	if(strcmp(token,"#") == 0) {

		int Z = pop(s);
		int W = pop(s);
		push(s, pow(W,Z));         /*Utilizar -lm ao compilar*/
		return 1;
	}

	else return 0;
}


/*Função que incrementa 1 ao ultimo elemento colocado na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" devolva 1
*/

int incrementa(STACK *s, char *token){
	
	if(strcmp(token,")") == 0) {

		int Z = pop(s);
		push(s, ++Z );
		return 1;
	}

	else return 0;
}



/*Função que subtrai 1 ao ultimo elemento colocado na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int decrementa(STACK *s, char *token){
	
	if(strcmp(token,"(") == 0) {

		int Z = pop(s);
		push(s, --Z);
		return 1;
	}

	else return 0;
}


/*Função que calcula o resto da divisão dos ultimos dois elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int modulo(STACK *s, char *token){
	
	if(strcmp(token,"%") == 0) {
		
		int Z = pop(s);
		int W = pop(s);
		push(s, W%Z);
		return 1;
	}

	else return 0;
}


/*Função que calcula a divisão inteira dos dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int dividir(STACK *s, char *token){
	
	if(strcmp(token,"/") == 0) {

		int Z = pop(s);
		int W = pop(s);
		push(s, W/Z);
		return 1;
	}

	else return 0;
}


/*Função que multiplica os dois ultimos elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int mult(STACK *s, char *token){
	
	if(strcmp(token,"*") == 0) {

		int Z = pop(s);
		int W = pop(s);
		push(s,Z*W);
		return 1;
	}

	else return 0;
}


/*Função que calcula a diferença entre os ultimos dois elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int sub(STACK *s, char *token){
	
	if(strcmp(token,"-") == 0) {

		int Z = pop(s);
		int W = pop(s);
		push(s,W - Z);
		return 1;
	}

	else return 0;
}



/*Função que calcula a soma entre os ultimos dois elementos colocados na stack.
Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
*/

int soma(STACK *s, char *token){
	
	if(strcmp(token,"+") == 0){
		
		int X = pop(s);
		int Y = pop(s);
		push(s, X + Y);
		return 1;
	
	}

	else return 0;

}
