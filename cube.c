#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>


//notes for now:
//relevant ANSI escape codes:
    // \e[H   : move cursor to home
    // \e[2J  : clear entire screen
    // \e[{line};{column}H  : move to a certain line and column coordinate

 //business logic functions:

//geometry logic

    //1: locate_points
        //in: angle A, angle B
        //out: array of rotated xyz points

//rending logic

    //2: locate_surface
        //in: rotated xyz point
        //out: unit vector describing surface normal
    //3: project
        //in: rotated xyz point
        //out: projected xy point
    //4: illuminate
        //in: rotated xyz point and its surface normal
        //out: ascii character
    //5: render
        //in: projected xy point, ascii char

void sigint_handler(int sig);


int main() {

    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits

    printf("\e[?25l"); //hide cursor

    sigint_handler(SIGINT);

    return 0;
}


void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h"); //clear entire screen, move cursor home, show cursor

    exit(0);
}