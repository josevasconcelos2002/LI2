#include "operadores.h"

int igual(STACK *s, char *token);
int menor(STACK *s, char *token);
int maior(STACK *s, char *token);
int nao_logico(STACK *s, char *token);
int e_short(STACK *s, char *token);
int ou_short(STACK *s, char *token);
int push_m(STACK *s, char *token);
int push_M(STACK *s, char *token);
int if_then_else(STACK *s, char *token);