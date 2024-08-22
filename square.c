#include <stdio.h>
#include <unistd.h>
#include <string.h>

//asuming a raster-like behavior for printing, 
//loop len times:
    //loop len times:
        //print #
        //flush
        //sleep
    //move cursor down and back len times, to start next raster


int main() {

    int len;
    int i; //iterator outer
    int j; //outer iterator

    printf("How long do you want the sides of the square to be?\n");
    scanf("%d", &len); //to scanf, I pass a format string to indicate we're receiving a digit, and a reference of len, which scanf will use to load w/ user input

    // Hide cursor
    printf("\e[?25l"); 

    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            putchar('#'); //just prints character (but also moves cursor ahead)
            fflush(stdout); //this forces printing to the console (stdout is buffered)
            // usleep(100000);
        }
        printf("\n\e[%dE", len);
    }

    usleep(100000);
    printf("\e[%dB\n", len); //move the cursor out of the way, depending on how big the box was
    printf("\e[?25h\n");    // Show cursor


    return 0;
}