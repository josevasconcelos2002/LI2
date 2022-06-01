/**
 * @Module      : Guião2_LEIPL8G05
 * @Description : Manipulação da stack, conversão de tipos e leitura com o comando I
 * @Copyright   : 
 * @             José Pedro Torres Vasconcelos <a100763@alunos.uminho.pt>;
 * @             André Lima São Gil            <a93192@alunos.uminho.pt>;
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle.h"


/**  
 *\brief Função, que, se aquilo que for lido, for diferente de "NULL", ou seja, se for 
 *inserido alguma coisa pela utilizador, ela chama a função "handle", definida
 *no ficheiro "handle.h", que vai "tratar" aquilo que é lido.
 *
 *@returns 0.
 */
int main(){

	STACK *s = new_stack();
	char line[BUFSIZ];
	char token[BUFSIZ];
	DATA values[26];
	int i;
	for(i = 0;i<26;i++) {
		values[i].type = LONG;
	}
	values['S' - 'A'].type = values['N' - 'A'].type = CHAR;
	values['S' - 'A'].value.charValue = ' '; 
	values['N' - 'A'].value.charValue = '\n';
	values['A' - 'A'].value.longValue = 10; 
	values['B' - 'A'].value.longValue = 11; 
	values['C' - 'A'].value.longValue = 12;
	values['D' - 'A'].value.longValue = 13;
	values['E' - 'A'].value.longValue = 14;
	values['F' - 'A'].value.longValue = 15;
	values['X' - 'A'].value.longValue = 0;
	values['Y' - 'A'].value.longValue = 1;
	values['Z' - 'A'].value.longValue = 2;
	

	if(fgets(line,BUFSIZ, stdin)!= NULL) {
		
		while(sscanf(line,"%s%[^\n]", token , line) == 2){
			handle(s,values,token);
		}
		handle(s,values,token);
		printStack(s);
		printf("\n"); 	
	}

 return 0;
}