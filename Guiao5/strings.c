#include <string.h>
#include "strings.h"



int str(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,/*"""*/) == 0) {   // como colocar """ (?) ... inicia a string


								// while token != """ (?) string

	return r;
	}

 else return r;	
}





int str_length(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,",") == 0) {
		DATA res;
		DATA x = pop(s);
		if(has_type(x,STR)) {
			res.type = LONG;
			STR a = x.value.stringValue;
			res.value.longValue = strlen(a);
			push(s,res);
			r = 1;
		}

	 return r;
	}

 else return r; 
}

int sub_str(STACK *s, char *token) {

	if(strcmp(token,"#") == 0) {
		DATA res;
		DATA x = pop(s);
		if(has_type(x,STR)) {                //procura uma sub string... se econtrar, devolve o índice, otherwise, return (-1)
			res.type = LONG;
			STR a = x.value.stringValue;
			if(/*encontra a sub string*/) {
				res.value.longValue = /*índice da sub string*/;
				push(s,res);
			}
			else {
			res.value.longValue = -1; // se não encontra, devolve -1
			push(s,res);
			}
		
		}

	 return 1;
	}

 else return 0; 
}