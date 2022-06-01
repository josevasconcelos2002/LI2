#include "arrayStrings.h"


int arrayToStack(STACK *s, char *token) {
    
    int r = 0;
    if((strcmp(token,"~") == 0) && (s->stack[s->sp].type == 16)) {
       
        DATA *temp  = (DATA*) malloc(32*32);
        int i = 0;
        int top = s->stack[s->sp].value.arrayValue->sp; 
        while(i <= top) {
            
            temp[i] = pop(s->stack[s->sp].value.arrayValue);
            i++;

        }

        while(top>=0) { 
            
            push(s,temp[top]);
            top--;

        }
        r = 1;
    }
  return r;

}

int concatSA(STACK *s,char *token) {
    
    int r = 0;
    if((strcmp(token,"+")) && ((s->stack[s->sp].type == ARR) || (s->stack[s->sp-1].type == ARR))) {
        
        if(has_type(s->stack[s->sp-1],ARR) && (s->stack[s->sp].type != ARR)) {
           
            DATA x;
            DATA y;
            x = pop(s);
            y=pop(s);
            push(y.value.arrayValue,x);
            push(s,y);
            r=1;

        }
        else if((s->stack[s->sp - 1].type!=ARR) && (s->stack[s->sp].type == ARR)) {
               
                DATA *aux;
                STACK *arrAux;
                DATA res;
                arrAux = new_stack();
                int i , top;
                aux = (DATA *) malloc(32*32);
                top = s->stack[s->sp].value.arrayValue->sp;
                for(i = 0; i <= top; i++) {

                    aux[i] = pop(s->stack[s->sp].value.arrayValue);

                }

                pop(s);
                aux[i] = pop(s);
                while(i>=0) {
                    
                    push(arrAux,aux[i]);

                }

                res.type = ARR;
                res.value.arrayValue = arrAux;
                push(s,res);
                r = 1;

             }

             else if((s->stack[s->sp].type == ARR) && (s->stack[s->sp - 1].type == ARR)) {
                
                    int i = 0;
                    int top = s->stack[s->sp].value.arrayValue->sp;
                    DATA *aux = (DATA *) malloc(32*32);
                    while(i<=top) {

                        aux[i] = pop(s->stack[s->sp].value.arrayValue);
                        i++;

                    }

                    pop(s);
                    i = top;
                    while(i >= 0) {

                        push(s->stack[s->sp].value.arrayValue,aux[i]);
                        i--;

                    }
                    r = 1;
                  }
    }
  return r;

}


int concatVSA(STACK *s, char *token) {
    
    int r = 0;
    if((strcmp(token,"*") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp - 1].type == ARR)) {
       
        int i = 0;
        DATA xTimes = pop(s);
        DATA arr = pop(s);
        int top = arr.value.arrayValue->sp;
        DATA *aux = malloc(32*32);
        while(i<=top) {

            aux[i] = pop(arr.value.arrayValue);
            i++;

        }

        for(int j = 0;j<xTimes.value.longValue;j++) {
            
            for(int k = top;k>=0;k--) {

                push(arr.value.arrayValue,aux[k]);

            }
        }

        push(s,arr);
        r = 1;
        
    }

    else if((strcmp(token,"*") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp - 1].type == STR)) {
        
            DATA xTimes = pop(s);
            DATA str = pop(s);
            DATA res;
            res.type = STR;
            res.value.stringValue = strdup(str.value.stringValue);
            for(int i = 1;i<xTimes.value.longValue;i++) {

                res.value.stringValue = strcat(res.value.stringValue,str.value.stringValue);

            }

            push(s,res);
            r = 1;

         }
  return r;

}


int byIndex(STACK *s, char *token) {
    
    int r = 0;
    if((strcmp(token,"=") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == ARR)) {
        
        DATA indice;
        DATA arr;
        DATA res;
        indice = pop(s);
        arr = pop(s);
        if(has_type(arr.value.arrayValue->stack[indice.value.longValue],ARR)) {
            
            res.type = ARR;
            res.value.arrayValue = arr.value.arrayValue->stack[indice.value.longValue].value.arrayValue;
            r = 1;

        }

        else {
           
            res.type = LONG;
            res.value.longValue = arr.value.arrayValue->stack[indice.value.longValue].value.longValue;
            r = 1;

        }

        push(s,res);
        
    }

    else if((strcmp(token,"=") == 0)  && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == STR)) {
       
            DATA indice = pop(s);
            DATA str = pop(s);
            DATA res;
            res.type = CHAR;
            res.value.charValue = str.value.stringValue[indice.value.longValue];
            push(s,res);
            r = 1;
 
         }
  return r;

}


