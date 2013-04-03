#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define BOOL int
#define true 1
#define false 0

typedef struct{
	int number;
	BOOL drawn;
} tile_t;

void delay(double seconds);
void initializeArray(int array[], int size);
int draw(BOOL drawnNumbers[]);
char getLetter(int num);
void createCard(tile_t card[6][6], BOOL inCardNumbers[]);
void markInCard(tile_t card[6][6], int num);
BOOL checkWinner(int pattern, tile_t card[6][6]);
void displayPattern(int pattern);
void printCard(tile_t card[6][6]);


/* --------------------- NOTE: Indexing always start at 1 ---------------------------*/
int main(){
	BOOL drawnNumbers[76];
	BOOL inCardNumbers[76];													//this is to know if the number has already been drawn
	tile_t card1[6][6];														//2d array card[row][col]
	int i=0, j=0, luckyNum, flag=0;
	int pattern=0;
	
	srand((unsigned)time(0));
	pattern = (rand() % 7)+1;
	displayPattern(pattern);

	initializeArray(inCardNumbers, 76);
	for(i=1;i<6;i++){
		for(j=1;j<6;j++){
			card1[i][j].drawn = false;
		}
	}
	
	card1[3][3].drawn = true;
	createCard(card1, inCardNumbers);

	printf("\n");
	
	//initialize drawnNumbers array
	initializeArray(drawnNumbers, 76);
	while(1){
   	luckyNum = draw(drawnNumbers);
   	printf("Number is being drawn");
   	delay(0.5); printf(".");
   	delay(1.0); printf(".");
   	delay(1.0); printf(".\n");
   	printf("On the letter %c!\n", getLetter(luckyNum));
   	printf("The number is");
   	delay(0.5); printf(".");
   	delay(1.0); printf(".");
   	delay(1.0); printf(".\n");
   	printf("%d\n", luckyNum);
   	markInCard(card1, luckyNum);
   	
   	/* check */	
   	flag = checkWinner(pattern, card1);
   	if(flag == true){
   		printf("BINGO\n\n");
   		break;
   	}
   	printf("\n");
  
   	printf("Press ENTER to continue...");
   	getch();
   	system("cls");
   	displayPattern(pattern);
   	printCard(card1);
   	printf("\n");
	}
	getch();	
   return 0;
}

void delay(double seconds){ 
	time_t start;
	time_t current;
	time(&start);
	do{ time(&current); } while(difftime(current,start) < seconds);
}

void initializeArray(int array[], int size){
	int i=0;
	for(i=1;i<=size;i++) array[i] = 0;		
}


int draw(BOOL drawnNumbers[]){
	int num = 0;
	do{
		//srand((unsigned)time(0));
		num = rand() % 75 + 1;
	} while(drawnNumbers[num] == true);
	drawnNumbers[num] = true;
	return num;
}

char getLetter(int num){
	if(num < 16) return 'B';
	else if(num < 31) return 'I';
	else if(num < 46) return 'N';
	else if(num < 61) return 'G';
	else return 'O';	
}

void createCard(tile_t card[6][6], BOOL inCardNumbers[]){
		int num, i, j;
		
		for(i=1; i<6;i++){
			for(j=1; j<6; j++){
			//	if(i == 3 && j ==3) printf("|FREE");
			//	else{
					do{
						srand((unsigned)time(0));
						num = rand() % 15 +(15*(j-1))+1;
					}while(inCardNumbers[num] == true);
					card[i][j].number = num;
					inCardNumbers[num] = true;
				//	printf("| %2d ", card[i][j].number);
			//	}
			//	if(j == 5)
		//			printf("|");
				
			}
//		printf("\n");
		}	
		printCard(card);
}
void markInCard(tile_t card[6][6], int num){
		int i, column;
		column = (num-1)/15 + 1; //this is to determine what column the luckyNumber belongs in
		for(i=1; i<6; i++){
			if(card[i][column].number == num) {
				printf("The number %d is in your card! ",card[i][column].number);
				card[i][column].drawn = true;
				break;
			}
		}
		if(i>5)printf("Number not in your card.");
}

