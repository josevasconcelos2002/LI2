#include "operadores.h"
#include <string.h>



int nao(STACK *s, char *token){
	
	int r = 0;	
	if(strcmp(token,"~") == 0 && s->stack[s->sp].type!=STR && s->stack[s->sp].type!=ARR){
		DATA res;
		DATA x = pop(s);
		if (has_type(x , LONG)) {  
			long x1 = x.value.longValue;
			long result = ~x1;
			res.type = LONG;
			res.value.longValue = result;
			push(s, res);
			r = 1;
		
		}

		else if (has_type(x , DOUBLE)) {

				long x1 = (long) x.value.doubleValue;
				long result = ~x1;
				res.type = LONG;
				res.value.longValue = result;
				push(s, res);
				r = 1;

			  }
	}
	return r;
}


int myxor(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"^") == 0){
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			res.type = LONG;
			res.value.longValue = y.value.longValue ^ x.value.longValue;
			push(s,res);
			r = 1;	

		}
		else {
			if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				long y1 = (long) y.value.doubleValue;
				long result;
				result = y1 ^ x.value.longValue;
				res.value.longValue = result;
				push(s,res);
				r = 1;
			}
			else {
				if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long result;
					result = y.value.longValue ^ x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
				else {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long y1 = (long) y.value.doubleValue;
					long result;
					result = y1 ^ x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
			}
		}
	}
 return r;

}


int ou(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"|") == 0){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = y.value.longValue | x.value.longValue;
			push(s,res);
			r = 1;			
		}
		else {
			if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				long y1 = (long) y.value.doubleValue;
				long result;
				result = y1 | x.value.longValue;
				res.value.longValue = result;
				push(s,res);
				r = 1;
			}
			else {
				if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long result;
					result = y.value.longValue | x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
				else {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long y1 = (long) y.value.doubleValue;
					long result;
					result = y1 | x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
			}
		}
	}
 return r;

}


int e(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"&") == 0){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = y.value.longValue & x.value.longValue;
			push(s,res);
			r = 1;

		}
		else {
			if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				long y1 = (long) y.value.doubleValue;
				long result;
				result = y1 & x.value.longValue;
				res.value.longValue = result;
				push(s,res);
				r = 1;

			}
			else {
				if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long result;
					result = y.value.longValue & x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
				else {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long y1 = (long) y.value.doubleValue;
					long result;
					result = y1 & x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				}
			}
		}
	}
 return r;

}


int expoente(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"#") == 0 && s->stack[s->sp].type!=STR){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if ((has_type(x , LONG)) && (has_type(y , LONG))) {
			
			double x1 = x.value.longValue;
			double y1 = y.value.longValue;
			long result = pow(y1,x1);
			res.type = LONG;
			res.value.longValue = result;
			push(s, res);
			r = 1;
		
		}

		else if ((has_type(x , DOUBLE)) && (has_type(y , DOUBLE))) {
				
				double x1 = x.value.doubleValue;
				double y1 = y.value.doubleValue;
				double result = (double) pow(y1,x1);
				res.type = DOUBLE;
				res.value.doubleValue = result;
				push(s, res);
				r = 1;

			  }

			 else if ((has_type(x , LONG)) && (has_type(y , DOUBLE))) {
					
					double x1 = x.value.longValue;
					double y1 = y.value.doubleValue;
					double result = (double)pow(y1,x1);
					res.type = DOUBLE;
					res.value.doubleValue = result;
					push(s, res);
					r = 1;	

				  }

				  else if ((has_type(x , DOUBLE)) && (has_type(y , LONG))) {
							
							double x1 = x.value.doubleValue;
							double y1 = y.value.longValue;
							double result = (double)pow(y1,x1);
							res.type = DOUBLE;
							res.value.doubleValue = result;
							push(s, res);
							r = 1;	

						}
	}
 return r;

}


