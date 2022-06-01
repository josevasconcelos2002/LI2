#include "arrays.h"




int arr(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"[") == 0) {      //inicia o array
		while(token != "]")
                                      // while token != "]" , colocar dentro do array
	
	}	
	return r;

 else return r;
}


int push_elementos_arr(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"~") == 0) {
		DATA x = pop(s);
		if(has_type(x,ARR)) {
			ARR a = x.value.Value; // arrValue(?)
			while(a[i] != NULL) {
				push(s,a[i]);
				i++;
			}
			
		 r = 1;
		}

	 return r;
	}

 else return r;	
}


int indice(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"=") == 0) {
		DATA res;
		DATA x = pop(s); // indice
		DATA y = pop(s); // array
		if(has_type(x,LONG) && (has_type(y,ARR))) {
			LONG a = x.value.longValue;
			res.type = //type dos elementos do array
			res.value.//type dos elementos = y[x];
			push(s,res);
			r = 1;
		}

	  return r;
	}

 else return r;
}