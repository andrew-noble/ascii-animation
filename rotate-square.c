#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#define LEN 16 //side LENgth of square
#define ORIGIN_L 30
#define ORIGIN_C 40

#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif

#define theta_increment (M_PI / 45.0) // 1 degree in radians

//desired functionality:
    //rotates a 2D square (of fixed size, for now), about its, lets say, bottom left hand corner. 15 ccw degrees per frame

//parts:
    //create an array describing all the points in the square. It will be a list of 2-element lists (x and y coords)
    //animate function: All it does is loop through the (x,y) pts and print them in the correct spots in the terminal. 
    //rotate function: performs linear transformation math to move every point by 15 deg. See: https://en.wikipedia.org/wiki/Rotation_matrix
    //in main, in while loop:
        //call animation function
        //call rotate function, passing it a ref to the array
        //sleep

void populate(float arr[LEN * LEN][2]);
void render(float arr[LEN * LEN][2]);
void rotate(float arr[LEN * LEN][2], float th);
void sigint_handler(int sig);


int main() {
    float coords[LEN * LEN][2];
    float theta = 0.0;

    signal(SIGINT, sigint_handler); //set up sigint handler for cleaner program quits

    printf("\e[?25l"); //hide cursor
    populate(coords);

    while (1) {
        rotate(coords, theta);
        render(coords);
        usleep(100000);
        theta += theta_increment;
        if (theta >= 2 * M_PI) theta -= 2 * M_PI; // Reset theta after a full rotation

    }

    printf("\e[?25h\n"); //show cursor

    return 0;
}

//sets up a list of x-y coordinate pairs
void populate(float arr[LEN * LEN][2]) {
    for (int i = 0; i < LEN * LEN; i++) { //loop 16 times to create 16 different x-y pairs
        arr[i][0] = fmod(i, LEN); //produces a cycle through 0,1,2,3,0,1,2... (but in floats via float modulus)

        //took me an eternity to figure this out. Here, we intentionally ignore the remainder through floor division.
        arr[i][1] = floor(i / LEN);  //prodcuces 0000111122223333 (but in floats)

        // printf("x, y for i %d: %d, %d\n", i, arr[i][0], arr[i][1]);
    }

    return;
}

void render(float arr[LEN*LEN][2]) { //this is where virtual float coords get converted into integers for terminal coordinates.
    printf("\e[2J"); //clear entire screen
    printf("\e[%d;%dH", ORIGIN_L, ORIGIN_C); //move cursor to center-ish origin


    for (int i = 0; i < LEN * LEN; i++) { //loop through points
        int x = (int)roundf(arr[i][0]) + ORIGIN_C; //cast the float coords to integers for rendering
        int y = (int)roundf(arr[i][1]) + ORIGIN_L;

        printf("\e[0m\e[%d;%dH", y, x * 2); //move cursor to line:column and print, and we pass in the current coordinate from coords, relative to origin
        printf("# ");
        fflush(stdout);
    }
    return;
}

void rotate(float arr[LEN*LEN][2], float th) {
    for (int i = 0; i < LEN*LEN; i++) {
        float x = arr[i][0]; //precalculate before using to do math
        float y = arr[i][1];

        arr[i][0] = x*cosf(th) - y*sinf(th); 
        arr[i][1] = x*sinf(th) + y*cosf(th);

        // printf("x, y for pt %d: %d, %d\n", i, arr[i][0], arr[i][1]);

    }
    return;
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (Ctrl+C)");
    printf("\e[2J\e[H\e[?25h"); //clear entire screen, move cursor home, show cursor

    exit(0);
}