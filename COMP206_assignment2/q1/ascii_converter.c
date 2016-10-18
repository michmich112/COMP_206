#include <stdio.h>
int main(int argc, char *argv[]){
	long int letter = 0;
	int i=0;
	while(argv[1][i] != '\0'){
		letter += argv[1][i];	
		i++;
	}
	printf("%s -> %ld\n",argv[1],letter);
	return 0;
}
