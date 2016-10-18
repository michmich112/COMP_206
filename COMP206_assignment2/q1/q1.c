#include <stdio.h>
#include <stdlib.h>

void translator(char* argv[]);

int main(int argc, char* argv[]){
	translator(argv);
	return 0;
}
void translator(char* argv[]){
	char Sun[30], Mon[30], Tue[30], Wed[30], Thu[30], Fri[30], Sat[30]; // initialize the days as string arrays witha maximum of 30 characters.
	char Jan[30], Feb[30], Mar[30], Apr[30], May[30], Jun[30], Jul[30], Aug[30], Sep[30], Oct[30], Nov[30], Dec[30]; //initialize the months as string arrays with a maximum of 30 characters.

	FILE * dataFile;
	if((dataFile= fopen(argv[1], "r")) == NULL){
		printf("Can't read from file %s\n",argv[1]);
		exit(1);
	} else {
		fscanf(dataFile," %s %s %s %s %s %s %s", Sun, Mon, Tue, Wed, Thu, Fri, Sat);
		fscanf(dataFile," %s %s %s %s %s %s %s %s %s %s %s %s", Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec);
	}

	char Day[3], Month[3], Date[2], Time[8], Zone[3], Year[4];
	scanf("%s %s %s %s %s %s",Day,Month,Date,Time,Zone,Year);
	
	int day = Day[0] + Day[1] + Day[2];
	int month = Month[0] + Month[1] + Month[2];

	char *tday, *tmonth;
	
	switch(day){
		case 298 :
			tday = Mon;
			break;
		case 302 :
			tday = Tue;
			break;
		case 288 :
			tday = Wed;
			break;
		case 305 :
			tday = Thu;
			break;
		case 289 :
			tday = Fri;
			break;
		case 296 :
			tday = Sat;
			break;
		case 310 :
			tday = Sun;
			break;	
		default:
			printf("No value found\n");
			exit(1);
	}
	
	switch(month){
		case 281 :
			tmonth = Jan;
			break;
		case 269 :
			tmonth = Feb;
			break;
		case 288 :
			tmonth = Mar;
			break;
		case 291 :
			tmonth = Apr;
			break;
		case 295 :
			tmonth = May;
			break;
		case 301 :
			tmonth = Jun;
			break;
		case 299 :
			tmonth = Jul;
			break;
		case 285 :
			tmonth = Aug;
			break;
		case 296 :
			tmonth = Sep;
			break;
		case 294 :
			tmonth = Oct;
			break;
		case 307 :
			tmonth = Nov;
			break;
		case 268 :
			tmonth = Dec;
			break;
		default:
			printf("No value found for month\n");
			exit(1);
	}
	
	printf("%s %s %s %s %s %s\n", tday, tmonth, Date, Time, Zone, Year);
}
