#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handle.h"


int main(){
	
    char line[BUFSIZ];
	if(fgets(line,BUFSIZ, stdin)!= NULL){
		
        parse(line);

	}
 return 0;

}