int getElem(STACK *s,char *token) {
    
    int r = 0;
    if((strcmp(token,"<") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == ARR)) {
        
        DATA *aux = (DATA *) malloc(32*32);
        DATA range = pop(s);
        DATA arr = pop(s);
        int j = 0;
        int top = arr.value.arrayValue->sp;
        for(int i = top; i>=0 ;i++) {

            DATA x = pop(arr.value.arrayValue);
            aux[i] = x;

        }

        while(j<range.value.longValue) {
            
            push(s,aux[j]);
            j++;

        }

        r = 1;
    }
    
    else if((strcmp(token,">") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == ARR)) {
        
            DATA *aux = (DATA *) malloc(32*32);
            DATA range = pop(s);
            DATA arr = pop(s);
            int top = arr.value.arrayValue->sp;
            int j = range.value.longValue;
            for(int i = top; i>=0 ;i++) {

                DATA x = pop(arr.value.arrayValue);
                aux[i] = x;

            }

            for(int x = top - range.value.longValue + 1; j>0 ; j-- , x++) {
               
                push(s,aux[x]);

            }

            r = 1;

         }

         else if((strcmp(token,"<") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == STR)) {
            
                int i = 0;
                DATA range = pop(s);
                DATA str = pop(s);
                DATA res;
                res.type = STR;
                res.value.stringValue = strdup(str.value.stringValue);
                while(res.value.stringValue[i] && i<range.value.longValue) {
                    
                    i++;

                }

                res.value.stringValue[i] = '\0';
                push(s,res);
                r = 1;

              }

              else if((strcmp(token,">") == 0) && (s->stack[s->sp].type == LONG) && (s->stack[s->sp-1].type == STR)) {
                   
                        int i = 0,j = 0;
                        char* aux = malloc(32*32);
                        DATA range = pop(s);
                        DATA str = pop(s);
                        DATA res;
                        res.type = STR;
                        while(str.value.stringValue[i]!='\0') {
                            
                            i++;

                        }
                        
                        i = i-range.value.longValue;
                        while(str.value.stringValue[i] && j<range.value.longValue) {
                           
                            aux[j] = str.value.stringValue[i];
                            i++;
                            j++;

                        }

                        res.value.stringValue = aux;
                        push(s,res);
                        r = 1;
                     
                   }
  return r;
           
}


int removeElem(STACK *s,char *token) {
    
    int r = 0;
    if(((strcmp(token,")") == 0) || (strcmp(token,"(") == 0)) && (s->stack[s->sp].type == ARR)) {
        
        if(strcmp(token,")") == 0) {
            
            DATA x;
            DATA arr;
            arr = pop(s);
            x = pop(arr.value.arrayValue);
            push(s,arr);
            push(s,x);
            r = 1;

        }

        else if(strcmp(token,"(") == 0) {
            
                DATA arr = pop(s);
                STACK *arrAux = new_stack();
                DATA res;
                int i = 0;
                DATA *aux = malloc(32*32);
                int top = arr.value.arrayValue->sp;
                while(i <= top) {

                    aux[i] = pop(arr.value.arrayValue);
                    i++;

                }

                i = top;
                res = aux[top];
                top--;
                while(top>=0) {

                    push(arrAux,aux[top]);
                    top--;

                }

                arr.value.arrayValue = arrAux;
                push(s,arr);
                push(s,res);
                r = 1;

             }
    }

    else if(((strcmp(token,")") == 0) || (strcmp(token,"(") == 0)) && (s->stack[s->sp].type == STR)) {
        
                if(strcmp(token,")") == 0) {
                   
                    DATA x = pop(s);
                    DATA res;
                    res.type = CHAR;
                    res.value.charValue = x.value.stringValue[strlen(x.value.stringValue)-1];
                    x.value.stringValue[strlen(x.value.stringValue) - 1] = '\0';
                    push(s,x);
                    push(s,res);
                    r = 1;

                }

                else if(strcmp(token,"(") == 0) {
                   
                        DATA x = pop(s);
                        DATA res;
                        res.type = CHAR;
                        res.value.charValue = x.value.stringValue[0];
                        x.value.stringValue = strdup(x.value.stringValue +1);
                        push(s,x);
                        push(s,res);
                        r = 1;

                     }
         }
  return r;

}


