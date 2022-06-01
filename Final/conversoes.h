#include <string.h>
#include "stack.h"


/**
 *\brief Esta é a função que é responsável por converter o valor que está no topo da Stack para o tipo LONG.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela conversão em questão.
 * 
 *@returns um valor lógico; 0 se a conversão "converte_int" não for utilizada. De outro modo, retorna 1.
 */
int converte_int(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsável por converter o valor que está no topo da Stack para o tipo DOUBLE.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela conversão em questão.
 * 
 *@returns um valor lógico; 0 se a conversão "converte_dbl" não for utilizada. De outro modo, retorna 1.
 */
int converte_dbl(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsável por converter o valor que está no topo da Stack para o tipo CHAR.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela conversão em questão.
 * 
 *@returns um valor lógico; 0 se a conversão "converte_char" não for utilizada. De outro modo, retorna 1.
 */
int converte_char(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsável por converter o valor que está no topo da Stack para o tipo STR.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela conversão em questão.
 * 
 *@returns um valor lógico; 0 se a conversão "converte_str" não for utilizada. De outro modo, retorna 1.
 */
int converte_str(STACK *s, char *token);