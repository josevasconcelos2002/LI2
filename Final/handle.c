#include "handle.h"

char* strndup(char const*,size_t n);

char *strtok_r(char *str, const char *delim, char **saveptr);


char* getToken(char *linha,char **rest) {
	
	char* token;
	int i = 0;
	token = strdup(linha);
	while((token[i]) && ((token[i]!= ' ') && (token[i]!= '\n') && (token[i]!='\t'))) {
		
		i++;

	}

	token[i] = '\0';
	*rest = strdup(1 + i+linha);
	return token;

}


STACK *doStack(char *line, char **rest, DATA *values) {
	
	char *token;
	char* resto;
	int i = 0;
	STACK *aux = new_stack();
	char* insideArray = strdup(line);
	while(insideArray[i] && insideArray[i] != ']') {
		if(insideArray[i] == '[') {
			
			insideArray = insideArray + 2;
			DATA a;
			a.type = ARR;
			a.value.arrayValue = doStack(insideArray,&resto,values);
			push(aux,a);

		}

		else {
			
			token = getToken(insideArray,&resto);
			handle(aux,values,token);
			
		}
		insideArray = resto;
	}
	*rest = strdup(insideArray+2);
	return aux;
}

char* doArrString (char* line, char **rest) {
	
	int j = 1;
	char *arr = strdup(line);
	while(arr[j] && arr[j] != '\"') j++;
	arr[j] = '\0';
	*rest = strdup(line+j+1);
	arr = arr + 1;
	return arr;
}
	

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
	
	int r = 0;
	if(strcmp(token,"l") == 0) {
		
		char str[1024];
		if(fgets(str,1024,stdin)) {
		
			int length = strlen(str);
			DATA elem;
			elem.type = STR;
			elem.value.stringValue = strndup(str,length-1);
			push(s,elem);
			r = 1;

		}
	}
	else if(strcmp(token,"t") == 0) {
			char str[1024];
			if(fgets(str,1024,stdin)) {
				
				int length= strlen(str);
				DATA elem;
				elem.type = STR;
				elem.value.stringValue = strndup(str,length-1);
				push(s,elem);
				r = 1;

			}
		 }
  return r;

}


int val(STACK *s, char *token) {
	
	int r = 0;
	char *rest;
	long lnumber = strtol(token,&rest,10);      
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
			
			DATA elem;                            
			elem.type = DOUBLE;
			elem.value.doubleValue = dnumber;
			push(s,elem);
			r = 1;

		}
	}
  return r;

}

int pushSTR(STACK *s,char *token) {
	
	char *a;
	a = strdup(token);
	int i = 0;
	int control = 1;
	int r = 0;
	while(a[i]) {
		if(isalpha(a[i]) == 0) control = 0;
		i++;
	}

	if(control!=0) {
		
		DATA res;
		res.type = STR;
		res.value.stringValue = a;
		push(s,res);
		r = 1;

	}		
  return r;

}


int handle(STACK *s, DATA* values,  char *token){

	 return (soma(s,token) || sub(s,token) || mult(s,token)
	 || dividir(s,token) || expoente(s,token) 
	 || decrementa(s,token)|| incrementa(s,token) || e(s,token)
	 || modulo(s,token) || ou(s,token) || e(s,token) || nao(s,token) 
	 || myxor(s,token) || readinput(s,token)|| converte_int(s,token)
	 || converte_dbl(s,token) || converte_char(s,token) || converte_str(s,token)
	 || duplica(s,token)|| mypop(s,token) || troca2(s,token) || roda3(s,token)
	 || copia(s,token)  || igual(s,token)  || menor(s,token)  || maior(s,token)  
	 || nao_logico(s,token)  || e_short(s,token)  || ou_short(s,token) 
	 || push_m(s,token)  || push_M(s,token) || if_then_else(s,token) || var(s,values,token)  
	 || val(s,token) || pushSTR(s,token) || arrayToStack(s,token) 
	 || concatSA(s,token) || concatVSA(s,token) || byIndex(s,token) || getElem(s,token) 
	 || byRange(s,token) || getElem(s,token) || searchSubString(s,token) || removeElem(s,token) || sepString(token,s)) ;
    
}

STACK *makeStack(char* line, DATA* values, STACK *s) {
	
	if(s == NULL) s = new_stack();
	
	char* rest;
	char* token;
	while(strlen(line)!= 0){
		if(line[0] == '\"') {
			
			char *str;
			str = doArrString(line,&rest);
			STACK* aux = makeStack(str,values,NULL);
			DATA a;
			a.type = ARR;
			a.value.arrayValue = aux;
			push(s,a);

		}

		else {
			
			token = getToken(line,&rest);
			if(*token!= '\0') {
				
				if(strcmp(token,"[") == 0) {
					
					STACK *aux = doStack(rest,&rest,values);
					DATA a;
					a.type = ARR;
					a.value.arrayValue = aux;
					push(s,a);
				
				}

				else {

					handle(s,values,token);

				}
			}
		}
		line = rest;
	}
  return s;

}

		
DATA *init_values(DATA values[]) {
	
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
	return values;

}


void parse(char *line) {
	
	STACK *s = new_stack();
	DATA values[26];
	int i;
	for(i = 0;i<26;i++) {

		values[i].type = LONG;

	}

	init_values(values);
	makeStack(line,values,s);
	printStack(s);		
	printf("\n");
	free(s);

}











