#include <string.h>
#include "manipula_stack.h"






int duplica(STACK *s, char *token){
    int r = 0;
    if(strcmp(token,"_") == 0){
        DATA x = pop(s);
        DATA dup;
        if ((has_type(x , LONG))) {
        dup.type = LONG;
        dup.value.longValue = x.value.longValue;      
        push(s,dup);
        push(s, x);
        r = 1;
        }
        else if((has_type(x , DOUBLE))) {
            dup.type = DOUBLE;
            dup.value.doubleValue = x.value.doubleValue;
            push(s,dup); 
            push(s,x);
            r = 1;
            }   

        else if ((has_type(x , CHAR))) { 
            dup.type = CHAR;
            dup.value.charValue = x.value.charValue;
            push(s,dup);                         
            push(s, x);
            r = 1;
            }

        else if ((has_type(x , STR))) {   
            dup.type = CHAR;
            dup.value.charValue = x.value.charValue;
            push(s, x);
            r = 1;
                    
            }

                      /*  else if ((has_type(DATA x , 16))) {  
        
                            ARR x = pop(s);
                            push(s, x);
                            return 1;
                            
                            }

                            else if ((has_type(DATA x , 32))) {  
        
                                BLK x = pop(s);
                                push(s, x);
                                return 1;
                                
                                }
        
    }
    
*/
    }
return r;
}





int mypop(STACK *s, char *token) {
    int r = 0;
	if(strcmp(token,";") == 0) {      
       pop(s);
       r = 1;
    }
    return r;
}





int troca2(STACK *s, char *token) {
    int r = 0;
    if(strcmp(token,"\\") == 0) {
        DATA x = pop(s);
        DATA y = pop(s);
        push(s,x);
        push(s,y);
        r = 1;

    }
    return r;
}


int roda3(STACK *s, char *token) {
    int r = 0;
    if(strcmp(token,"@") == 0) {
        DATA x = pop(s);
        DATA y = pop(s);
        DATA z = pop(s);
        push(s,y);
        push(s,x);
        push(s,z);
        r = 1;
    }
    return r;
}


int copia(STACK *s, char *token) {
    int r = 0;
    if(strcmp(token,"$") == 0) {
        DATA elem = pop(s);
        DATA res;
        if(has_type(elem,LONG)) {
            int pos = elem.value.longValue;
            res = s->stack[s->sp - pos];
            push(s,res);
            r = 1;
        }
        else if(has_type(elem,DOUBLE)) {
            int pos = (int) elem.value.longValue;
            res = s->stack[s->sp - pos];
            push(s,res);
            r = 1;
        }
    }
    return r;
}

        
             
