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

const float halfLen = 20; //half the width of the cube
const int screenWidth = 100, screenHeight = 40;
const float increment = 0.5; //how densely we're plotting 3D points

const float distToObj = 100;
const float distToScreen = 40; // calculated with: (screenWidth * distToObj)/(1.5 * sqrt(2*len*len))) to keep the viewport 1.5x the width of the max 2D projection

float zBuffer[100*40];
char buffer[100*40];

void sigint_handler(int sig);
void calculatePoint(float x, float y, float z, char ch);


int main() {
    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits on C-c
    printf("\e[?25l"); //hide cursor

    while (1) {
        memset(buffer, ' ', screenHeight*screenWidth); //clear the frame and z buffers
        memset(zBuffer, 0, screenHeight*screenWidth * sizeof(float)); //need to account for 4-byte length of floats

        cosA = cos(A), cosB = cos(B), cosC = cos(C); //precompute trig
        sinA = sin(A), sinB = sin(B), sinC = sin(C);

        for (float i = -halfLen; i < halfLen; i += increment) { //loop a face, any face
            for (float j = -halfLen; j < halfLen; j += increment) {
                calculatePoint(-i, j, -halfLen, '#'); //back
                calculatePoint(i, j, halfLen, '#'); //front
                calculatePoint(-i, -halfLen, j, '&'); //bottom
                calculatePoint(i, halfLen, j, '&'); //top
                calculatePoint(-halfLen, -i, j, ','); //left
                calculatePoint(halfLen, i, j, ','); //right
            }
        }

        printf("\e[H"); // move cursor to home position, this mitigates screen flicker by making the terminal overwrite last frame instead of scrolling last frame out of view
        for (int idx = 0; idx < screenHeight*screenWidth; idx++) {
            putchar(idx % screenWidth ? buffer[idx] : '\n'); //this un-encodes 1D data to 2D pixels. If index is multiple of screenwidth, means we need a newline
        }

        usleep(50000);

        A += 0.07;
        B += 0.05;
        C += 0.03;
    }

    sigint_handler(SIGINT);
    return 0;
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h");
    exit(0);
}

void calculatePoint(float x, float y, float z, char ch) { 
    float xt = x; //temps to keep the old vals during math
    float yt = y;
    float zt = z;

    //---------3D rotation math----------
    x = xt*(cosB*cosC) + yt*(sinA*sinB*cosC + cosA*sinC) + zt*(sinA*sinC - cosA*sinB*cosC); 
    y = xt*(-cosB*sinC) + yt*(cosA*cosC - sinA*sinB*sinC) + zt*(cosA*sinB*sinC + sinA*cosC);
    z = xt*(sinB) - yt*(sinA*cosB) + zt*(cosA*cosB);


    //----------2D projection math---------------------
    z = z + distToObj; //first push the z component back so the object is in front of camera
    float ooz = 1 / (z); //calculate 1/z for projection below

    int xp = (int)((screenWidth/2) + distToScreen*x*ooz*2); //cast to int because these are the 2D grid values. x needs to be doubled due to aspect ratio
    int yp = (int)((screenHeight/2) + distToScreen*y*ooz); //y is negative since higher terminal row numbers = lower down the screen

    //----------rendering logic----------------------
    int idx = xp + screenWidth * yp; //this is "row-major ordering", or, a way to encode 2D data in 1D memory per known row-length
    if (idx >= 0 && idx < screenHeight * screenWidth) { //stops segfaults... this shouldn't be necessary
        if (ooz > zBuffer[idx]) { //"z-sorting" : ensures we only render the frontmost of many potentially-overlaid points
            zBuffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }

    return;
}