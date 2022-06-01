#include <string.h>
#include "manipula_stack.h"






int duplica(STACK *s, char *token){
    
    if(strcmp(token,"_") == 0){

        DATA x = pop(s);
        
        if ((has_type(DATA x , 1))) {  
        
        LONG a = x.value.longValue;
        push(s, x);
        return 1;
        
        }

        else if((has_type(DATA x , 2))) {

             DOUBLE a = x.value.doubleValue;
             push(s,x);
             return 1;

             }   

             else if ((has_type(DATA x , 4))) {  
        
                  CHAR a = x.value.longValue;
                  push(s, x);
                  return 1;

                  }

                  else if ((has_type(DATA x , 8))) {  
        
                       STR a = x.value.*stringValue;
                       push(s, x);
                       return 1;
                    
                        }

                        else if ((has_type(DATA x , 16))) {  
        
                            ARR a = x.value.longValue;
                            push(s, x);
                            return 1;
                            
                            }

                            else if ((has_type(DATA x , 32))) {  
        
                                BLK a = x.value.longValue;
                                push(s, x);
                                return 1;
                                
                                }
        
    }
    

    else return 0;
}





int pop1(STACK *s, char *token) {


	if(strcmp(token,";") == 0) {
        

       pop(s);

          
    }

    else return 0;

}





int troca2(STACK *s, char *token) {


    if(strcmp(token,"\\") == 0) {
       
       TYPE Z = s;
       TYPE W = pop(s);
       (s-1) = Z;
       s = W;
        
    }

    else return 0;

}


int roda3(STACK *s, char *token) {


    if(strcmp(token,"@") == 0) {
        

        TYPE Z = s;
        TYPE W = pop(s);
        TYPE X = pop(s-1);
        s = X;
        (s-1) = Z;
        (s-2) = W;
          
    }

    else return 0;

}


int copia(STACK *s, char *token) {


    if(strcmp(token,"$") == 0) {

        int y = s;

        if ((has_type(DATA x , 1))) {  
        
        LONG x = *(s-y);
        push(s, x);
        return 1;
        
        }

        else if((has_type(DATA x , 2))) {

             DOUBLE x = *(s-y);
             push(s,x);
             return 1;

             }   

             else if ((has_type(DATA x , 4))) {  
        
                  CHAR x = *(s-y);
                  push(s, x);
                  return 1;

                  }

                  else if ((has_type(DATA x , 8))) {  
        
                       STR x = *(s-y);
                       push(s, x);
                       return 1;
                    
                        }

                        else if ((has_type(DATA x , 16))) {  
        
                            ARR x = *(s-y);
                            push(s, x);
                            return 1;
                            
                            }

                            else if ((has_type(DATA x , 32))) {  
        
                                BLK x = *(s-y);
                                push(s, x);
                                return 1;
                                
                                }
        
          
    }

    else return 0;

}