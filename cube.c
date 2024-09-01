#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

float A = 0.0;
float B = 0.0;
float C = 0.0;
float cosA;
float cosB;
float cosC;
float sinA;
float sinB;
float sinC;

const int halfLen = 10; //half the width of the cube
const int screenWidth = 100;
const int screenHeight = 40;

const float distToObj = 60;
const float distToScreen = 40; // calculated with: (screenWidth * distToObj)/(1.5 * sqrt(2*len*len))) to keep the viewport 1.5x the width of the max 2D projection

void sigint_handler(int sig);
void precomputeTrig(float A, float B, float C);
void rotate(float *x, float *y, float *z);


int main() {
    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits on C-c
    printf("\e[?25l"); //hide cursor

    char frame[screenWidth*screenHeight];
    float zBuffer[screenWidth*screenHeight];

    sigint_handler(SIGINT);
    return 0;
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h");
    exit(0);
}

void precomputeTrig(float A, float B, float C) { //should speed things up so trig isn't recalculated for each point
    cosA = cos(A);
    cosB = cos(B);
    cosC = cos(C);
    sinA = cos(A);
    sinB = cos(B);
    sinC = cos(C);

    return;
}

void rotate(float *x, float *y, float *z) { //signature says "pass 3 pointers to float in as args"
    float xt = *x; //temps to keep the old vals during math
    float yt = *y;
    float zt = *z;

    *x = xt*(cosB*cosC) + yt*(sinA*sinB*cosC+cosA*sinC + sinA*sinC) - zt*(cosA*sinB*cosC);
    *y = xt*(-cosB*sinC) + yt*(cosA*cosC - sinA*sinB*sinC) + zt*(cosA*sinB*sinC + sinA*cosC);
    *z = xt*(sinB) + yt*(sinA*(-cosB)) + zt*(cosA*cosB);

    return;
}