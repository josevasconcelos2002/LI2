#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/** 
 *\brief Função que constroi uma stack, onde estarão presentes elementos do tipo DATA
 *
 *@returns stack que foi construída.
 */
STACK *new_stack();

/** 
 *\brief Função que verifica 
 *
 *@param DATA elem elemento do tipo DATA.
 *@param int mask             .
 * 
 *@returns .
 */
int has_type(DATA elem, int mask);

/** 
 *\brief Função que coloca o elemento no topo da stack.
 *
 *@param STACK *s apontador para a stack.
 *@param DATA elem elemento do tipo DATA.
 */
void push(STACK *s, DATA elem);

/** 
 *\brief Função que remove o elemento que está no topo da stack.
 *
 *@param STACK *s apontador para a stack.
 *
 *@returns o elemento da stack, que originalmente estava em 2º lugar.
 */
DATA pop(STACK *s);

/** 
 *\brief Função que verifica se a stack está vazia.
 *
 *@param STACK *s apontador para a stack.
 *
 *@returns 0 ou 1, dependendo se a stack se encontra vazia(1) ou não (0).
 */
int isEmpty(STACK *s);

/** 
 *\brief Função que verifica se a stack está cheia.
 *
 *@param STACK *s apontador para a stack.
 *
 *@returns 0 ou 1, dependendo se a stack se encontra cheia(1) ou não (0).
 */
int isFull(STACK *s);

/** 
 *\brief Função que faz print da stack.
 *
 *@param STACK *s apontador para a stack.
 */
void printStack(STACK *s);