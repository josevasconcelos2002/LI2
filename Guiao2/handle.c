/**
 * 
 * @Para que este ficheiro funcione corretamente, incluímos o ficheiro "handle.h" onde foram declaradas as funções "val" e "handle".
 * 
**/


#include "handle.h"


/** 
 * 
 * @A função "val" é do tipo "int" e recebe um apontador para a stack e um token. 
 * 
 * @É declarada uma variável "val" onde será guardado o token, através do recurso da função "sscanf".
 * 
 * @Por fim, coloca o inteiro "val" no topo da stack, neste caso, no endereço s.
 * 
 * @Como esta função, como já referimos, é do tipo "int", tem que retornar um inteiro, neste caso, 1.
 * 
**/


int val(STACK *s, char *token) {
	int r = 0;
	char *rest;
	long lnumber = strtol(token,&rest,10);      //->algum erro por esta parte do código, long number n conseguem ser respresentados//
	if(strlen(rest) == 0) {                     
		DATA elem;
		elem.type = LONG;
		elem.value.longValue = lnumber;
		push(s,elem);
		r = 1;
	}
	else {
		double dnumber = strtod(token,&rest);
		if(strlen(rest) == 0) {
			DATA elem;                            // double numbers a funcionarem corretamente//
			elem.type = DOUBLE;
			elem.value.doubleValue = dnumber;
			push(s,elem);
			r = 1;
		}
	}
	return r;
}


int readinput(STACK *s,char *token) {
	if(strcmp(token,"l") == 0) {
		char str[1024];
		if(fgets(str,1024,stdin)) {
		int length = strlen(str);
		DATA elem;
		elem.type = STR;
		elem.value.stringValue = strndup(str,length-1);
		push(s,elem);
		}
	}
	return 0;
}




/**
 * 
 * @A função "handle" é do tipo "void", pelo que não retorna nenhum valor, e, tal como a função "val", recebe um apontador para a stack e um token.
 * 
 * @Esta função vai testando cada um dos operadores matemáticos.
 * 
 * @Se aquilo que o utilizador inseriu não foi nenhum operador, foi um inteiro.
 * 
*/


int handle(STACK *s, char *token){

	 return (/*soma(s,token) || sub(s,token) || mult(s,token)
	 || dividir(s,token) || expoente(s,token) 
	 || decrementa(s,token)|| incrementa(s,token) || e(s,token)
	 || modulo(s,token) || ou(s,token) || e(s,token) || nao(s,token) 
	 || myxor(s,token) || */readinput(s,token)|| /*converte_int(s,token)
	 || converte_dbl(s,token) || converte_char(s,token) || converte_str(s,token)
	 || duplica(s,token)|| pop1(s,token) || troca2(s,token) || roda3(s,token)
	 || copia(s,token)  || */ val(s,token));
    
}
