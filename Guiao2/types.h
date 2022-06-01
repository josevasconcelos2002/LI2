typedef enum {
	LONG,
	DOUBLE,
	CHAR,
	STR,
	ARR,
	BLK
} TYPE;

typedef union value {
	long longValue;
	double doubleValue;
	char charValue;
	char *stringValue;
} VALUE;


typedef struct {
	TYPE type;
	VALUE value;
} DATA;

typedef struct {

	DATA *stack;
	int sp;
	int size;

} STACK;