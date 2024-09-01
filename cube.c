#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

//rotate a single square in 3D space

const int len = 20; //screen is 30 units wide
float A = 0.0;
float B = 0.0;

const int screenWidth = 100;
const int screenHeight = 40;

const float distToObj = 60;
const float distToScreen = 40; // calculated with: (screenWidth * distToObj)/(1.5 * sqrt(2*len*len))) to keep the viewport 1.5x the width of the max 2D projection

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h"); //clear entire screen, move cursor home, show cursor

    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits on C-c
    printf("\e[?25l"); //hide cursor

    char frame[screenWidth*screenHeight];
    float zBuffer[screenWidth*screenHeight];

    sigint_handler(SIGINT);
    return 0;
}