void displayPattern(int pattern){
	
	printf("Today's game pattern is:\n\n");
	switch(pattern){
		case 1:	printf("| B | I | N | G | O |\n" 	/* T-pattern */
                  	 "| x | x | x | x | x |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n\n");
         		break;
         		
   	case 2: 	printf("| B | I | N | G | O |\n"		/* X-pattern */
                  	 "| x |   |   |   | x |\n"
                  	 "|   | x |   | x |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   | x |   | x |   |\n"
                  	 "| x |   |   |   | x |\n\n");
         		break;
         		
   	case 3:	printf("| B | I | N | G | O |\n" 	/* Y-pattern */
                  	 "| x |   |   |   | x |\n"
                  	 "|   | x |   | x |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n\n");
         		break;
         		
   	case 4:	printf("| B | I | N | G | O |\n"		/* N-pattern  */
                  	 "| x |   |   |   | x |\n"
                  	 "| x | x |   |   | x |\n"
                  	 "| x |   | x |   | x |\n"
                  	 "| x |   |   | x | x |\n"
                  	 "| x |   |   |   | x |\n\n");
         		break;
         		
	   case 5:	printf("| B | I | N | G | O |\n"		/* Box-pattern  */
                  	 "| x | x | x | x | x |\n"
                  	 "| x |   |   |   | x |\n"
                  	 "| x |   |   |   | x |\n"
                  	 "| x |   |   |   | x |\n"
                  	 "| x | x | x | x | x |\n\n");
         		break;
   	
   	case 6: 	printf("| B | I | N | G | O |\n"		/* I-pattern */
                  	 "| x | x | x | x | x |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "|   |   | x |   |   |\n"
                  	 "| x | x | x | x | x |\n\n");
         		break;
         		
      case 7: 	printf("| B | I | N | G | O |\n"		/* H-pattern */
                  	 "| x |   |   |   | x |\n"
                  	 "| x |   |   |   | x |\n"
                  	 "| x | x | x | x | x |\n"
                  	 "| x |   |   |   | x |\n"
                  	 "| x |   |   |   | x |\n\n");
         		break;
        
      case 8: 	printf("| B | I | N | G | O |\n"		/* Black-out pattern */
                  	 "| x | x | x | x | x |\n"
                  	 "| x | x | x | x | x |\n"
                  	 "| x | x | x | x | x |\n"
                  	 "| x | x | x | x | x |\n"
                  	 "| x | x | x | x | x |\n\n");
         		break;
	}	
}

BOOL checkWinner(int pattern, tile_t card[6][6]){
	int i=0, j=0, k=0, count=0;
	
	switch(pattern){
		case 1: 	/* T-pattern */
			k=3;
			j=1;
			for(i=1; i<6; i++){
      		if(card[j][i].drawn == true)
      			count++;
      		if(card[i][k].drawn == true)
      			count++;   	
      	}
      	if(count == 10) return true;
      	break;
      
      case 2: /* X-pattern */
       	for(i=1, j=5; i<6; i++, j--){
	    	   if(card[i][i].drawn == true)
	    	   	count++;
	    	   if(card[i][j].drawn == true)
	    	   	count++;	
	    	}
      	
      	if(count == 10) return true;
      	break;
      
      case 3:  /* Y-pattern */
      	for(i=1, j=5; i<3; i++, j--){
	      	if(card[i][i].drawn == true)
	    	   	count++;
	    	   if(card[i][j].drawn == true)
	    	   	count++;
	      }
	      for(i=3, j=4; j<6; j++){
		   	if(card[j][i].drawn == true)
	    	   	count++;
		   }
		   if(count == 6) return true;
		   break;
		
		case 4: /* N-pattern */
			for(i=1; i<6; i++){
				if(card[i][1].drawn == true)
	    	   	count++;
	    	   if(card[i][5].drawn == true)
	    	   	count++;
	    	   if(card[i][i].drawn == true)
	    	   	count++;
			}
			if(count == 15) return true;
			break;
			
		case 5: /* Box-pattern */
			for(i=1; i<6; i++){
				if(card[i][1].drawn == true)
	    	   	count++;
	    	   if(card[1][i].drawn == true)
	    	   	count++;
	    	   if(card[i][5].drawn == true)
	    	   	count++;
	    	   if(card[5][i].drawn == true)
	    	   	count++;
			}
			if(count == 20) return true;
			break;
			
		case 6: /* I-pattern */
			for(i=1; i<6; i++){
	    	   if(card[1][i].drawn == true)
	    	   	count++;
	    	   if(card[5][i].drawn == true)
	    	   	count++;
	    	   if(card[i][3].drawn == true)
	    	   	count++;
			}
			if(count == 15) return true;
			break;
		
		case 7: /* H-pattern */
			for(i=1; i<6; i++){
				if(card[i][1].drawn == true)
	    	   	count++;
	    	   if(card[i][5].drawn == true)
	    	   	count++;
	    		if(card[3][i].drawn == true)
	    	   	count++;
			}
			if(count == 15) return true;
			break;
			
		case 8: /* Black-out pattern */
			for(i=1; i<6; i++){
      		for(j=1; j<6; j++){
      			if(card[i][j].drawn == true)
      				count++;
      		}
      	}
	
			if(count == 25) return true;
			break;	
	}	
	
	return false;
}

void printCard(tile_t card[6][6]){
	int i=0, j=0;
	
	printf("Your card:\n");
	printf("|  B |  I |  N |  G |  O |\n");
	
	for(i=1; i<6; i++){
		for(j=1; j<6; j++){	
   		if(i == 3 && j ==3) printf("|FREE");
   		else{
	   		if(card[i][j].drawn == false)
   				printf("| %2d ", card[i][j].number);
   			else
   				printf("| %2c ", 'x');
   				
   		}
   		if(j == 5)
				printf("|");	
		}
		printf("\n");
	}
	
	
}