int incrementa(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,")") == 0 && s->stack[s->sp].type!=STR && s->stack[s->sp].type!=ARR){
		
		DATA res;
		DATA x = pop(s);
		if (has_type(x , LONG)) {  
			long x1 = x.value.longValue;
			long result = x1 + 1;
			res.type = LONG;
			res.value.longValue = result;
			push(s, res);
			r = 1;
		
		}

		else if ((has_type(x , DOUBLE))) {
				
				double x1 = x.value.doubleValue;
				double result = (double) x1 + 1;
				res.type = DOUBLE;
				res.value.doubleValue = result;
				push(s, res);
				r = 1;

			}
		
			 else if(has_type(x,CHAR)) {
					long x1 = (long) x.value.charValue;
					res.type = CHAR;
					x1 = x1 + 1;
					res.value.charValue = (char) x1;
					push(s,res);
					r = 1;	
				  }

				  else if(has_type(x,STR)) {
							char *aux;
							long x1 = strtol(x.value.stringValue,&aux,10);
							res.type = LONG;
							x1 = x1 + 1;
							res.value.longValue = x1;
							push(s,res);
							r = 1;
						}
	}
 return r;

}


int decrementa(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"(") == 0 && s->stack[s->sp].type!=STR && s->stack[s->sp].type!=ARR){
		
		DATA res;
		DATA x = pop(s);
		if (has_type(x , LONG)) {  
			
			long x1 = x.value.longValue;
			long result = x1 - 1;
			res.type = LONG;
			res.value.longValue = result;
			push(s, res);
			r = 1;
		
		}

		else if (has_type(x , DOUBLE)) {
				
				double x1 = x.value.doubleValue;
				double result = (double) x1 - 1;
				res.type = DOUBLE;
				res.value.doubleValue = result;
				push(s, res);
				r = 1;

			}
		
			 else if(has_type(x,CHAR)) {
					
					long x1 = (long) x.value.charValue;
					res.type = CHAR;
					x1 = x1 - 1;
					res.value.charValue = (char) x1;
					push(s,res);
					r = 1;

				}

				   else if(has_type(x,STR)) {
							char *aux;
							long x1 = strtol(x.value.stringValue,&aux,10);
							res.type = LONG;
							x1 = x1 - 1;
							res.value.longValue = x1;
							push(s,res);
							r = 1;
						}
	}
  return r;

}


int modulo(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"%") == 0){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = y.value.longValue % x.value.longValue;
			push(s,res);
			r = 1;	

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				long y1 = (long) y.value.doubleValue;
				long result;
				result = y1 % x.value.longValue;
				res.value.longValue = result;
				push(s,res);
				r = 1;

			 }
			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					long x1 = (long) x.value.doubleValue;
					long result;
					result = y.value.longValue % x1;
					res.value.longValue = result;
					push(s,res);
					r = 1;

				  }

				  else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {
							
							res.type = DOUBLE;
							long x1 = (long) x.value.doubleValue;
							long y1 = (long) y.value.doubleValue;
							long result;
							result = y1 % x1;
							res.value.longValue = result;
							push(s,res);
							r = 1;

					   }

					   else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
								
								res.type = LONG;
								long x1 = (long) x.value.charValue;
								res.value.longValue = x1 % y.value.longValue;
								push(s,res);
								r = 1;

							}
		
							else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
									
									res.type = LONG;
									long y1 = (long) y.value.charValue;
									res.value.longValue = y1 % x.value.longValue;
									push(s,res);
									r = 1;

								}

								else if((has_type(x,STR)) && (has_type(y,LONG))) {
										
										char *aux;
										res.type = LONG;
										long x1 = strtol(x.value.stringValue,&aux,10);
										res.value.longValue = x1 % y.value.longValue;
										push(s,res);
										r = 1;

									 }

									 else if((has_type(x,LONG)) && (has_type(y,STR))) {
											
											char *aux;
											res.type = LONG;
											long y1 = strtol(y.value.stringValue,&aux,10);
											res.value.longValue = y1 % x.value.longValue;
											push(s,res);
											r = 1;

										}
	}
  return r;

}


