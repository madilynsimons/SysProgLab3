/**
 *  Lab 3
 *  @Author:  Madilyn Simons
 */

/*

    Number converter

    Menu
    Convert between integer, binary, octal and hexadecimal

    This program should accept numeric values in hexadecimal,
    decimal, octal and binary formats as:

        Hex 0x0 to 0xFFFFFFFF
        Dec 0 to 4294967295
        Oct o0 to o37777777777
        Bin b0 to b11111111111111111111111111111111

    After a value is input the code in main will interpret the
    data types above an process the conversion to an unsigned
    int.  The unsigned int will be used to convert the input to
    strings containing hexadecimal, octal and binary strings.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//int input_to_decimal(char *input);
unsigned int bin_to_uint(char *input);
unsigned int oct_to_uint(char *input);
unsigned int hex_to_uint(char *input);
unsigned int dec_to_uint(char *input);
void uint_to_hex(unsigned int n, char *output);
void uint_to_oct(unsigned int n, char *output);
void uint_to_bin(unsigned int n, char *output);


int error = 0;


int main(){

    char input[50];
    unsigned int n = 0;
    char output[50];

    // Write code here to test your functions
    // Uncomment code below when done

    printf("Enter a binary, octal, decimal or hexadecimal number\n");
    printf("convert > ");
    gets(input);

    // Detect input data type
    // Hexadecimal
    if(input[0] == '0' && input[1] == 'x'){
        n = hex_to_uint(input);
    }
    // Decimal
    else if(input[0] >= '0' && input[0] <= '9'){
        n = dec_to_uint(input);
    }
    // Octal
    else if(input[0] == 'o'){
        n = oct_to_uint(input);
    }
    // Binary
    else if(input[0] == 'b'){
        n = bin_to_uint(input);
    }
    // Unknown
    else{
        printf("ERROR: Unknown data type: %s\n", input);
    }

    // Print results
    printf("The decimal value of %s is %u\n", input, n);
    uint_to_hex(n, output);
    printf("The hexadecimal value of %s is %s\n", input, output);
    uint_to_oct(n, output);
    printf("The octal value of %s is %s\n", input, output);
    uint_to_bin(n, output);
    printf("The binary value of %s is %s\n", input, output);

    return 0;
}


/*
    This function converts the value part of the hex
    string to an unsigned integer value.  The first
    two chars are 0x, which tells that the string is
    in hex.  Start processing the value at index 2 until
    the null, calculating the int value as you would on
    paper.  Try on paper first.
*/
// Convert a hexadecimal char array to uint
unsigned int hex_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;

    // Declare and set multiplier to 1
    unsigned int multiplier = 16;

    // Declare iterator
    int j;

    // Loop through value part of input string

    for(j = 2; input[j] != '\0'; j++)
    {
    	// If between 0 and 9 add 0 to 9 to res with multiplier
    	if(input[j] >= '0' && input[j] <= '9')
    	{
    		res = res*multiplier + input[j] - 48;
    	}
    	// If between A and F add 10 to 15 to res with multiplier
    	else if(input[j] >= 'A' && input[j] <= 'F')
    	{
    		res = res*multiplier + input[j] - 55;
    	}
    	// Error - exit
    	else
    	{
    		printf("INPUT ERROR -- exiting...\n");
    		exit(2);
    	}
    }

    return res;
}

/*
    Copy hex_to_uint() and modify for decimal input.
*/
// Convert a unsigned integer char array to uint
unsigned int dec_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;

    unsigned int multiplier = 10;

    int j;

    for(j = 0; input[j] != '\0'; j++)
    {
    	// If between 0 and 9 add 0 to 9 to res with multiplier
    	if(input[j] >= '0' && input[j] <= '9')
    	{
    		res = res*multiplier + input[j] - 48;
    	}
    	// Error - exit
    	else
    	{
    		printf("INPUT ERROR -- exiting...\n");
    		exit(2);
    	}
    }

    return res;
}


