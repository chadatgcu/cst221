/*
* Chad Weirick
* CST - 221
* GCU
* 
* requests directly from the guide:
*
* Write a C program that takes a decimal number between 0 and 1000 as input from a user that performs the following operations on the input:
* a.	Display the number as a 32-bit binary number displaying each binary digit as a 1 or 0 (with the least significant bit on right) on the console. 
* b.	Display the number as a 32-bit hexidecimal number on the console. 
* c.	Transform the input by shifting the number 16 bits to the left, then mask out (AND) the bottom 16 bits, and finalNumberly add (OR) the hex number 0x07FF to produce the finalNumber resultant number. Display the finalNumber result in binary, hexausersDecimal, and usersDecimal to the console.
* d.	Write your program in a modular fashion to eliminate redundant code.
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char easyToChangeArray [32];



int counter;
int counter2;
int finalNumber;
int x;



unsigned int usersDecimal; 
unsigned int shiftedNumber; // for Step C


void* getBinary (){

	if (usersDecimal >= 0){ 
		unsigned int mask = 1<<31;

		for (counter = 0; counter < 8; counter++){
			for (counter2 = 0; counter2 < 4; counter2++){
				char c = (usersDecimal & mask) == 0 ? '0' : '1';
				easyToChangeArray[x++] = c;
				putchar(c);
				mask >>= 1;
			}
			putchar(' ');
		}
		putchar('\n');
	} 
}

void* readFromConsole (){
	scanf("%d", &usersDecimal); // ask user for a usersDecimal
	while ((getchar()) != '\n');
}

// here are the printing commands
void* consoleMessage (char sendThis []){
	printf("%s\n", sendThis);
}

void* showHex (){
	printf("%04x\n", usersDecimal);
}

void* makeUsersDecimal (){
	consoleMessage("Binary form : ");
	getBinary();
	consoleMessage("hex Form: ");
	showHex();
}

void* shiftedNumber_number (){
	// Step C part 1 & 2 here
	shiftedNumber = usersDecimal << 16;
	finalNumber = shiftedNumber & usersDecimal;
	unsigned int addition = 0x07FF; // shifting
	usersDecimal = addition + usersDecimal;
	printf("Decimal code is now: %d\n", finalNumber);
	
	
	makeUsersDecimal(); //Change usersDecimal and print new numbers
}


int main (void){
	usersDecimal = -1, shiftedNumber;
	// prevent user from entering invalid data range
	while (usersDecimal < 0 || usersDecimal > 1000){
		//Opening user prompt
		consoleMessage("Enter a positive number under 1000 and press enter/return. ");
		readFromConsole();
		if (usersDecimal < 0 || usersDecimal > 1000){
			consoleMessage("Please enter a positive number under 1000.\n");
		}
	}
	// Execute step a
	makeUsersDecimal();
	// Execute step b
	shiftedNumber_number();
	return 0;
}