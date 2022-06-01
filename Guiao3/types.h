typedef enum {
	LONG = 1,
	DOUBLE = 2,
	CHAR = 4,
	STR = 8,
	ARR = 16,
	BLK = 32
} TYPE;

typedef struct stack STACK;

typedef union value {
	long longValue;
	double doubleValue;
	char charValue;
	char *stringValue;
	STACK *arrayValue;
} VALUE;


typedef struct data {
	TYPE type;
	VALUE value;
} DATA;

typedef struct stack {

	DATA *stack;
	int sp;
	int size;

} STACK;