#include "arrays_e_strings.h"



int concatena(STACK *s, char *token) {

	int r = 0;
		if(strcmp(token,"+") == 0) {
			DATA res;
			DATA x = pop(s);
			DATA y = pop(s);
			if(has_type(x,STR) && has_type(y,STR)) {
				STR a = x.value.stringValue;
				STR b = y.value.stringValue;
				res.type = STR;
				res.value.stringValue = strcat(a,b);
				push(s,res);
				r = 1;
			}
			else if(has_type(x,ARR) && has_type(y,ARR)) {
					ARR a = x.value.array;
					ARR b = y.value.array;
					res.type = ARR;
					res.value.array = // array resultante, após a concatenção
					push(s,res);
					r = 1;
				 }
				 else if(has_type(x,ARR) && has_type(y,CHAR)) {
							ARR a = x.value.array; // arrValue(?)
							ARR b = (ARR)y.value.charValue;
							res.type = ARR;
							res.value.array = // array resultante, após a concatenção
							push(s,res);
							r = 1;
					  }
					  else if(has_type(x,CHAR) && has_type(y,ARR)) {
								ARR a = (ARR)x.value.charValue;
								ARR b = y.value.array;
								res.type = ARR;
								res.value.array = // array resultante, após a concatenção
								push(s,res);
								r = 1;
						   }
						   else if(has_type(x,CHAR) && has_type(y,STR)) {
									STR a = (STR)x.value.charValue;
									STR b = y.value.stringValue;
									res.type = STR;
									res.value.stringValue = strcat(a,b); // string resultante, após a concatenção
									push(s,res);
									r = 1;
							    }
							    else if(has_type(x,STR) && has_type(y,CHAR)) {
										STR a = x.value.stringValue;
										STR b = (STR)y.value.charValue;
										res.type = STR;
										res.value.stringValue = strcat(a,b); // string resultante, após a concatenção
										push(s,res);
										r = 1;
								     }

	  return r;
	}

 else return r;
}


int mult_concatena(STACK *s, char *token) {  //concatena múltiplas vezes

	int r = 0;
		if(strcmp(token,"*") == 0) {
			DATA res;
			DATA x = pop(s);
			DATA y = *(s+2);             //ex:  "aaa" * 3    = "aaaaaaaaa"   *(s+2) = 3(?)
			if(has_type(x,STR) && has_type(y,LONG)) {
				STR a = x.value.stringValue;
				long a = y.value.longValue;
				res.type = STR;
				res.value.stringValue = //resultado da concatenção múltipla
				push(s,res);
				r = 1;
			}

			else if(has_type(x,ARR) && has_type(y,LONG)) {
					ARR a = x.value./*arr*/Value;
					long a = y.value.longValue;
					res.type = ARR;
					res.value./*arr*/Value = //resultado da concatenção múltipla
					push(s,res);
					r = 1;
				 }

	return r;
	}

else return r;
}


int remove_primeiro(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"(") == 0) {
		DATA res1;
		DATA res2;
		DATA x = pop(s);
		if(has_type(x,STR)) {
			STR a = x.value.stringValue;
			res1.type = STR;
			res1.value.stringValue = // string resultante, após a remoção do primeiro caractere
			res2.type = CHAR;
			res2.value.charValue = //caractere removido da string
			push(s,res1);
			push(s,res2);
			r = 1;
		}

		else if(has_type(x,ARR)) {
				ARR a = x.value.Value; // arrValue(?)
				res1.type = ARR;
				res1.value.Value = // arrValue(?)    = array resultante após a remoção do primeiro elemento do inicial
				res2.type = //tipo dos elementos do ARR
				res2.value.Value = //tipo dos elementos do ARR (?)   = elemento removido do array inicial
				push(s,res1);
				push(s,res2);
				r = 1;
			 }

	  return r;
	}

 else return r;
}


int remove_ult(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,")") == 0) {
		DATA res1;
		DATA res2;
		DATA x = pop(s);
		if(has_type(x,STR)) {
			STR a = x.value.stringValue;
			res1.type = STR;
			res1.value.stringValue = // string resultante, após a remoção do último caractere
			res2.type = CHAR;
			res2.value.charValue = //caractere removido da string
			push(s,res1);
			push(s,res2);
			r = 1;
		}

		else if(has_type(x,ARR)) {
				ARR a = x.value.Value; //arrValue(?)
				res1.type = ARR;
				res1.value.array = //array resultante após a remoção do último elemento do inicial
				res2.type = //tipo dos elementos do ARR
				res2.value.Value = //tipo dos elementos do ARR (?)   = elemento removido do array inicial
				push(s,res1);
				push(s,res2);
				r = 1;
			 }

	  return r;
	}

 else return r;
}


int busca_inicio(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"<") == 0) {
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if(has_type(x,LONG) && (has_type(y,STR))) {
			LONG a = x.value.longValue;
			res.type = STR;
			res.value.//types dos elementos = for(int i = 0;i<x;i++) ...
			push(s,res);
			r = 1;
		}

		else if(has_type(x,LONG) && (has_type(y,ARR))) {
				LONG a = x.value.longValue;
				res.type = //type dos elementos do array (?)
				res.value.//types dos elementos = for(int i = 0;i<x;i++) ...
				push(s,res);
				r = 1;

			 }

	  return r;
	}

 else return r;
}


int busca_fim(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,">") == 0) {
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if(has_type(x,LONG) && (has_type(y,STR))) {
			LONG a = x.value.longValue;
			res.type = STR;
			res.value.//types dos elementos = for(int i = 0;i<x;i++) ...
			push(s,res);
			r = 1;
		}

		else if(has_type(x,LONG) && (has_type(y,ARR))) {
				LONG a = x.value.longValue;
				res.type = //type dos elementos do array (?)
				res.value.//types dos elementos = for(int i = 0;i<x;i++) ...
				push(s,res);
				r = 1;

			 }

	  return r;
	}

 else return r;
}


int length_or_range(STACK *s, char *token) {

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
		else if(has_type(x,LONG)) {
				LONG a = x.value.longValue;
				int j = 0;
				for(j; (i < a) && (a > 0) ;j++)j;    //como converter b em ARR?
				res.type = ARR;
				res.value. = b;	
				push(s,res);
				r = 1;
			 }
			 else if(has_type(x,ARR)) {
					ARR a = x.value.array;
					int i = 0;
					int j = 0;
					for(j;a != '\0';j++) i += 1;
					LONG b = 
					push(s,res);
					r = 1;
				  }

	 return r;
	}

 else return r; 
}