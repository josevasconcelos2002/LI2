#include "operadores.h"
#include <string.h>



/**
 * 
 * @Função que faz um bitwise not do ultimo elemento colocado na stack. 
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/




int nao(STACK *s, char *token){
	
	if(strcmp(token,"~") == 0){


		DATA x = pop(s);
		
		if ((has_type(DATA x , 1))) {  
		
		LONG a = x.value.longValue;
		LONG w = ~x;
		push(s, w);
		return 1;
		}	
		
    }
    

	else return 0;
}



/**
 * 
 * @Função que faz bitwise xor dos dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/



int myxor(STACK *s, char *token){
	
	if(strcmp(token,"^") == 0){


		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = x ^ y;
		push(s, w);
		return 1;
		}	
		
    }
    

	else return 0;
}





/**
 * 
 * @Função que faz bitwise or dos dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/




int ou(STACK *s, char *token){
	
	if(strcmp(token,"|") == 0){


		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = x | y;
		push(s, w);
		return 1;
		}	
		
    }
    

	else return 0;
}




/**
 * 
 * @Função que faz bitwise and dos dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/



int e(STACK *s, char *token){
	
	if(strcmp(token,"&") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = x & y;
		push(s, w);
		return 1;
		}	
		
    }
    

	else return 0;
}


/**
 * 
 * @Função que calcula a exponenciação dos dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/





int expoente(STACK *s, char *token){
	
	if(strcmp(token,"#") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = pow(y,x);
		push(s, w);
		return 1;
		
		}

		else if ((has_type(DATA x , 2)) & (has_type(DATA y , 2))) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE b = y.value.doubleValue;
				DOUBLE w = pow(y,x);
				push(s, w);
				return 1;

			  }

			  else if ((has_type(DATA x , 1)) & (has_type(DATA y , 2))) {


				    LONG a = x.value.longValue;
					DOUBLE b = y.value.doubleValue;
					DOUBLE w = pow(y,x);
					push(s, w);
					return 1;
					
					}

					else if ((has_type(DATA x , 2)) & (has_type(DATA y , 1))) {


						 DOUBLE a = x.value.doubleValue;
						 LONG b = y.value.longValue;
						 DOUBLE w = pow(y,x);
						 push(s, w);
						 return 1;

					     }
    
    }

	else return 0;
}




/**
 * 
 * @Função que incrementa 1 ao ultimo elemento colocado na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" devolva 1
 *
 *
*/




int incrementa(STACK *s, char *token){
	
	if(strcmp(token,")") == 0){

		DATA x = pop(s);
		
		if (has_type(DATA x , 1)) {  
		
		LONG a = x.value.longValue;
		LONG w = ++x;
		push(s, w);
		return 1;
		
		}

		else if (has_type(DATA x , 2)) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE w = ++x;
				push(s, w);
				return 1;

			  }
    
    }

	else return 0;
}




/**
 * 
 * @Função que subtrai 1 ao ultimo elemento colocado na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/




int decrementa(STACK *s, char *token){
	
	if(strcmp(token,"(") == 0){

		DATA x = pop(s);
		
		if (has_type(DATA x , 1)) {  
		
		LONG a = x.value.longValue;
		LONG w = --x;
		push(s, w);
		return 1;
		
		}

		else if (has_type(DATA x , 2)) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE w = --x;
				push(s, w);
				return 1;

			  }
    
    }

	else return 0;
}




/**
 * 
 * @Função que calcula o resto da divisão dos ultimos dois elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 *
*/



int modulo(STACK *s, char *token){
	
	if(strcmp(token,"%") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = y % x;
		push(s, w);
		return 1;
		}	
		
    }
    

	else return 0;
}




/**
 * 
 * @Função que calcula a divisão inteira dos dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1
 *
 *
*/




