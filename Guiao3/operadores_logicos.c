#include "operadores_logicos.h"




int igual(STACK *s, char *token) {

	int r = 0;
	if(strcmp(token,"=") == 0) {
		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);
		if((has_type(x,LONG)) && (has_type(y,LONG))) {  
			res.type = LONG;
			long a = x.value.longValue;
			long b = y.value.longValue;
			if(a == b) {
				res.value.longValue = 1;	
				push(s,res);
		    	r = 1;
		    }

			else {
				res.value.longValue = 0;	
				push(s,res);
				r = 1;
			}

		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {
				res.type = DOUBLE;
				long a = x.value.longValue;
				double b = y.value.doubleValue;

				if(a == b) {
					res.value.doubleValue = 1.0;
					push(s,res);
					r = 1;
				}

				else {
					res.value.doubleValue = 0.0;
					push(s,res);
					r = 1;

                }

			}

		else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
				res.type = DOUBLE;
				double a = x.value.doubleValue;
				long b = y.value.longValue;

				if(a == b) {
					res.value.doubleValue = 1.0;
					push(s,res);
					r = 1;
					}

				else {
					res.value.doubleValue = 0.0;
					push(s,res);
					r = 1;
				}
			}

		else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {
				res.type = DOUBLE;
				double a = x.value.doubleValue;
				double b = y.value.doubleValue;

				if(a == b) {
					res.value.doubleValue = 1.0;
					push(s,res);
					r = 1;
				}

				else {
					res.value.doubleValue = 0.0;
					push(s,res);
					r = 1;
				}
			}

		else if((has_type(x,LONG)) && (has_type(y,CHAR))) {
				res.type = LONG;
				long a = x.value.longValue;
				long b = (long) y.value.charValue;

				if(a == b) {
					res.value.longValue = 1;
					push(s,res);
					r = 1;
				}

				else {
					res.value.longValue = 0;
					push(s,res);
					r = 1;
				}
			}

		else if((has_type(x,CHAR)) && (has_type(y,LONG))) {
				res.type = LONG;
				long a = (long) x.value.charValue;
				long b = y.value.longValue;

				if(a == b) {
					res.value.longValue = 1;
					push(s,res);
					r = 1;
				}

				else {
					res.value.longValue = 0;
					push(s,res);
					r = 1;

				}
			}

			else if((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {
					res.type = DOUBLE;
					double a = (double) x.value.charValue;
					double b = y.value.doubleValue;
							
                    if(a == b) {
						res.value.doubleValue = 1.0;
						push(s,res);
						r = 1;
					}

					else {
						res.value.doubleValue = 0.0;
						push(s,res);
						r = 1;
					}				 	   
				}

			else if((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {
					res.type = DOUBLE;
					double a = x.value.doubleValue;
					double b = (double) y.value.charValue;

					if(a == b) {
						res.value.doubleValue = 1.0;
						push(s,res);
						r = 1;

					}

					else {
						res.value.doubleValue = 0.0;
					    push(s,res);
						r = 1;

					}					 	    
				}

			else if((has_type(x,CHAR)) && (has_type(y,CHAR))) {
					res.type = LONG;
			        long a = (long) x.value.charValue;
				    long b = (long) y.value.charValue;

					if(a == b) {

						res.value.longValue = 1;
						push(s,res);
					    r = 1;
					}

					else {

					    res.value.longValue = 0;
						push(s,res);
						r = 1;

					}


				}
	}
    return r;

}


int menor(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"<") == 0) {

		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);

		
		if ((has_type(x,LONG)) && (has_type(y,LONG))) {  
		
			res.type = LONG;
			long a = x.value.longValue;
			long b = y.value.longValue;
		
			if(a > b) {

				res.value.longValue = 1; 
				push(s,res);
				r = 1;

		    }

			else {

				res.value.longValue = 0;	
				push(s,res);
				r = 1;

			}
		}

		else if ((has_type(x,LONG)) && (has_type(y,DOUBLE))) {  
		
				res.type = DOUBLE;
				long a = x.value.longValue;
				double b = y.value.doubleValue;
		
				if(a > b) {

					res.value.doubleValue = 1.0; 
					push(s,res);
					r = 1;

		    	}

				else {

					res.value.doubleValue = 0.0;	
					push(s,res);
					r = 1;

				}

			}

			 else if ((has_type(x,DOUBLE)) && (has_type(y,LONG))) {  
		
					res.type = DOUBLE;
					double a = x.value.doubleValue;
					long b = y.value.longValue;
		
					if(a > b) {

						res.value.doubleValue = 1.0; 
						push(s,res);
						r = 1;

		    		}

					else {

						res.value.doubleValue = 0.0;	
						push(s,res);
						r = 1;

					}

			 	}

			 	  else if ((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {  
		
							res.type = DOUBLE;
							double a = x.value.doubleValue;
							double b = y.value.doubleValue;
					
							if(a > b) {

								res.value.doubleValue = 1.0; 
								push(s,res);
								r = 1;

					    	}

							else {

								res.value.doubleValue = 0.0;	
								push(s,res);
								r = 1;

							}
					 }

					 else if ((has_type(x,LONG)) && (has_type(y,CHAR))) {  
		
								res.type = LONG;
								long a = x.value.longValue;
								long b = (long) y.value.charValue;
						
								if(a > b) {

									res.value.longValue = 1; 
									push(s,res);
									r = 1;

						    	}

								else {

									res.value.longValue = 0;	
									push(s,res);
									r = 1;

								}
						  }

						  else if ((has_type(x,CHAR)) && (has_type(y,LONG))) {  
		
									res.type = LONG;
									long a = (long)x.value.charValue;
									long b = y.value.longValue;
							
									if(a > b) {

										res.value.longValue = 1; 
										push(s,res);
										r = 1;

							    	}

									else {

										res.value.longValue = 0;	
										push(s,res);
										r = 1;

									}
							   }

							   else if ((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {  
		
										res.type = DOUBLE;
										double a = (double) x.value.charValue;
										double b = y.value.doubleValue;
								
										if(a > b) {

											res.value.doubleValue = 1.0; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.doubleValue = 0.0;	
											push(s,res);
											r = 1;

										}

								    }

								    else if ((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {  
		
										res.type = DOUBLE;
										double a = x.value.doubleValue;
										double b = (double) y.value.charValue;
								
										if(a > b) {

											res.value.doubleValue = 1.0; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.doubleValue = 0.0;	
											push(s,res);
											r = 1;

										}
								    }

								    else if ((has_type(x,CHAR)) && (has_type(y,CHAR))) {  
		
										res.type = LONG;
										long a = (long)x.value.charValue;
										long b = (long)y.value.charValue;
								
										if(a > b) {

											res.value.longValue = 1; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.longValue = 0;	
											push(s,res);
											r = 1;

										}
								    }
	}

    return r;

}



int maior(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,">") == 0) {

		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);

		
		if ((has_type(x,LONG)) && (has_type(y,LONG))) {  
		
			res.type = LONG;
			long a = x.value.longValue;
			long b = y.value.longValue;
		
			if(a < b) {

				res.value.longValue = 1; 
				push(s,res);
				r = 1;

		    }

			else {

				res.value.longValue = 0;	
				push(s,res);
				r = 1;

			}
		}

		else if ((has_type(x,LONG)) && (has_type(y,DOUBLE))) {  
		
				res.type = DOUBLE;
				long a = x.value.longValue;
				double b = y.value.doubleValue;
		
				if(a < b) {

					res.value.doubleValue = 1.0; 
					push(s,res);
					r = 1;

		    	}

				else {

					res.value.doubleValue = 0.0;	
					push(s,res);
					r = 1;

				}

			}

			 else if ((has_type(x,DOUBLE)) && (has_type(y,LONG))) {  
		
					res.type = DOUBLE;
					double a = x.value.doubleValue;
					long b = y.value.longValue;
		
					if(a < b) {

						res.value.doubleValue = 1.0; 
						push(s,res);
						r = 1;

		    		}

					else {

						res.value.doubleValue = 0.0;	
						push(s,res);
						r = 1;

					}

			 	}

			 	  else if ((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {  
		
							res.type = DOUBLE;
							double a = x.value.doubleValue;
							double b = y.value.doubleValue;
					
							if(a < b) {

								res.value.doubleValue = 1.0; 
								push(s,res);
								r = 1;

					    	}

							else {

								res.value.doubleValue = 0.0;	
								push(s,res);
								r = 1;

							}
					 }

					 else if ((has_type(x,LONG)) && (has_type(y,CHAR))) {  
		
								res.type = LONG;
								long a = x.value.longValue;
								long b = (long) y.value.charValue;
						
								if(a < b) {

									res.value.longValue = 1; 
									push(s,res);
									r = 1;

						    	}

								else {

									res.value.longValue = 0;	
									push(s,res);
									r = 1;

								}
						  }

						  else if ((has_type(x,CHAR)) && (has_type(y,LONG))) {  
		
									res.type = LONG;
									long a = (long)x.value.charValue;
									long b = y.value.longValue;
							
									if(a < b) {

										res.value.longValue = 1; 
										push(s,res);
										r = 1;

							    	}

									else {

										res.value.longValue = 0;	
										push(s,res);
										r = 1;

									}
							   }

							   else if ((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {  
		
										res.type = DOUBLE;
										double a = (double) x.value.charValue;
										double b = y.value.doubleValue;
								
										if(a < b) {

											res.value.doubleValue = 1.0; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.doubleValue = 0.0;	
											push(s,res);
											r = 1;

										}

								    }

								    else if ((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {  
		
										res.type = DOUBLE;
										double a = x.value.doubleValue;
										double b = (double) y.value.charValue;
								
										if(a < b) {

											res.value.doubleValue = 1.0; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.doubleValue = 0.0;	
											push(s,res);
											r = 1;

										}
								    }

								    else if ((has_type(x,CHAR)) && (has_type(y,CHAR))) {  
		
										res.type = LONG;
										long a = (long)x.value.charValue;
										long b = (long)y.value.charValue;
								
										if(a < b) {

											res.value.longValue = 1; 
											push(s,res);
											r = 1;

								    	}

										else {

											res.value.longValue = 0;	
											push(s,res);
											r = 1;

										}
								    }
	}
    return r;

}


int nao_logico(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"!") == 0) {

		DATA res;
		DATA x = pop(s);

		if((has_type(x,LONG))) {

			res.type = LONG;
			long a = x.value.longValue;

			if(a>0) { 

				res.value.longValue = 0;
				push(s,res);
				r = 1;

			}

			else if(a == 0) {

					res.value.longValue = 1;
			 		push(s,res);
			 		r = 1;
			 		

			 	 }
			 	 	
			     else {

			     	res.value.longValue = a;
			      	push(s,res);
			      	r = 1;

			     }
		}

		else if((has_type(x,DOUBLE))) {

				res.type = DOUBLE;
				double a = x.value.doubleValue;

				if(a > 0.0) { 

					res.value.doubleValue = 0.0;
					push(s,res);
					r = 1;

				}

				else if(a == 0.0) {

						res.value.doubleValue = 1.0;
			 			push(s,res);
			 			r = 1;
			 		

			 	 	}
			 	 	
			     	else {

			     		res.value.doubleValue = a;
			      		push(s,res);
			      		r = 1;

			    	 }
			 }

			 else if((has_type(x,CHAR))) {

						res.type = LONG;
						long a = (long) x.value.charValue;

						if(a > 0) { 

							res.value.longValue = 0;
							push(s,res);
							r = 1;

						}

						else if(a == 0) {

								res.value.longValue = 1;
					 			push(s,res);
					 			r = 1;
					 		

					 	 	}
					 	 	
					     	else {
					      		push(s,x);
					      		r = 1;

					    	}
				}
	}


    return r;

}


int e_short(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"e&") == 0) {

		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);


		if((has_type(x,LONG)) && (has_type(y,LONG))) {

			res.type = LONG;
			long a = x.value.longValue;
			long b = y.value.longValue;

			if(a == 0 || b == 0){

				res.value.longValue = 0;
				push(s,res);
				r = 1;

			}

			else {
			    res.value.longValue = a;
			    push(s,res);
			    r = 1;

			}
		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {

				res.type = DOUBLE;
				long a = x.value.longValue;
				double b = y.value.doubleValue;

				if(a == 0 || b == 0.0){
					res.value.doubleValue = 0.0 ;
					push(s,res);
					r = 1;

				}

				else {

				    res.value.doubleValue = a;
				    push(s,res);
				    r = 1;

				}
			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {

					res.type = DOUBLE;
					double a = x.value.doubleValue;
					long b = y.value.longValue;
					if((a == 0.0) | (b == 0)){

						res.value.doubleValue = 0.0;
						push(s,res);
						r = 1;

					}

					else {

					    res.value.doubleValue = a;
					    push(s,res);
					    r = 1;

					}
				}

			      else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {

							res.type = DOUBLE;
							double a = x.value.doubleValue;
							double b = y.value.doubleValue;

							if(a == 0.0 || b == 0.0){

								res.value.doubleValue = 0.0;
								push(s,res);
								r = 1;

							}

						    else {
						     	res.value.doubleValue = a;
						     	push(s,res);
						     	r = 1;

						    }
					}

					   else if((has_type(x,LONG)) && (has_type(y,CHAR))) {

								res.type = LONG;
								long a = x.value.longValue;
								long b = (long)y.value.charValue;

								if(a == 0 || b == 0){

									res.value.longValue = 0;
									push(s,res);
									r = 1;
                                }

								
							    else {

							     	res.value.longValue = a;
							     	push(s,res);
							     	r = 1;

							    }
						    }

						    else if((has_type(x,CHAR)) && (has_type(y,LONG))) {

										long a = (long) x.value.charValue;
										long b = y.value.longValue;

										if(a == 0 || b == 0){
                                            res.type = LONG;
											res.value.longValue = 0;
											push(s,res);
											r = 1;

										}

									    else {
                                            push(s,x);
									     	r = 1;
									    }
							    }

							     else if((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {

											res.type = DOUBLE;
											double a = (double) x.value.charValue;
											double b = y.value.doubleValue;

											if(a == 0.0 || b == 0.0){

												res.value.doubleValue = 0.0;
												push(s,res);
												r = 1;

											}

										    else {
										     	push(s,x);
										     	r = 1;
										    }
								      }

								      else if((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {

												res.type = DOUBLE;
												double a = x.value.doubleValue;
												double b = (double)y.value.charValue;

												if(a == 0.0 || b == 0.0){

													res.value.doubleValue = 0.0;
													push(s,res);
													r = 1;

												}

												
											    else {
											     	res.value.doubleValue = a;
											     	push(s,res);
											     	r = 1;

											    }
									       }

									       else if((has_type(x,CHAR)) && (has_type(y,CHAR))) {

													res.type = LONG;
													long a = (long) x.value.charValue;
													long b = (long) y.value.charValue;

													if(a == 0 || b == 0){

														res.value.longValue = 0;
														push(s,res);
														r = 1;
                                                    }

												
												    else {
												     	push(s,x);
												     	r = 1;
												    }				   
    	                                    }
    }
    return r;

}



int ou_short(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"e|") == 0) {

		DATA res;
		DATA x = pop(s);
		DATA y = pop(s);


		if((has_type(x,LONG)) && (has_type(y,LONG))) {

			res.type = LONG;
			long a = x.value.longValue;
			long b = y.value.longValue;

			if(a == 0){

				
				push(s,y);
				r = 1;

			}

			else if (b == 0) {
			    push(s,x);
			    r = 1;

			}

            else {
                push(s,y);
                r = 1;
            }
		}

		else if((has_type(x,LONG)) && (has_type(y,DOUBLE))) {

				
				long a = x.value.longValue;
				double b = y.value.doubleValue;

				if(a == 0) {
                    
					push(s,y);
					r = 1;

				}

				else if (b == 0.0) {
        
				    push(s,x);
				    r = 1;

				}

                else {
                    
                    push(s,y);
                    r = 1;
                }
			 }

			 else if((has_type(x,DOUBLE)) && (has_type(y,LONG))) {
				 	double a = x.value.doubleValue;
					long b = y.value.longValue;

					
                    if(a == 0.0) {
					push(s,y);
					r = 1;

				    }

				    else if (b == 0) {
                        
				        push(s,x);
				        r = 1;

				    }

                else {
                    
                    push(s,x);
                    r = 1;
                }
			 }

			      else if((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {

							
							double a = x.value.doubleValue;
							double b = y.value.doubleValue;

							if(a == 0.0) {
                                
					            push(s,y);
					            r = 1;

				            }

				            else if (b == 0.0) {
				            
				                push(s,x);
				                r = 1;

				            }

                            else {
                                res.type = DOUBLE;
                                res.value.doubleValue = b;
                                push(s,res);
                                r = 1;
                            }
			            }

					   else if((has_type(x,LONG)) && (has_type(y,CHAR))) {

								res.type = LONG;
								long a = x.value.longValue;
								long b = (long)y.value.charValue;

								if(a == 0) {
					                push(s,y);
					                r = 1;

				                }

				                else if (b == 0) {
				                    push(s,x);
				                    r = 1;

				                }

                                else {
                                    push(s,y);
                                    r = 1;
                                }
			                }  

						    else if((has_type(x,CHAR)) && (has_type(y,LONG))) {

										long a = (long) x.value.charValue;
										long b = y.value.longValue;

										if(a == 0) {
					                        push(s,y);
					                        r = 1;

				                        }

				                        else if (b == 0) {
				                            push(s,x);
				                            r = 1;

				                        }

                                        else {
                                            push(s,y);
                                            r = 1;
                                        }
			                    } 

							     else if((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {

											res.type = DOUBLE;
											double a = (double) x.value.charValue;
											double b = y.value.doubleValue;

											if(a == 0.0) {
					                            push(s,y);
					                            r = 1;

				                            }

				                            else if (b == 0.0) {
				                                push(s,x);
				                                r = 1;

				                            }

                                            else {
                                                push(s,y);
                                                r = 1;
                                            }
			                            } 

								      else if((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {

												res.type = DOUBLE;
												double a = x.value.doubleValue;
												double b = (double)y.value.charValue;

												if(a == 0.0) {
					                                push(s,y);
					                                r = 1;

				                                }

				                                else if (b == 0.0) {
				                                    push(s,x);
				                                    r = 1;

				                                }

                                                else {
                                                    push(s,y);
                                                    r = 1;
                                                }
			                                } 

									       else if((has_type(x,CHAR)) && (has_type(y,CHAR))) {

													res.type = LONG;
													long a = (long) x.value.charValue;
													long b = (long) y.value.charValue;

													if(a == 0) {
					                                    push(s,y);
					                                    r = 1;

				                                    }

				                                    else if (b == 0) {
				                                        push(s,x);
				                                        r = 1;

				                                    }   

                                                    else {
                                                        push(s,y);
                                                        r = 1;
                                                    }
			                                    } 
    }
    return r;

}



int push_m(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"e<") == 0) {

		DATA x = pop(s);
		DATA y = pop(s);

		
		if ((has_type(x,LONG)) && (has_type(y,LONG))) {  

			
			long a = x.value.longValue;
			long b = y.value.longValue;

			if(a > b) {
				push(s,y);
				r = 1;

			}

			else {
				push(s,x);
				r = 1;

			}
		}

		else if ((has_type(x,LONG)) && (has_type(y,DOUBLE))) {  

				
				long a = x.value.longValue;
				double b = y.value.doubleValue;

				if(a > b) {

					
					push(s,y);
					r = 1;

				}

				else {

					push(s,x);
					r = 1;

				}
			 }

			 else if ((has_type(x,DOUBLE)) && (has_type(y,LONG))) {  

						double a = x.value.doubleValue;
						long b = y.value.longValue;

						if(a > b) {
							push(s,y);
							r = 1;

						}

						else {

							push(s,x);
							r = 1;

						}
				  }

				  else if ((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {  

							double a = x.value.doubleValue;
							double b = y.value.doubleValue;

							if(a > b) {
								push(s,y);
								r = 1;

							}

							else {

								push(s,x);
								r = 1;

							}

				  	   }

				  	   else if ((has_type(x,LONG)) && (has_type(y,CHAR))) {  

								long a = x.value.longValue;
								long b = (long)y.value.charValue;

								if(a > b) {

									push(s,y);
									r = 1;

								}

								else {
									push(s,x);
									r = 1;
								}
					  	    }

					  	    else if ((has_type(x,CHAR)) && (has_type(y,LONG))) {  

									long a = (long)x.value.charValue;
									long b = y.value.longValue;

									if(a > b) {
										push(s,y);
										r = 1;
									}

									else {

										push(s,x);
										r = 1;

									}
						  	     }

						  	     else if ((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {  

											long a = (long)x.value.charValue;
											double b = y.value.doubleValue;

											if(a > b) {
												push(s,y);
												r = 1;

											}

											else {

												push(s,x);
												r = 1;

											}
							
							  	      }

							  	      else if ((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {  
												double a = x.value.doubleValue;
												long b = (long)y.value.charValue ;

												if(a > b) {

													push(s,y);
													r = 1;

												}

												else {
													push(s,x);
													r = 1;

												}
								  	       }

								  	       else if ((has_type(x,CHAR)) && (has_type(y,CHAR))) {  

													long a = (long)x.value.charValue;
													long b = (long)y.value.charValue;

													if(a > b) {
													
														push(s,y);
														r = 1;

													}

													else {

														push(s,x);
														r = 1;

													}
                                             }				  	        
	}

    return r;

}


int push_M(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"e>") == 0) {

		DATA x = pop(s);
		DATA y = pop(s);

		
		if ((has_type(x,LONG)) && (has_type(y,LONG))) {  

			long a = x.value.longValue;
			long b = y.value.longValue;

			if(a > b) {
				push(s,x);
				r = 1;

			}

			else {
				push(s,y);
				r = 1;

			}
		}

		else if ((has_type(x,LONG)) && (has_type(y,DOUBLE))) {  

				
				long a = x.value.longValue;
				double b = y.value.doubleValue;

				if(a > b) {

					
					push(s,x);
					r = 1;

				}

				else {

					push(s,y);
					r = 1;

				}
			 }

			 else if ((has_type(x,DOUBLE)) && (has_type(y,LONG))) {  

						double a = x.value.doubleValue;
						long b = y.value.longValue;

						if(a > b) {
							push(s,x);
							r = 1;

						}

						else {

							push(s,y);
							r = 1;

						}
				  }

				  else if ((has_type(x,DOUBLE)) && (has_type(y,DOUBLE))) {  

							double a = x.value.doubleValue;
							double b = y.value.doubleValue;

							if(a > b) {
								push(s,x);
								r = 1;

							}

							else {

								push(s,y);
								r = 1;

							}

				  	   }

				  	   else if ((has_type(x,LONG)) && (has_type(y,CHAR))) {  

								long a = x.value.longValue;
								long b = (long)y.value.charValue;

								if(a > b) {

									push(s,x);
									r = 1;

								}

								else {
									push(s,y);
									r = 1;
								}
					  	    }

					  	    else if ((has_type(x,CHAR)) && (has_type(y,LONG))) {  

									long a = (long)x.value.charValue;
									long b = y.value.longValue;

									if(a > b) {
										push(s,x);
										r = 1;
									}

									else {

										push(s,y);
										r = 1;

									}
						  	     }

						  	     else if ((has_type(x,CHAR)) && (has_type(y,DOUBLE))) {  

											long a = (long)x.value.charValue;
											double b = y.value.doubleValue;

											if(a > b) {
												push(s,x);
												r = 1;

											}

											else {

												push(s,y);
												r = 1;

											}
							
							  	      }

							  	      else if ((has_type(x,DOUBLE)) && (has_type(y,CHAR))) {  
												double a = x.value.doubleValue;
												long b = (long)y.value.charValue ;

												if(a > b) {

													push(s,x);
													r = 1;

												}

												else {
													push(s,y);
													r = 1;

												}
								  	       }

								  	       else if ((has_type(x,CHAR)) && (has_type(y,CHAR))) {  

													long a = (long)x.value.charValue;
													long b = (long)y.value.charValue;

													if(a > b) {
													
														push(s,x);
														r = 1;

													}

													else {

														push(s,y);
														r = 1;

													}
                                             }				  	        
	}

    return r;

}


int if_then_else(STACK *s, char *token) {

	int r = 0;

	if(strcmp(token,"?") == 0) {

		DATA x = pop(s);
		DATA y = pop(s);
		DATA z = pop(s);

		if((has_type(z,LONG))) {

			long c = z.value.longValue;

							if(c == 0) {
								push(s,x);
								r = 1; 

							}

							else {
								push(s,y);
								r = 1;


							}
					   }

					   else if((has_type(z,DOUBLE))) {

								double c = z.value.doubleValue;

								if(c == 0.0) {
									push(s,x);
									r = 1; 

								}

								else {
									push(s,y);
									r = 1;

								}

						    }

						    else if((has_type(z,CHAR))) {
							    	long c = (long) z.value.charValue;

										if(c == 0.0) {
											push(s,x);
											r = 1; 

										}

										else {

											push(s,y);
											r = 1;


										}

							     }
                                else if((has_type(z,STR))) {
                                    char* aux;
                                    long c = strtol(z.value.stringValue,&aux,10);
                                    if(c == 0) {
                                        push(s,x);
                                        r = 1;
                                    }
                                    else {
                                        push(s,y);
                                        r = 1;
                                    }
                                }

		
	}

    return r;
}