/*
    Copy dec_to_uint() and modify for octal input.
*/
// Convert a octal char array to uint
unsigned int oct_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;

    unsigned int multiplier = 8;

    int j;

    for(j = 1; input[j] != '\0'; j++)
    {
    	// If between 0 and 9 add 0 to 9 to res with multiplier
    	if(input[j] >= '0' && input[j] <= '7')
    	{
    		res = res*multiplier + input[j] - 48;
    	}
    	// Error - exit
    	else
    	{
    		printf("INPUT ERROR -- exiting...\n");
    		exit(2);
    	}
    }

    return res;
}


/*
    Copy oct_to_uint() and modify for binary input.
*/
// Convert a binary char array to unsigned int
unsigned int bin_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;

    unsigned int multiplier = 2;

    int j;

    for(j = 1; input[j] != '\0'; j++)
    {
    	// If between 0 and 9 add 0 to 9 to res with multiplier
    	if(input[j] >= '0' && input[j] <= '1')
    	{
    		res = res*multiplier + input[j] - 48;
    	}
    	// Error - exit
    	else
    	{
    		printf("INPUT ERROR -- exiting...\n");
    		exit(2);
    	}
    }

    return res;
}


/*
    This function converts from unsigned int to a hex
    char array.  Try this on paper before coding.
*/
// Convert a unsigned integer char array to hexadecimal
void uint_to_hex(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int remainder;

    // Declare an int for division
    int divider = 16;

    // Declare a char array buffer
    char buffer[100];

    // Use a loop to generate a hex string - string will be reverse
    int j;
    for(j = 0; n > 0; j++)
    {
		remainder = n % divider;

		if(remainder < 10)
		{
			buffer[j] = (char) (remainder + 48);
		}
		else
		{
			buffer[j] = (char) (remainder + 55);
		}

		n /= divider;
	}
    // Get last hex char
    // Put null at end of buffer
    buffer[j] = '\0';

    // Copy 0x to output string
    strcpy(output, "0x");

    // Copy chars from buffer in reverse order to output string
    int left = 0;
    int right = j-1;
    while(left < right)
    {
    	char temp = buffer[left];
    	buffer[left] = buffer[right];
    	buffer[right] = temp;
    	left++;
    	right--;
    }

    strcat(output, buffer);

    return;
}


/*
    Copy uint_to_hex() and modify for octal
*/
// Convert a unsigned integer char array to octal
void uint_to_oct(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int remainder;

    // Declare an int for division
    int divider = 8;

    // Declare a char array buffer
    char buffer[100];

    // Use a loop to generate a hex string - string will be reverse
    int j;
    for(j = 0; n > 0; j++)
    {
		remainder = n % divider;

		buffer[j] = (char) (remainder + 48);

		n /= divider;
	}
    // Get last hex char
    // Put null at end of buffer
    buffer[j] = '\0';

    // Copy 0x to output string
    strcpy(output, "o");

    // Copy chars from buffer in reverse order to output string
    int left = 0;
    int right = j-1;
    while(left < right)
    {
    	char temp = buffer[left];
    	buffer[left] = buffer[right];
    	buffer[right] = temp;
    	left++;
    	right--;
    }

    strcat(output, buffer);
    
    return;
}


/*
    Copy uint_to_oct() and modify for binary
*/
// Convert a unsigned integer char array to binary
void uint_to_bin(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int remainder;

    // Declare an int for division
    int divider = 2;

    // Declare a char array buffer
    char buffer[100];

    // Use a loop to generate a hex string - string will be reverse
    int j;
    for(j = 0; n > 0; j++)
    {
		remainder = n % divider;

		buffer[j] = (char) (remainder + 48);

		n /= divider;
	}
    // Get last hex char
    // Put null at end of buffer
    buffer[j] = '\0';

    // Copy 0x to output string
    strcpy(output, "b");

    // Copy chars from buffer in reverse order to output string
    int left = 0;
    int right = j-1;
    while(left < right)
    {
    	char temp = buffer[left];
    	buffer[left] = buffer[right];
    	buffer[right] = temp;
    	left++;
    	right--;
    }

    strcat(output, buffer);
    
    return;
}