int dividir(STACK *s, char *token){
	
	if(strcmp(token,"/") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = b / a;
		push(s, w);
		return 1;
		
		}

		else if ((has_type(DATA x , 2)) & (has_type(DATA y , 2))) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE b = y.value.doubleValue;
				DOUBLE w = y / x;
				push(s, w);
				return 1;

			  }

			  else if ((has_type(DATA x , 1)) & (has_type(DATA y , 2))) {


				    LONG a = x.value.longValue;
					DOUBLE b = y.value.doubleValue;
					DOUBLE w = y / x;
					push(s, w);
					return 1;
					
					}

					else if ((has_type(DATA x , 2)) & (has_type(DATA y , 1))) {


						 DOUBLE a = x.value.doubleValue;
						 LONG b = y.value.longValue;
						 DOUBLE w = y / x;
						 push(s, w);
						 return 1;

					     }
    
    }

	else return 0;
}





/**
 * 
 * @Função que multiplica os dois ultimos elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 * 
*/




int mult(STACK *s, char *token){
	
	if(strcmp(token,"*") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = y * x;
		push(s, w);
		return 1;
		
		}

		else if ((has_type(DATA x , 2)) & (has_type(DATA y , 2))) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE b = y.value.doubleValue;
				DOUBLE w = y * x;
				push(s, w);
				return 1;

			  }

			  else if ((has_type(DATA x , 1)) & (has_type(DATA y , 2))) {


				    LONG a = x.value.longValue;
					DOUBLE b = y.value.doubleValue;
					DOUBLE w = y * x;
					push(s, w);
					return 1;
					
					}

					else if ((has_type(DATA x , 2)) & (has_type(DATA y , 1))) {


						 DOUBLE a = x.value.doubleValue;
						 LONG b = y.value.longValue;
						 DOUBLE w = y * x;
						 push(s, w);
						 return 1;

					     }
    
    }

	else return 0;
}



/**
 * 
 * @Função que calcula a diferença entre os ultimos dois elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 * 
*/




int sub(STACK *s, char *token){
	
	if(strcmp(token,"-") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = y - x;
		push(s, w);
		return 1;
		
		}

		else if ((has_type(DATA x , 2)) & (has_type(DATA y , 2))) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE b = y.value.doubleValue;
				DOUBLE w = y - x;
				push(s, w);
				return 1;

			  }

			  else if ((has_type(DATA x , 1)) & (has_type(DATA y , 2))) {


				    LONG a = x.value.longValue;
					DOUBLE b = y.value.doubleValue;
					DOUBLE w = y - x;
					push(s, w);
					return 1;
					
					}

					else if ((has_type(DATA x , 2)) & (has_type(DATA y , 1))) {


						 DOUBLE a = x.value.doubleValue;
						 LONG b = y.value.longValue;
						 DOUBLE w = y - x;
						 push(s, w);
						 return 1;

					     }
    
    }

	else return 0;
}




/**
 * 
 * @Função que calcula a soma entre os ultimos dois elementos colocados na stack.
 * @Retorna 1 se conseguir concluir a operação e 0 caso o "strcmp" retorne 1.
 *
 * 
*/




int soma(STACK *s, char *token){
	
	if(strcmp(token,"+") == 0){

		DATA x = pop(s);
		DATA y = pop(s);
		
		if ((has_type(DATA x , 1)) & (has_type(DATA y , 1))) {  
		
		LONG a = x.value.longValue;
		LONG b = y.value.longValue;
		LONG w = y + x;
		push(s, w);
		return 1;
		
		}

		else if ((has_type(DATA x , 2)) & (has_type(DATA y , 2))) {

				DOUBLE a = x.value.doubleValue;
				DOUBLE b = y.value.doubleValue;
				DOUBLE w = y + x;
				push(s, w);
				return 1;

			  }

			  else if ((has_type(DATA x , 1)) & (has_type(DATA y , 2))) {


				    LONG a = x.value.longValue;
					DOUBLE b = y.value.doubleValue;
					DOUBLE w = y + x;
					push(s, w);
					return 1;
					
					}

					else if ((has_type(DATA x , 2)) & (has_type(DATA y , 1))) {


						 DOUBLE a = x.value.doubleValue;
						 LONG b = y.value.longValue;
						 DOUBLE w = y + x;
						 push(s, w);
						 return 1;

					     }
    
    }

	else return 0;
}