int dividir(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"/") == 0 && s->stack[s->sp].type!=STR){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			long x1 = x.value.longValue;
			long y1 = y.value.longValue;
			long result = y1/x1;
			res.type = LONG;
			res.value.longValue = result;
			push(s,res);
			r = 1;	

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				double result;
				result = (double) y.value.doubleValue / x.value.longValue;
				res.value.doubleValue = result;
				push(s,res);
				r = 1;

			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					double result;
					result = (double) y.value.longValue / x.value.doubleValue;
					res.value.doubleValue = result;
					push(s,res);
					r = 1;

				  }

				  else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {
							
							double x1 = x.value.doubleValue;
							double y1 = y.value.doubleValue;
							double result = (double)y1/x1;
							res.type = DOUBLE;
							res.value.doubleValue = result;
							push(s,res);
							r = 1;

					   }

					   else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
								
								long x1 = (long) x.value.charValue;
								long y1 = y.value.longValue;
								if(y1%x1==0) {
									
									long result = y1/x1;
									res.type = LONG;
									res.value.longValue = result;
									push(s,res);
									r = 1;

								}

								else { 
									
									double x2 =(double) x1;
									double y2 = (double) y1;
									double result = (double)y2/x2;
									res.type = DOUBLE;
									res.value.doubleValue = result;
									push(s,res);
									r = 1;

								}
							}
							
							else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
									
									long y1 = (long) y.value.charValue;
									long x1 = x.value.longValue;
									if(y1%x1==0) {
										
										long result = y1/x1;
										res.type = LONG;
										res.value.longValue = result;
										push(s,res);
										r = 1;

									}
									else { 
										
										double x2 =(double) x1;
										double y2 = (double) y1;
										double result = (double)y2/x2;
										res.type = DOUBLE;
										res.value.doubleValue = result;
										push(s,res);
										r = 1;

									}
								 }

								 else if((has_type(x,STR)) && (has_type(y,LONG))) {
										
										char *aux;
										long x1 = strtol(x.value.stringValue,&aux,10);
										long y1 = y.value.longValue;
										if(y1%x1==0) {
											
											long result = y1/x1;
											res.type = LONG;
											res.value.longValue = result;
											push(s,res);
											r = 1;

										}

										else { 
											
											double x2 =(double) x1;
											double y2 = (double) y1;
											double result = (double)y2/x2;
											res.type = DOUBLE;
											res.value.doubleValue = result;
											push(s,res);
											r = 1;

										}
									}	

									else if((has_type(x,LONG)) && (has_type(y,STR))) {
											
											char *aux;
											long y1 = strtol(y.value.stringValue,&aux,10);
											long x1 = x.value.longValue;
											if(y1%x1==0) {
												
												long result = y1/x1;
												res.type = LONG;
												res.value.longValue = result;
												push(s,res);
												r = 1;

											}

											else { 
												
												double x2 =(double) x1;
												double y2 = (double) y1;
												double result = (double)y2/x2;
												res.type = DOUBLE;
												res.value.doubleValue = result;
												push(s,res);
												r = 1;

											}
										}				
	}
  return r;

}


int mult(STACK *s, char *token){
	
	int r = 0;
	if((strcmp(token,"*") == 0) && (s->stack[s->sp -1].type!=STR) && (s->stack[s->sp -1].type!=ARR)){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = x.value.longValue * y.value.longValue;
			push(s,res);
			r = 1;	

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				double result;
				result = x.value.longValue * y.value.doubleValue;
				res.value.doubleValue = result;
				push(s,res);
				r = 1;

			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
						
						res.type = DOUBLE;
						double result;
						result = x.value.doubleValue * y.value.longValue;
						res.value.doubleValue = result;
						push(s,res);
						r = 1;

				  }

				  else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {
							
							res.type = DOUBLE;
							double result;
							result = x.value.doubleValue * y.value.doubleValue;
							res.value.doubleValue = result;
							push(s,res);
							r = 1;

					   }

					   else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
								
								res.type = LONG;
								long x1 = (long) x.value.charValue;
								res.value.longValue = x1 * y.value.longValue;
								push(s,res);
								r = 1;

							}
		
							else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
									
									res.type = LONG;
									long y1 = (long) y.value.charValue;
									res.value.longValue = y1 * x.value.longValue;
									push(s,res);
									r = 1;

								 }

								 else if((has_type(x,STR)) && (has_type(y,LONG))) {
										
										char *aux;
										res.type = LONG;
										long x1 = strtol(x.value.stringValue,&aux,10);
										res.value.longValue = x1 * y.value.longValue;
										push(s,res);
										r = 1;

									  }

									  else if((has_type(x,LONG)) && (has_type(y,STR))) {
												
												char *aux;
												res.type = LONG;
												long y1 = strtol(y.value.stringValue,&aux,10);
												res.value.longValue = y1 * x.value.longValue;
												push(s,res);
												r = 1;

										   }	
	}
  return r;

}


