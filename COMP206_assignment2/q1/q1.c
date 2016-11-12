/*
 * =======================================================
 * Name:			q1.c
 * Author:			Michel Cantacuzene
 * Description:		Question1 of COMP 206 assignment 2
 * =======================================================
 */

#include <stdio.h>
#include <stdlib.h>

void translator(char* argv[]); //translator function with the important code

int main(int argc, char* argv[]){ //main function
	if (argc != 2){printf("How to use: pipe date to program and pass emplate file as argument:\n\tdate | ./a.out template_file.txt\n");exit(1);}
	translator(argv);
	return 0;
}

void translator(char* argv[]){

	char Sun[30], Mon[30], Tue[30], Wed[30], Thu[30], Fri[30], Sat[30]; // initialize the days as string arrays witha maximum of 30 characters.
	char Jan[30], Feb[30], Mar[30], Apr[30], May[30], Jun[30], Jul[30], Aug[30], Sep[30], Oct[30], Nov[30], Dec[30]; //initialize the months as string arrays with a maximum of 30 characters.

	//associate the data from stdin (the piped date input) to the correct variables (might not work on all systems
	char Day[3], Month[3], Date[2], Time[8], Zone[3], Year[4];
	
	int day;
	int month;

	char *tday, *tmonth; //pointers 
	
	//open the file stream and read the data
	FILE * dataFile;
	if((dataFile= fopen(argv[1], "r")) == NULL){
		printf("Can't read from file %s\n",argv[1]);
		exit(1);
	} else {
		// we assume that the file arangement is the same for all label files
		fscanf(dataFile," %s %s %s %s %s %s %s", Sun, Mon, Tue, Wed, Thu, Fri, Sat);
		fscanf(dataFile," %s %s %s %s %s %s %s %s %s %s %s %s", Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec);
	}

	//if (scanf("%s %s %s %s %s %s",Day,Month,Date,Time,Zone,Year) <0){printf("How to use: pipe date to program and pass emplate file as argument:\n\tdate | ./a.out template_file.txt\n");exit(1);}
	scanf("%s %s %s %s %s %s",Day,Month,Date,Time,Zone,Year);

	day = Day[0] + Day[1] + Day[2];	//we sum up the ascii codes to get the cases ex: Mon = M+o+n = 77+111+110 = 298
	month =  Month[0] + Month[1] + Month[2];  //we sum up the ascii codes to get the cases ex: Oct = O+c+t = 79+99+116 = 294
	
	// switch statement to determine the day and the month.	
	switch(day){
		case 298 : //we sum up the ascii codes to get the cases ex: Mon = M+o+n = 77+111+110 = 298
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
		default: //default not necessary but useful for debug
			printf("No value found for week\n");
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
		default: //default not necessary but useful for debug
			printf("No value found for month\n");
			exit(1);
	}
	
	printf("%s %s %s %s %s %s\n", tday, tmonth, Date, Time, Zone, Year); //print in the correct way
}
