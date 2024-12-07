#include <stdlib.h>
#include <stdio.h>




void streamCleaner(){
	int ch;
	while(((ch = getchar()) != '\n') && (ch != EOF)){
	}
}
