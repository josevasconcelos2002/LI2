#include "conversoes.h"



int converte_int(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"i") == 0) {

		DATA res;
		res.type = LONG;

		printStack(s);

		DATA elem = pop(s);
		
		printStack(s);
		
		TYPE t = elem.type;
		
		printf("%ld",elem.value.longValue);
		
		if(t == LONG) {

			res.value.longValue = elem.value.longValue;
			printf("%ld",res.value.longValue);
			push(s,res);
			r=1;

		}

	    else {

			if(t == DOUBLE) {
				res.value.longValue = (int)elem.value.doubleValue;
				push(s,res);
				r=1;
			}
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

		if(has_type(elem,1)) {

			res.value.doubleValue = (double)elem.value.longValue;
			push(s,res);
			r = 1;

		}

		else {

			if(has_type(elem,2)) {
				res.value.doubleValue = elem.value.doubleValue;
				push(s,res);
				r = 1;
				
			}
		}    
    }

	return r;  
}
	






int converte_char(STACK *s, char *token){

	int r = 0;

	if(strcmp(token,"c") == 0) {
		DATA res;
		res.type = CHAR;
		DATA elem = pop(s);

		if(has_type(elem,1)) {

	    res.value.charValue = (char)elem.value.charValue;
	    push(s,res);
	    r = 1;

		}

		else if(has_type(elem,2)) {


			 res.value.charValue = (char)elem.value.charValue;
			 push(s,res);
			 r = 1;
			 
			 }

			 else if(has_type(elem,3)) {

			 	  res.value.charValue = elem.value.charValue;
			 	  push(s,res);
			 	  r = 1;	   


			 	   }


	
	}
		
	return r;    
}





int converte_str(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"s") == 0) {
	         
		DATA res;
		res.type = STR;
		DATA elem = pop(s);

		if(has_type(elem,1)) {

	    res.value.*stringValue = (char)elem.value.*stringValue;
	    push(s,res);
	    r = 1;

		}

		else if(has_type(elem,2)) {


			 res.value.*stringValue = (char)elem.value.*stringValue;
			 push(s,res);
			 r = 1;
			 
			 }

			 else if(has_type(elem,3)) {

			 	  res.value.*stringValue = (char)elem.value.*stringValue;
			 	  push(s,res);
			 	  r = 1;	   


			 	   }

			 	   else if(has_type(ele,4)) {

			 	   		res.value.*stringvalue = ele.value.*stringValue;
			 	   		push(s,res);
			 	   		r = 1;

			 	   		}


	
	}
		
	return r;    
}
	
	    
