/*
 * =======================================================
 * Name:			q2.c
 * Author:			Mcihel Cantacuzene
 * Description:		Question2 of COMP 206 assignment 2
 * =======================================================
 */

#include <stdio.h>
#include <stdlib.h>

static int DAYSIZE;
static char Jan[30], Feb[30], Mar[30], Apr[30], May[30], Jun[30], Jul[30], Aug[30], Sep[30], Oct[30], Nov[30], Dec[30]; //initialize the months as string arrays with a maximum of 30 characters.
static char Sun[30], Mon[30], Tue[30], Wed[30], Thu[30], Fri[30], Sat[30]; // initialize the days as string arrays witha maximum of 30 characters.
static char* Days[]={Sun,Mon,Tue,Wed,Thu,Fri,Sat};

void translator(char* argv[]); //translator function with the important code
void drawCalendar(int *currentDay);
void drawLine(int lineSize);
void completeSpaces(int i);
void printMonth(int month);
void printWeek();
void writeWeekday(int pos);

int main(int argc, char* argv[]){
	if(argc<4 || atoi(argv[2])<2 || atoi(argv[3])<1 || atoi(argv[3])>7){printf("Input is: $./executable label_file.txt <int1> <int2>\n\t<int1> >= 2\n\t1<= <int2> <=7\n");exit(1); //Be carefull if argv[2]==1
	}else {DAYSIZE =atoi(argv[2]);}
	int lineLength=7*(DAYSIZE+3);
	int currentDay = atoi(argv[3]), i;
	
	translator(argv);
	
	for(i=1;i<=12;i++){
		drawLine(lineLength);
		printMonth(i);
		drawLine(lineLength);
		printWeek();
		drawLine(lineLength);
		drawCalendar(&currentDay);
	}
	
	return 0;
}

void printMonth(int month){
	enum{january=1,febuary,march,april,may,june,july,august,september,october,november,december}; //not necessary, just to make the code clearer
	switch(month){
		case january:
			printf("* %s\n",Jan);
			break;
		case febuary:
			printf("* %s\n",Feb);
			break;
		case march:
			printf("* %s\n",Mar);
			break;
		case april:
			printf("* %s\n",Apr);
			break;
		case may:
			printf("* %s\n",May);
			break;
		case june:
			printf("* %s\n",Jun);
			break;
		case july:
			printf("* %s\n",Jul);
			break;
		case august:
			printf("* %s\n",Aug);
			break;
		case september:
			printf("* %s\n",Sep);
			break;
		case october:
			printf("* %s\n",Oct);
			break;
		case november:
			printf("* %s\n",Nov);
			break;
		case december:
			printf("* %s\n",Dec);
			break;
		default:
			printf("No month to display\n");
	}
}

void printWeek(){
	int i;
	for(i=1;i<8;i++){
		writeWeekday(i-1);
	}
	printf("\n");
}

void writeWeekday(int pos){
	int i,j;
	printf("* ");
	for(i=0;i<DAYSIZE;i++){
		if(Days[pos][i]=='\0'){
			printf(" ");
		}else{
			printf("%c",Days[pos][i]);
		}
	}
	printf(" ");
}

void drawLine(int lineSize){
	int i;
	for (i=0;i<lineSize;i++){
		printf("*");
	}
	printf("\n");
}

void drawCalendar(int *currentDay){
	int i;
	if (*currentDay==8){*currentDay=1;}
	for(i=1;i<*currentDay;i++){
		printf("* ");
		completeSpaces(0);
	}
	for(i=1;i<31;i++){
		if (*currentDay==8){printf("\n");*currentDay=1;}
		printf("* %d",i);
		completeSpaces(i);
		printf(" ");
		*currentDay+=1;
	}
	for(i=0;i<(7-*currentDay)+1;i++){
		printf("* ");
		completeSpaces(0);
	}
	printf("\n");
}

void completeSpaces(int i){
	if(i==0){
		for(i;i<DAYSIZE+1;i++){
			printf(" ");
		}
	}else{
		int x = i>=10?DAYSIZE-2:DAYSIZE-1;
		for(i=0;i<x;i++){
			printf(" ");
		}
	}
}

void translator(char* argv[]){
	//printf("started translator");

	//open the file stream and read the data
	FILE * dataFile;
	if((dataFile= fopen(argv[1], "r")) == NULL){
		printf("Can't read from file %s\n",argv[1]);
		exit(1);
	} else {
		// we assume that the file arangement is the same for all label files
		fscanf(dataFile," %s %s %s %s %s %s %s", Sun, Mon, Tue, Wed, Thu, Fri, Sat);
		fscanf(dataFile," %s %s %s %s %s %s %s %s %s %s %s %s", Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec);
		//printf(" %s %s %s %s %s %s %s\n", Sun, Mon, Tue, Wed, Thu, Fri, Sat);
		//printf(" %s %s %s %s %s %s %s %s %s %s %s %s\n", Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec);

	}
	fclose(dataFile);

}
