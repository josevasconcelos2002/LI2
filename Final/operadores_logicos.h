#include "operadores.h"

/**
 *\brief Esta é a função que verifica se os dois ultimos elementos colocados na stack são iguais.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "igual" não for utilizada. De outro modo, retorna 1.
 */
int igual(STACK *s, char *token);

/**
 *\brief Esta é a função que verifica se o elemento abaixo do que está no topo da stack é menor do que está no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "menor" não for utilizada. De outro modo, retorna 1.
 */
int menor(STACK *s, char *token);

/**
 *\brief Esta é a função que verifica se o elemento abaixo do que está no topo da stack é maior do que está no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "maior" não for utilizada. De outro modo, retorna 1.
 */
int maior(STACK *s, char *token);

/**
 *\brief Esta é a função responsável por realizar a operação "nao_logico", do elemento que se encontra no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "nao_logico" não for utilizada. De outro modo, retorna 1.
 */
int nao_logico(STACK *s, char *token);

/**
 *\brief Esta é a função responsável por realizar a operação "e_short", dos dois elementos que se encontram no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "e_short" não for utilizada. De outro modo, retorna 1.
 */
int e_short(STACK *s, char *token);

/**
 *\brief Esta é a função responsável por realizar a operação "ou_short", dos dois elementos que se encontram no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "ou_short" não for utilizada. De outro modo, retorna 1.
 */
int ou_short(STACK *s, char *token);

/**
 *\brief Esta é a função que verifica qual o elemento é menor, se o que está no topo, ou o que está imediatamente abaixo.
 * Faz push do menor, colocando-o no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "push_m" não for utilizada. De outro modo, retorna 1.
 */
int push_m(STACK *s, char *token);

/**
 *\brief Esta é a função que verifica qual o elemento é maior, se o que está no topo, ou o que está imediatamente abaixo.
 * Faz push do maior, colocando-o no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "push_M" não for utilizada. De outro modo, retorna 1.
 */
int push_M(STACK *s, char *token);

/**
 *\brief Esta é a função responsável por realizar a operação "if_then_else", dos três elementos que se encontram no topo da stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação lógica em questão.
 * 
 *@returns um valor lógico; 0 se o operador lógico "if_then_else" não for utilizada. De outro modo, retorna 1.
 */
int if_then_else(STACK *s, char *token);