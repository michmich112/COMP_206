#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	char tmp;
	printf("Awaiting input:");
	tmp=getc(stdin);
	while(tmp!='\n'){
		printf("%c",tmp);
		tmp=getc(stdin);
	}
	printf("\n");
	return 0;
}