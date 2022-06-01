#include <math.h>
#include "conversoes.h"

/**
 *\brief Esta é a função que faz "bitwise xor" dos dois ultimos elementos colocados na stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "myxor" não for utilizada. De outro modo, retorna 1.
 */
int myxor(STACK *s, char *token);

/**
 *\brief Esta é a função que faz "bitwise not" dos dois ultimos elementos colocados na stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "nao" não for utilizada. De outro modo, retorna 1.
 */
int nao(STACK *s, char *token);

/**
 *\brief Esta é a função que faz "bitwise or" dos dois ultimos elementos colocados na stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "ou" não for utilizada. De outro modo, retorna 1.
 */
int ou(STACK *s, char *token);

/**
 *\brief Esta é a função que faz "bitwise and" dos dois ultimos elementos colocados na stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "e" for não utilizada. De outro modo, retorna 1.
 */
int e(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a exponenciação dos dois números que se encontram no topo da Stack, sendo um a base e o outro o expoente.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "expoente" não for utilizada. De outro modo, retorna 1.
 */
int expoente(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por incrementar o número que se encontra no topo da Stack em 1.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "incrementa" não for utilizada. De outro modo, retorna 1.
 */
int incrementa(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por decrementar o número que se encontra no topo da Stack em 1.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "decrementa" não for utilizada. De outro modo, retorna 1.
 */
int decrementa(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a operação "modulo", ou seja, calcular o resto da divisão, entre os dois números que se encontram no topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "modulo" não for utilizada. De outro modo, retorna 1.
 */
int modulo(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a operação "dividir", ou seja, calcular o quociente da divisão, entre os dois números que se encontram no topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "dividir" não for utilizada. De outro modo, retorna 1.
 */
int dividir(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a multiplicação dos dois números que se encontram no topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "mult" for utilizada. De outro modo, retorna 1.
 */
int mult(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a subtração dos dois números que se encontram no topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "sub" for utilizada. De outro modo, retorna 1.
 */
int sub(STACK *s, char *token);

/**
 *\brief Esta é a função que é responsavel por realizar a soma dos dois números que se encontram no topo da Stack.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação aritmética em questão.
 * 
 *@returns um valor lógico; 0 se a operação "soma" for utilizada. De outro modo, retorna 1.
 */
int soma(STACK *s, char *token);