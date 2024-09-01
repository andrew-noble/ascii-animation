#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

const int len = 20; //screen is 30 units wide
float A = 0.0;
float B = 0.0;
const float distToObj = 60;
const float distToScreen =  40; //calculated to keep 16-wide cube about 5/8 occupying screen/ Screen width = 30
const int screenWidth = 100; //this actually produces square screen because ASCII chars are 2:1 aspect ratio
const int screenHeight = 50;

//sets up a list of xyz coordinate pairs for a face
void populate(float arr[len * len][3]) {
    for (int i = 0; i < len * len; i++) { 
        arr[i][0] = fmod(i, len); //produces a cycle through 0,1,2,3,0,1,2... (but in floats via float modulus)

        //took me an eternity to figure this out. Here, we intentionally ignore the remainder through floor division.
        arr[i][1] = floor(i / len);  //prodcuces 0000111122223333 (but in floats)

        arr[i][2] = 0; //start w/ no z component

        // printf("x, y, z: %f, %f, %f for point %d\n", arr[i][0], arr[i][1], arr[i][2], i);
    }

    return;
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h"); //clear entire screen, move cursor home, show cursor

    exit(0);
}

int main() {
    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits on C-c
    printf("\e[?25l"); //hide cursor

    float coords[len * len][3];
    char frame[screenWidth*screenHeight];
    float zBuffer[screenWidth*screenHeight];
    populate(coords); //pre-populate a side that lays in x-y plane to start

    while (1) {

        memset(frame, 32, screenWidth*screenHeight); //inits 2D frame cells all to " "
        memset(zBuffer, 0, screenHeight*screenWidth); //inits ooz to 0 for all frame cells (ooz = 0 corresponds to infinite depth)

        float cosA = cos(A); //precompute trig
        float sinA = sin(A);
        float cosB = cos(B);
        float sinB = sin(B);

        for (int i = 0; i < len * len; i++) {
            float x = coords[i][0];
            float y = coords[i][1];
            float z = coords[i][2];

            //rotate in 3D
            float i = x*cosB + y*cosA*sinB + z*sinA*sinB;
            float j = -x*sinB + y*cosA*cosB + z*sinA*cosB;
            float k = -y*sinA + z*cosA + distToObj; //rotate the points and push Z back
            float ooz = (k !=0) ?  1/k : 0;

            // printf("Rotated at A:%f and B:%f: %f, %f, %f\n\n", A, B, i, j, k);

            //project to 2D
            int xp = (int)((screenWidth/2) + distToScreen*i*ooz); //cast to int because these are the 2D grid values.
            int yp = (int)((screenHeight/2) - distToScreen*j*ooz); //y is negative since higher terminal row numbers = lower down the screen

            int index = xp + screenWidth * yp; //this is row-major ordering, or, a way to encode 2D data in 1D memory

            if (index >= 0 && index <= screenHeight * screenWidth) {
                if (ooz > zBuffer[index]) { //if this pt is closer than what we have in the zBuffer, overwrite it. Means we're encountering a hollow part of the object
                    zBuffer[index] = ooz;
                    frame[index] = '#';
            }}

            // printf("Point #%d (depth %f) will be plotted at %d, %d\n\n", index, ooz, xp, yp);

            
        }

        printf("\e[H"); //move to home

        for (int i = 0; i < screenHeight * screenWidth; i++) {
            putchar(i % screenWidth ? frame[i] : 10); //if this is a new row, print a new row. See row-major ordering step

        }

        usleep(1000000);

        A += 0.3;
        B += 0.1;
    }

    sigint_handler(SIGINT);
    return 0;
}

