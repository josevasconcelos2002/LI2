#include "arrayStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/**
 *\brief Esta é a função responsável por colocar no topo da stack, o valor do elemento, que anteriormente ocupava esse lugar.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que corresponde ao o que utilizador introduziu.
 * 
 *@returns um valor lógico; 0 se o operador  "val" não for utilizada. De outro modo, retorna 1.
 */
int val(STACK *s, char *token);

/**
 *\brief Esta é a função responsável por executar todas as operações
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que corresponde ao o que utilizador introduziu.
 *@param values que corresponde ao array de valores das variaveis
 * 
 *@returns um valor lógico; 0 se não conseguir executar qualquer operação. De outro modo, retorna 1.
 */

int handle(STACK *s, DATA *values, char *token);

/**
 *\brief Esta é a função responsável por ler o input.
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que verifica se o que o utilizador introduz é igual ao símbolo responsável pela leitura do input.
 * 
 *@returns 0 se o operador "readinput" não for utilizada. De outro modo, retorna 1.
 */

int readinput(STACK *s,char *token);

/**
 *\brief Função responsavel por dar parse à linha
 *
 *@param line linha que vai ser separada
 * 
 *@returns um valor lógico; 0 se token for diferente de "l".De outro modo, retorna 1 se conseguir ler uma string
 */

void parse(char *linha);

/**
 *\brief Função que trata das variaveis
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que corresponde ao o que utilizador introduziu.
 *@param values que corresponde ao array com o valor das variaveis
 * 
 *
 */

int var(STACK* s, DATA *values, char *token);

/**
 *\brief Esta é a função responsável por alterar o valor das variaveis para o valor que se encontra no topo da stack
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que corresponde ao o que utilizador introduziu.
 *@param n que corresponde a variavel a ser alterada
 * 
 *@returns 0 se token for igual a :v, com v pertencente as variaveis. De outro modo, retorna 1.
 */

void switchValValue(STACK *s, DATA *values, char n);

/**
 *\brief Esta é a função responsável por transformar o que se encontra entre ( [] ) numa Stack, para depois operar com arrayValue
 *
 *@param line que corresponde a linha onde vamos delimitar o array
 *@param rest que corresponde ao resto da linha sem o array 
 *@param values que corresponde ao array com o valor das variaveis
 * 
 *@returns de um array dentro de uma stack
 */
STACK *doStack(char *line, char **rest, DATA *values);

/**
 *\brief Esta é a função responsável por criar a stack e e realizar as operações necessarios sobre os tokens obtidos
 *
 *@param line corresponde a linha introduzida pelo utilizador
 *@param s corresponde a stack
 *@param values que corresponde ao array com o valor das variaveis
 * 
 *@returns stack com todos os elementos
 */

STACK *makeStack(char* line, DATA *values, STACK *s);

/**
 *\brief Esta é a função responsável por dar push para a stack da transformação de string em array
 *
 *@param s stack onde retiramos os valores e colocamos o resultado.
 *@param token que corresponde ao o que utilizador introduziu.
 *@param values que corresponde ao array com o valor das variaveis
 * 
 *@returns 0 se a função não for utilizada . Retorna 1 se a string introduzida estiver entre aspas ("");
 */

char* doArrString (char* line, char **rest);