int byRange(STACK *s,char *token) {
    
    int r = 0;
    if((strcmp(token,",") == 0) && (s->stack[s->sp].type == LONG)) {
        
        DATA x = pop(s);
        int range = x.value.longValue;
        DATA aux;
        aux.type = LONG;
        DATA arr;
        arr.type = ARR;
        arr.value.arrayValue = new_stack();
        for(int i = 0;i<range;i++) {

            aux.value.longValue = i;
            push(arr.value.arrayValue,aux);

        }

        push(s,arr);
        r = 1;
    }

    else if((strcmp(token,",") == 0) && (s->stack[s->sp].type == ARR)) {
        
            long size;
            printf("erro");
            DATA arr;
            DATA res;
            arr = pop(s);
            res.type = LONG;
            size = 1 + arr.value.arrayValue->sp;
            res.value.longValue = size;
            push(s,res);
            r = 1;

         }
  return r;

}


int searchSubString (STACK *s,char *token) {
    
    int r = 0;
    if((strcmp(token,"#") == 0) && (has_type(s->stack[s->sp],STR)) && (has_type(s->stack[s->sp - 1],STR))) {
        
        DATA res;
        int aux;
        res.type = LONG;
        DATA subString = pop(s);
        DATA str = pop(s);
        aux = subStringInString(str.value.stringValue,subString.value.stringValue);
        if(str.value.stringValue[aux]!='\0') {

            res.value.longValue = aux;

        }

        else res.value.longValue = -1;
        push(s,res);
        r = 1;

    }
  return r;

}
     

int subStringInString(char a[], char b[]) {
   
    int i = 0, j = 0, indice = 0, r = 0;
    if(b[0] == '\0') r = strlen(a);

    else if(a[0] == '\0' && b[0] == '\0') r = 0;

    else {
        for(;b[i];i++) {
            for(;a[j] && b[i]!='\0';j++) {
                if(b[0] == a[j]) {
                    indice = j;
                    i++;
                }
                else if(b[i] == a[j]) {
                    
                        i++;
                    
                     }
                     else if(i!=0 && b[i]!=a[j]) {
                           
                            i = 0;
                            j--;

                          }
            }
        }
        if(b[i] == '\0') r = indice;

        else r = -1;
    }
  return r;
   
}


int sepString(char *token, STACK *s){
    
    int r = 0;
    if(strcmp(token, "/") == 0 && s->stack[s->sp].type == STR && s->stack[s->sp - 1].type == STR){
       
        DATA limitador = pop(s);
        DATA str = pop(s); 
        char *token;
        DATA arr;
        DATA aux;
        aux.type = STR;
        arr.type = ARR;
        arr.value.arrayValue = new_stack();
        token = strtok(str.value.stringValue, limitador.value.stringValue);
        while(token != NULL){

            aux.value.stringValue = strdup(token);
            push(arr.value.arrayValue, aux);
            token = strtok(NULL, limitador.value.stringValue);

        }

        push(s, arr);
        r = 1;

    }
  return r;

int sepWhite(STACK *s, char *token){
    int r = 0;
    if(strcmp(token, "S/") == 0 && s->stack[s->sp].type == STR){
        DATA str = pop(s); 
        char *token;
        DATA arr;
        DATA aux;
        aux.type = STR;
        arr.type = ARR;
        arr.value.arrayValue = new_stack();
        token = strtok(str.value.stringValue, " ");
        while(token != NULL){
            aux.value.stringValue = strdup(token);
            push(arr.value.arrayValue, aux);
            token = strtok(NULL, " ");
        }
        push(s, arr);
        r = 1;
    }


    return r;
}

int sepNewLine(STACK *s, char* token){
    int r = 0;
    if(strcmp(token, "N/") == 0 && s->stack[s->sp].type == STR){
        DATA str = pop(s); 
        char *token;
        DATA arr;
        DATA aux;
        aux.type = STR;
        arr.type = ARR;
        arr.value.arrayValue = new_stack();
        token = strtok(str.value.stringValue, "\n");
        while(token != NULL){
            aux.value.stringValue = strdup(token);
            push(arr.value.arrayValue, aux);
            token = strtok(NULL, "\n");
        }
        push(s, arr);
        r = 1;
    }


    return r;
}
v
