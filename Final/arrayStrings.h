#include "manipula_stack.h"
#include <string.h>

/**
 *\brief Função responsável por fazer push de todos os elementos da stack para o Array
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (~) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int arrayToStack(STACK *s,char *token);

/**
 *\brief Função responsável por concatenar dois arrays ou duas Strings ou um array e uma string
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (+) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int concatSA(STACK *s,char *token);

/**
 *\brief Função responsável por repetir um array ou uma string x vezes, em que x é o elemento(LONG) anterior ao operando referente a esta função
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (*) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int concatVSA(STACK *s,char *token);

/**
 *\brief Função responsável por fornecer o elemento do array ou da string na posição x, em que x é o elemento(LONG) anterior ao operando referente a esta função
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (=) nao for igual ao token ou 1 se este for igual e a função for executada 
 */
int byIndex(STACK *s,char *token);

/**
 *\brief Função responsável por calcular elemento do principio (<) ou fim (>) da stack ou da string, com range x, em que x é o elemento(LONG) anterior ao operando referente a esta função
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (< ou >) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int getElem(STACK *s,char *token);

/**
 *\brief Função responsável por remover um elemento do principio (() ou fim ()) da stack ou da string e dar push do mesmo para o topo da stack
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (( ou )) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int removeElem(STACK *s,char *token);

/**
 *\brief Função responsável por calcular o tamanho do array ou string se o elemento no topo da stack for um dos anteriores, ou por criar um array com os elemento de 0 a x, em que x é o elemento(LONG) anterior ao operando referente a esta função
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (,) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int byRange(STACK *s,char *token);

/**
 *\brief Função responsável por calcular o endereço em que b ocorre em a
 *
 *@param a string em que a procura vai ocorrer
 *@param b string que vai ser procurada
 * 
 *@returns retorna o indice em que b ocorre em a, ou -1 se não encontrar
 */

int subStringInString(char a[], char b[]);

/**
 *\brief Função responsável por procurar o ultimo elemento da stack (string) no penultimo elemento (string)
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (#) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int searchSubString (STACK *s,char *token);

/**
 *\brief Função responsável por calcular no penultimo elemento da stack(string) os elementos limitados pelo ultimo elemento da stack(string)
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * 
 *@returns 0 se o operador (/) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int sepString(char *token, STACK *s);

/**
 *\brief Função responsável por calcular numa string os elementos separados por whitespace
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * /
 *@returns 0 se o operador (S/) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int sepWhite(STACK *s, char *token);

/**
 *\brief Função responsável por calcular numa string os elementos separados por newlines
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela operação em questão.
 * /
 *@returns 0 se o operador (N/) nao for igual ao token ou 1 se este for igual e a função for executada 
 */

int sepNewLine(STACK *s, char *token);





