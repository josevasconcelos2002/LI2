#include "stack.h"
#include <stdio.h>




STACK *new_stack(){

	STACK *s = (STACK *) malloc(sizeof(STACK));
	s->sp = -1;
	s->size = 100;
	s->stack = (DATA *) calloc(s->size,sizeof(DATA));
	return s;
	
}




void push (STACK *s, DATA elem){
	if(isFull(s)) {
		s->size+=100;
		s->stack = (DATA *) realloc(s->stack,s->size*sizeof(DATA));
	}
	s->sp++;
	s->stack[s->sp]= elem;
	
}


DATA pop(STACK *s) {

	DATA ret;
	ret = s->stack[s->sp--];
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
	DATA a;
	while(i <= s->sp) {
		a = s->stack[i];
		
		
	
		if(has_type(a,LONG)) 
				printf("%ld",a.value.longValue);
		
		else if(has_type(a,DOUBLE)) 
				printf("%g",a.value.doubleValue);
		
		else if(has_type(a,CHAR)) 
				printf("%c",a.value.charValue);
				
		else if(has_type(a,STR)) 
				printf("%s",a.value.stringValue);

		else if(has_type(a,ARR)) 
				printStack(a.value.arrayValue);	

		
		i++;
		}
	
}




int has_type(DATA elem, int mask) {

	return(elem.type & mask)!= 0;

}