int sub(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"-") == 0){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = y.value.longValue - x.value.longValue;
			push(s,res);
			r = 1;	

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				double result;
				result = y.value.doubleValue - x.value.longValue;
				res.value.doubleValue = result;
				push(s,res);
				r = 1;

			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					double result;
					result = y.value.longValue - x.value.doubleValue;
					res.value.doubleValue = result;
					push(s,res);
					r = 1;

				  }

				  else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) { 
							
							res.type = DOUBLE;
							double result;
							result = y.value.doubleValue - x.value.doubleValue;
							res.value.doubleValue = result;
							push(s,res);
							r = 1;

					   }

					   else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
								
								res.type = LONG;
								long x1 = (long) x.value.charValue;
								res.value.longValue = x1 - y.value.longValue;
								push(s,res);
								r = 1;

							}
		
							else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
									
									res.type = LONG;
									long y1 = (long) y.value.charValue;
									res.value.longValue = y1 - x.value.longValue;
									push(s,res);
									r = 1;

								 }

								 else if((has_type(x,STR)) && (has_type(y,LONG))) {
										
										char *aux;
										res.type = LONG;
										long x1 = strtol(x.value.stringValue,&aux,10);
										res.value.longValue = x1 - y.value.longValue;
										push(s,res);
										r = 1;

									  }

									  else if((has_type(x,LONG)) && (has_type(y,STR))) {
												
												char *aux;
												res.type = LONG;
												long y1 = strtol(y.value.stringValue,&aux,10);
												res.value.longValue = y1 - x.value.longValue;
												push(s,res);
												r = 1;

										   }	
	}
  return r;

}


int soma(STACK *s, char *token){
	
	int r = 0;
	if(strcmp(token,"+") == 0 && s->stack[s->sp].type!=STR && s->stack[s->sp].type!=ARR){
		
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {
			
			res.type = LONG;
			res.value.longValue = x.value.longValue + y.value.longValue;
			push(s,res);
			r = 1;	

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				
				res.type = DOUBLE;
				double result;
				result = x.value.longValue + y.value.doubleValue;
				res.value.doubleValue = result;
				push(s,res);
				r = 1;

			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
					
					res.type = DOUBLE;
					double result;
					result = x.value.doubleValue + y.value.longValue;
					res.value.doubleValue = result;
					push(s,res);
					r = 1;

				  }

				  else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {
							
							res.type = DOUBLE;
							double result;
							result = x.value.doubleValue + y.value.doubleValue;
							res.value.doubleValue = result;
							push(s,res);
							r = 1;

					   }

					   else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
								
								res.type = LONG;
								long x1 = (long) x.value.charValue;
								res.value.longValue = x1 + y.value.longValue;

							}
		
							else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
									
									res.type = LONG;
									long y1 = (long) y.value.charValue;
									res.value.longValue = y1 + x.value.longValue;

								 }

								 else if((has_type(x,STR)) && (has_type(y,LONG))) {
										
										char *aux;
										res.type = LONG;
										long x1 = strtol(x.value.stringValue,&aux,10);
										res.value.longValue = x1 + y.value.longValue;

									  }

									  else if((has_type(x,LONG)) && (has_type(y,STR))) {
											
												char *aux;
												res.type = LONG;
												long y1 = strtol(y.value.stringValue,&aux,10);
												res.value.longValue = y1 + x.value.longValue;

										   }	
	}
  return r;

}