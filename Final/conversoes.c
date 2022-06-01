#include "conversoes.h"



int converte_int(STACK *s, char *token) {
	
	int r = 0;
	if(strcmp(token,"i") == 0) {
		
		DATA res;
		res.type = LONG;
		DATA elem = pop(s);
		if(has_type(elem,LONG)) {
			
			res.value.longValue = elem.value.longValue;
			push(s,res);
			r=1;

		}
	    else if(has_type(elem,DOUBLE)) {
				
				res.value.longValue = (long)elem.value.doubleValue;
				push(s,res);
				r=1;

			 }
			 else if(has_type(elem,STR)) {
					
					char* aux;
					res.value.longValue = strtol(elem.value.stringValue,&aux,10);
					push(s,res);
					r = 1;

				  }
				  else if(has_type(elem,CHAR)) {
								
						    res.value.longValue = (long)elem.value.charValue;
							push(s,res);
							r = 1;

					   }
	}
  return r;

}


int converte_dbl(STACK *s, char *token) {
	
	int r=0;
	if(strcmp(token,"f") == 0) {
		
		DATA res;
		res.type = DOUBLE;
		DATA elem = pop(s);
		if(has_type(elem,LONG)) {
			
			res.value.doubleValue = (double) elem.value.longValue;
			push(s,res);
			r = 1;

		}

		else if(has_type(elem,DOUBLE)) {
				
				res.value.doubleValue = (double) elem.value.doubleValue;
				push(s,res);
				r = 1;

			 }

			 else if(has_type(elem,STR)) {
				
					char *aux;
					res.value.doubleValue = strtod(elem.value.stringValue,&aux);
					push(s,res);
					r = 1;

				  }
				  else if(has_type(elem,CHAR)) {
								
							res.value.doubleValue = (double)elem.value.charValue;
							push(s,res);
							r = 1;

					   } 
    }
  return r;  

}
	

int converte_char(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"c") == 0) {
		
		DATA elem = pop(s);
		DATA res;
		res.type = CHAR;
		if(has_type(elem,LONG)) {
			
			res.value.charValue = (char)elem.value.longValue;
			push(s,res);
			r = 1;

		}
		else if(has_type(elem,DOUBLE)) {
			
				res.value.charValue = (char)elem.value.doubleValue;
				push(s,res);
				r = 1;

			 }

			 else if(has_type(elem,CHAR)) {
				
					res.value.charValue = elem.value.charValue;
					push(s,res);
					r = 1;

				  }
		
				  else if(has_type(elem,STR)) {
					
							res.value.charValue = (char)(*elem.value.stringValue);
							push(s,res);
							r = 1;

					   }
	}
  return r; 

}


int converte_str(STACK *s, char *token) {
	
	int r = 0;
	if(strcmp(token,"s") == 0) {
		
		DATA elem = pop(s);
		DATA res;
		res.type = STR;
		if(has_type(elem,LONG)) {
			
			res.value.stringValue = (char*)elem.value.longValue;
			push(s,res);
			r = 1;

		}

		else if(has_type(elem,DOUBLE)) {
			
				long aux = (long)elem.value.doubleValue;
				res.value.stringValue = (char*)aux;
				push(s,res);
				r = 1;

			 }

			 else if(has_type(elem,CHAR)) {
				
					res.value.stringValue = (char*)elem.value.stringValue;
					push(s,res);
					r = 1;

				  }

				  else if(has_type(elem,STR)){
					
							res.value.stringValue = elem.value.stringValue;
							push(s,res);
							r = 1;

					   }

	}
  return r;

}