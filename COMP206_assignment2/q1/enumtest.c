#include <stdio.h>
int main(void){
	enum{a,b=2,c,d};
	printf("%d %d %d %d\n",a,b,c,d);
	return 0;
}
