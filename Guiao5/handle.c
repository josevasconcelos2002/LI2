/**
 * 
 * @Para que este ficheiro funcione corretamente, incluímos o ficheiro "handle.h" onde foram declaradas as funções "val" e "handle".
 * 
**/


#include "handle.h"

char* strndup(char const*,size_t n);

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

void switchValValue(STACK *s, DATA *values, char n) {
	DATA x = pop(s);
	values[n - 'A'].type = x.type;
	if(has_type(x,LONG)) {
		values[n - 'A'].value.longValue = x.value.longValue;
	}

	else if(has_type(x,DOUBLE)) {
		values[n - 'A'].value.doubleValue = x.value.doubleValue;
		 }

		 else if(has_type(x,CHAR)) {
			 	 values[n - 'A'].value.charValue = x.value.charValue;
		 	  }

			  else if(has_type(x,STR)) {
					   values[n - 'A'].value.stringValue = x.value.stringValue;
		 		   }

  push(s,x);
}


int var(STACK* s, DATA *values, char *token) {
	int r = 0;
	if(strlen(token) == 1 && isupper(*token)) {
		push(s,values[*token - 'A']);
		r = 1;
	}

	else if(strlen(token) == 2 && token[0] == ':' && isupper(token[1])) {
		switchValValue(s,values,token[1]);
		r = 1;
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


/**
 * 
 * @A função "handle" é do tipo "void", pelo que não retorna nenhum valor, e, tal como a função "val", recebe um apontador para a stack e um token.
 * 
 * @Esta função vai testando cada um dos operadores matemáticos.
 * 
 * @Se aquilo que o utilizador inseriu não foi nenhum operador, foi um inteiro.
 * 
*/


int handle(STACK *s, DATA* values,  char *token){

	 return (soma(s,token) || sub(s,token) || mult(s,token)
	 || dividir(s,token) || expoente(s,token) 
	 || decrementa(s,token)|| incrementa(s,token) || e(s,token)
	 || modulo(s,token) || ou(s,token) || e(s,token) || nao(s,token) 
	 || myxor(s,token) || readinput(s,token)|| converte_int(s,token)
	 || converte_dbl(s,token) || converte_char(s,token) || converte_str(s,token)
	 || duplica(s,token)|| mypop(s,token) || troca2(s,token) || roda3(s,token)
	 || copia(s,token)  || igual(s,token)  || menor(s,token)  || maior(s,token)  || nao_logico(s,token)  || e_short(s,token)  || ou_short(s,token) 
	 || push_m(s,token)  || push_M(s,token) || if_then_else(s,token) || var(s,values,token)  || val(s,token));
    
}
