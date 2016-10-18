#include <stdio.h>

int main(int argc,char *argv[]){
	char Day[3], Month[3], Date[2], Time[8], Zone[3], Year[4];
	scanf("%s %s %s %s %s %s",Day,Month,Date,Time,Zone,Year);
	printf("%s %s %s %s %s %s\n", Year, Time, Zone, Month, Day, Date);
	return 0;
}
