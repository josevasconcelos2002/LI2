/**
*\brief Definição da união de tipos dos elemento da stack 
*/
typedef enum {
	/* inteiros */
	LONG = 1,
	/* doubles */
	DOUBLE = 2,
	/* caracteres */
	CHAR = 4,
	/* strings */
	STR = 8,
	/* arrays */
	ARR = 16,
	/* blocks */
	BLK = 32
} TYPE;/**<tipos*/

typedef union value {/**<união de tipos de valores*/
	long longValue;/**<valores do tipo long*/
	double doubleValue;/**<valores do tipo double*/
	char charValue;/**<valores do tipo char*/
	char *stringValue;/**<valores do tipo string*/
	struct STACK *array;/**<valores do tipo array*/
} VALUE;
/**
 *\brief Definição da struct DATA, que guarda o tipo e o valor do elemento.
 */
typedef struct {
	TYPE type;/**<tipo do elemento*/
	VALUE value;/**<valor do elemento*/
} DATA;
/**
 *\brief Definição da struct STACK, que serve para colocar e guardar dados que sejam relevantes,tal como
 *o tamanho da stack, o apontador para a stack e o stack pointer.
 */
typedef struct {
	DATA *stack;/**<apontador para stack*/
	int sp;/**<stack pointer*/
	int size;/**<tamanho da stack*/
} STACK;