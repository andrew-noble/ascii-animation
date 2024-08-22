#include <stdio.h>
#include <unistd.h>
#include <string.h>



//create a simple cube animation where a A x A cube gets drawn, clockwise

//declare an array of ANSI escape codes that move the cursor right, down, left, and up, in sequence
//(this is not ** because we know the length of the strings at compile time!) youd need ** if it was not known like this.
const char* dir[4] = {"\e[C","\e[B","\e[D","\e[A"};

//instantiate variable len
//ask user for desired side length, store it in len

//loop 4 times with iterator i:
    //loop len times:
        //move in dir[i] direction,
        //print #
        //flush stdout
        //sleep 0.10s


int main() {

    int len;
    int i; //iterator outer
    int j; //outer iterator

    printf("How long do you want the sides of the square to be?\n");
    scanf("%d", &len); //to scanf, I pass a format string to indicate we're receiving a digit, and a reference of len, which scanf will load w/ user input

    // Hide cursor
    printf("\e[?25l"); 

    for (i = 0; i < 4; i++) {
        for (j=0; j < len; j++) {
            printf("%s#\b", dir[i]); //prints ansi control code and #, in one command
            fflush(stdout); //this forces printing to the console (stdout is normally buffered)
            usleep(100000);
        }
    }

    usleep(100000);
    printf("\e[%dB\n", len); //move the cursor out of the way, depending on how big the box was
    printf("\e[?25h\n");    // Show cursor


    return 0;
}
