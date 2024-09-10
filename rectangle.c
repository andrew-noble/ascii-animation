#include <stdio.h>
#include <unistd.h>
#include <string.h>

//asuming a raster-like behavior for printing, 

//ask user for length, width (maybe also incorporate into the cmd line args)


//loop len times:
    //loop len times:
        //print #
        //flush
        //sleep
    //move cursor down and back len times, to start next raster


int main() {

    int width;
    int height;
    int i; //iterator outer
    int j; //outer iterator

    printf("How wide?\n");
    scanf("%d", &width); 

    printf("How tall?\n");
    scanf("%d", &height); 

    // Hide cursor
    printf("\e[?25l"); 

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            putchar('#'); //just prints character (but also moves cursor ahead)
            fflush(stdout); //this forces printing to the console (stdout is buffered)
            usleep(100000);
        }
        printf("\n");
    }

    usleep(100000);
    printf("\e[%dE", height); //move the cursor out of the way, depending on how big the box was
    printf("\e[?25h\n");    // Show cursor


    return 0;
}