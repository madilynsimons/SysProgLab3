/*

    Safe integer calculator - warns if an overflow or
    underflow error occurs.

    Menu
    Negation
    Safe unsigned ops
    Safe signed ops
    Arithmetic without + - * / % ++ or --

    Code the functions below and uncomment the code in main()
    when completed.

    Code the functions in order as they appear.  Subsequent
    functions depend on previous functions.  You cannot use
    any math operators (+ - * / % ++ or --) except simple
    assignment (=).  However, you may use relational and
    logical operators.

    The _add() function should only use bitwise operators.  All
    other functions can call functions necessary to complete the
    required operation.  I added some hints above functions.

*/

#include <stdio.h>

// Prototypes
int _add(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int neg(int a);
int mul(int a, int b);
int div(int a, int b);
int mod(int a, int b);
int pow(int a, int b);
int convert(char *input);

int debugging = 0;


// Main
int main(int argc, char *argv[]){

    int res = 0;        // Cumulative result - running total
    int n = 0;          // For number conversion from input string
    char input[50];     // Input string
    input[0] = '\0';    // Put null in operator char so loop works

    // Write code here to test your functions
    // Uncomment code below when done

    // Loop until quit is selected
    while(input[0] != 'q' && input[0] != 'Q'){
        // Show menu choices
        menu();
        // Print prompt with running total
        printf("\nres = %d > ", res);
        // Get input string
        gets(input);
        // Clear screen
        system("clear");

        // Switch on operator char input[0]
        switch (input[0]){
            case '+':
                res = add(res, convert(input));
                break;
            case '-':
                res = sub(res, convert(input));
                break;
            case '*':
                res = mul(res, convert(input));
                break;
            case '/':
                res = div(res, convert(input));
                break;
            case '%':
                res = mod(res, convert(input));
                break;
            case '~':
                res = neg(res);
                break;
            case '^':
                res = pow(res, convert(input));
                break;
            case 'c':
            case 'C':
                res = 0;
                break;
            case 'q':
            case 'Q':
                printf("Good-bye!\n");
                break;
            default:
                printf("Enter a valid operator and operand\n");

        }

    }


    return 0;
}


// Show menu choices
void menu(){
    printf("\nSafe Integer Calculator\n");
    printf("+ x to add\n");
    printf("- x to subtract\n");
    printf("* x to multiply\n");
    printf("/ x to divide\n");
    printf("%% x to modulus\n");
    printf("~ x to negate\n");
    printf("^ x to raise by power x\n");
    printf("c x to clear result\n");
    printf("q x to quit\n");
    return;
}


/*
    This function should only use bitwise operators and
    relational operators
*/
// Add operation using only bitwise operators
int _add(int a, int b){
    if(debugging) printf("_add( %d, %d ) = ", a, b);
    // Loop until b is zero
    while(b != 0)
    {
        // Find carry 1 bits - a AND b assign to carry
        unsigned int carry = a & b;

        // Find non carry 1 bits - a XOR b assign to a
        a = a ^ b;

        // Multiply carry by 2 by shift and assign to b  
        b = (carry <<= 1); 
    }

    if(debugging) printf("%d\n", a);
    return a;
}


/*
    Safe add() should call _add() and check for both
    overflow and underflow errors.
*/
// Safe add operation
int add(int a, int b){
    if(debugging) printf("add( %d, %d ) = ", a, b);
    // Declare int for result
    int res = 0;
    // Call to _add() a and b and assign to result
    res = _add(a, b);

    if( ((res ^ a) & (res ^ b)) < 0)
    {
    	if(res > 0) printf("UNDERFLOW ERROR -- Exiting...\n");
    	if(res < 0) printf("OVERFLOW ERROR -- Exiting...\n");
    	exit(3);
    }

    if(debugging) printf("%d\n", res);
    return res;
}


/*
    Negate a by using a bitwise operator and safe add().
    Look on page 95 in book.
    Replace the zero with an expression that solves this.
*/
// Define negation with ~ and safe add
int neg(int a){
    if(debugging) printf("neg( %d ) = ", a);
    // Return negation of a and add 1
    int res = 0;
    res = add(~a, 1);

    if(debugging) printf("%d\n", res);
    return res;   // Replace 0 with code
}


/*
    Remember that subtraction is the same as addition
    if you negate one of the operands.
    Replace the zero with an expression that solves this.
*/
// Define safe subtract by safe add - negate b
int sub(int a, int b){
    if(debugging) printf("sub( %d, %d ) = ", a, b);

    int res = 0;
    res = add(a, neg(b));

    if(debugging) printf("%d\n", res);
    return res;  // Replace 0 with code
}


/*
    Safe mul() uses an iterative call to safe add()
    to calculate a product. Remember that
        5 x 4 = 5 + 5 + 5 + 5 = 20
*/
// Define safe multiply by calling safe add b times
int mul(int a, int b){
    if(debugging) printf("mult( %d, %d ) = ", a, b);

    if(a == 0 || b == 0) return 0;

    // Declare and initialize cumulative result
    int res = 0;
    // Declare sign of product - initially assume positive
    unsigned int sign = 0;
    if( a < 0 && b < 0 || a > 0 && b > 0) sign = 0;
    else sign = 1;

    if(neg(a) > 0) a = neg(a);
    if(neg(b) > 0) b = neg(b);

    int mult;
    int term;
    if(a < b)
    {
        mult = a;
        term = b;
    }
    else
    {
        mult = b;
        term = a;
    }

    int x;
    for(x = 0; x < mult; x++)
    {
        res = add(res, term);
    }

    // Set sign to output
    if(sign) res = neg(res);

    if(debugging) printf("%d\n", res);
    return res;
}


/*
    Safe div() repeatedly subtracts b from a, counting the
    number of subtractions until a < b, which it returns.
*/
// Define safe divide by calling safe subtract b times
int div(int a, int b){
    if(debugging) printf("div( %d, %d ) = ", a, b);

    if(a == 0) return 0;
    if(b == 0)
    { 
        printf("DIVIDE BY 0 ERROR -- Exiting...\n");
        exit(4);
    }

    // Declare int to count how many times can b be subtracted from a
    int cnt = 0;
    // Declare sign
    unsigned int sign = 0;
    if( a < 0 && b < 0 || a > 0 && b > 0) sign = 0;
    else sign = 1;

    if(neg(a) > 0) a = neg(a);
    if(neg(b) > 0) b = neg(b);

    // loop to calculate how many times can b be subtracted from a
    while(a >= b)
    {
        a = sub(a, b);
        cnt++;
    }

    // Set sign to output
    if(sign) cnt = neg(cnt);

    if(debugging) printf("%d\n", cnt);
    return cnt;
}


/*
    Safe mod() repeatedly subtracts b from a until a < b, returning a.
*/
// Define safe modulus by calling safe subtract
int mod(int a, int b){
    if(debugging) printf("mod( %d, %d ) = ", a, b);

    if(b == 0)
    {
    	printf("DIVIDE BY ZERO ERROR -- Exiting...\n");
    	exit(4);
    }

    int sign = 0;
    if(b < 0 || a < 0) sign = 1;

    // Absolute value of a
    if(neg(a) > 0 ) a = neg(a);

    // Absolute value of b
    if(neg(b) > 0 ) b = neg(b);

    // Find remainder by repeated subtraction a - b
    while(a > b)
    {
        a = sub(a, b);
    }

    if(sign) a = neg(a);

    if(debugging) printf("%d\n", a);
    return a;
}


/*
    Safe pow() calculates as the math pow function but
    only uses the safe operations.
        res = n^exp
    Loop until exp is zero
        res = res * n
        exp = exp - 1
    Remember the special case for n^0

*/
// Define safe pow by calling safe multiply exp times
int pow(int n, int exp){
    if(debugging) printf("pow( %d, %d ) = ", n, exp);
    if(exp == 0) return 1;
    // Declare int for result of n^exp
    int res = 0;
    // Loop and multiply to calculate n^exp
    for(res = 1; exp > 0; exp--)
    {
        res = mul(res, n);
    }

    if(debugging) printf("%d\n", res);
    return res;
}


/*
    This function extracts the integer value from the input string.
        If input = "+ -123", res = -123.
        If input = "* 987654", res = 987654.
    The best way to solve complicated problems is to work them out
    on paper first.
*/
// Extract the integer from the input string and convert to int
int convert(char *input){
    // Declare int for result extracted from input
    int res = 0;
    // Declare int for sign of result
    int sign = 0;

    // Declare two iterators
    int i = 0;
    int j = 1;

    // Declare a buffer for numeric chars
    char buffer[100];

    // Set error to zero - no error found yet
    int error = 0;

    // Check for space in element 1
    if(input[j] == ' ') j = add(j, 1);

    // Check for negative integer at element 2
    if(input[j] == '-')
    {
        sign = 1;
        j = add(j, 1);
    } 

    // Loop to copy all numeric chars to buffer
    // i is iterator for input string and should start at first numeric char
    // j is iterator for buffer where numeric chars are copied
    // This must test for chars between 0 and 9

    for(i = 0; input[j] != '\0' && error == 0;)
    {
        if(input[j] >= '0' && input[j] <= '9')
        {
            buffer[i] = input[j];
        }
        else error = 1;
        i = add(i, 1);
        j = add(j, 1);
    }

    // i gets position of last numeric char in buffer
    buffer[i] = '\0';

    // j is now used for pow function - start at zero

    j = 0;
    for(i = sub(i, 1); i >= 0; i = sub(i, 1))
    {
        int mult = 1;

        mult = pow(10, i);

        buffer[j] = sub(buffer[j], 48);
        mult = mul(mult, buffer[j]);
        res = add(res, mult);

        j = add(j, 1);
    }

    // Set sign for output
    if(sign) res = neg(res);

    return res;
}

