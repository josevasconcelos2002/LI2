#include "stack.h"


int arrayToStack(STACK *s, DATA values, char *token) {
    int r = 0;
    if((strcmp(token,"~") == 0) && has_type(s->stack[s->sp],ARR)) {
        DATA temp[]  = (DATA *) malloc(128*128);
        int i = 0;
        int top = s->stack[s->sp].value.arrayValue->sp; 
        while(i <= top) {
            temp[i] = pop(s->stack[s->sp].value.arrayValue);
            i++;
        }
        while(top>=0) { 
            push(s,temp[top])
            top--;
        }
        r = 1;
    }
    return r;

}

int concatSA(STACK *s,DATA values, char *token) {
    int r = 0;
    if((strcmp(token,"+")) && (has_type(s->stack[s->sp],ARR)) && (has_type))
}