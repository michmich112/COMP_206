#include <stdio.h>
#include <stdlib.h>

void getData(char Sun[],char Mon[],char Tue[],char Wed[],char Thu[],char Fri[],char Sat[],char Jan[],char Feb[],char Mar[],char Apr[],char May[],char Jun[],char Jul[],char Aug[],char Sep[],char Oct[],char Nov[],char Dec[],char* argv[]);

int main(int argc, char* argv[]){
	int size = 30;
	
	char Sun[size], Mon[size], Tue[size], Wed[size], Thu[size], Fri[size], Sat[size]; // initialize the days as string arrays witha maximum of 30 characters.
	char Jan[size], Feb[size], Mar[size], Apr[size], May[size], Jun[size], Jul[size], Aug[size], Sep[size], Oct[size], Nov[size], Dec[size]; //initialize the months as string arrays with a maximum of 30 characters.
		
	char Day[3], Month[3], Date[2], Time[8], Zone[3], Year[4]; 
	
	int day = Day[0] + Day[1] + Day[2]; //we get the numerical value of the 
	int month = Month[0] + Month[1] + Month[2];

	char *tday, *tmonth; //pointer
	
	getData(Sun,Mon,Tue,Wed,Thu,Fri,Sat,Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,argv);

	scanf("%s %s %s %s %s %s",Day,Month,Date,Time,Zone,Year);
	
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
	return 0;
}

void getData(char Sun[],char Mon[],char Tue[],char Wed[],char Thu[],char Fri[],char Sat[],char Jan[],char Feb[],char Mar[],char Apr[],char May[],char Jun[],char Jul[],char Aug[],char Sep[],char Oct[],char Nov[],char Dec[],char* argv[]){

	FILE * dataFile;
	if((dataFile= fopen(argv[1], "r")) == NULL){
		printf("Can't read from file %s\n",argv[1]);
		exit(1);
	} else {
		fscanf(dataFile," %s %s %s %s %s %s %s", Sun, Mon, Tue, Wed, Thu, Fri, Sat);
		fscanf(dataFile," %s %s %s %s %s %s %s %s %s %s %s %s", Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec);
	}
	fclose(dataFile);
}


