#include "operadores_logicos.h"

/**
 *\brief Esta é a função que é responsavel por duplicar o valor que está topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação de manipulação de stack em questão.
 * 
 *@returns um valor lógico; 0 se a operação "duplica" não for utilizada. De outro modo, retorna 1.
 */
int duplica(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por remover o valor que está topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação de manipulação de stack em questão.
 * 
 *@returns um valor lógico; 0 se a operação "mypop" não for utilizada. De outro modo, retorna 1.
 */
int mypop(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por trocar o valor que está topo da Stack, com o que está imediatamente abaixo.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação de manipulação de stack em questão.
 * 
 *@returns um valor lógico; 0 se a operação "troca2" não for utilizada. De outro modo, retorna 1.
 */
int troca2(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por rodar os 3 valores que estão mais próximos do topo da Stack, inclusive.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação de manipulação de stack em questão.
 * 
 *@returns um valor lógico; 0 se a operação "roda3" não for utilizada. De outro modo, retorna 1.
 */
int roda3(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por duplicar o valor que está topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação de manipulação de stack em questão.
 * 
 *@returns um valor lógico; 0 se a operação "copia" não for utilizada. De outro modo, retorna 1.
 */
int copia(STACK *s, char *token);