#include <stdio.h>

void test(int *a){
	*a +=1;
}

int main(void){
	int k=5;
	test(&k);
	printf("%d\n",k);
	return 0;
}
