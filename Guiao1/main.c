/*
Module      : Guião1_LEIPL8G05
Description : Implementação dos Operadores Matemáticos
Copyright   : José Pedro Torres Vasconcelos <a100763@alunos.uminho.pt>;
            : André Lima São Gil            <a93192@alunos.uminho.pt>;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle.h"


/*


A função "main" é do tipo "int", pelo que retorna um inteiro, neste caso, 0.

Esta, se aquilo que for lido, for diferente de "NULL", ou seja, se for 
inserido alguma coisa pela utilizador, ela chama a função "handle", definida
no ficheiro "handle.c", que vai "tratar" aquilo que é lido.



*/



int main(){

	STACK *s = new_stack();
	char line[BUFSIZ];
	char token[BUFSIZ];
	

	if(fgets(line,BUFSIZ, stdin)!= NULL) {
		
		while(sscanf(line,"%s%[^\n]", token , line) == 2){

			handle(s,token);

		}
		handle(s,token);

		for(int i = 1; i <= s->sp;i++){

			printf("%d",s->stack[i]);
			
		}
		printf("\n"); 	

	}


	return 0;

}
