#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define LEN 16 //side LENgth of square
#define ORIGIN_L 30
#define ORIGIN_C 40

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

void populate(int arr[LEN * LEN][2]);
void paint(int arr[LEN * LEN][2]);
void rotate(int arr[LEN * LEN][2], double th);


int main() {
    int coords[LEN * LEN][2];
    double theta = 0.0;

    // printf("\e[?25l"); //hide cursor
    populate(coords);

    while (1) {
        rotate(coords, theta);
        paint(coords);
        usleep(1000000);
        theta += 0.087; //increment theta about 5deg
    }

    // printf("\e[?25h\n"); //show cursor

    return 0;
}

void populate(int arr[LEN * LEN][2]) {
    for (int i = 0; i < LEN * LEN; i++) { //loop 16 times to create 16 different x-y pairs
        arr[i][0] = i % LEN; //produces a cycle through 0,1,2,3,0,1,2...

        //took me an eternity to figure this out. Here, we intentionally ignore the remainder through integer division. Effectively doing a "floor division".
        arr[i][1] = (i / LEN);  //prodcuces 0000111122223333

        // printf("x, y for i %d: %d, %d\n", i, arr[i][0], arr[i][1]);
    }

    return;
}

void paint(int arr[LEN*LEN][2]) {
    printf("\e[2J"); //clear entire screen
    printf("\e[%d;%dH", ORIGIN_L, ORIGIN_C); //move to center-ish origin

    for (int i = 0; i < LEN * LEN; i++) { //loop through points
        printf("\e[%d;%dH", arr[i][1] + ORIGIN_L, (arr[i][0] + ORIGIN_C) * 2); //move cursor to line:column and print, and we pass in the current coordinate from coords, relative to origin
        printf("# ");
        fflush(stdout);

    }

    return;
}

void rotate(int arr[LEN*LEN][2], double th) {
    for (int i = 0; i < LEN*LEN; i++) {
        int x = arr[i][0]; //store before modifying
        int y = arr[i][1];

        arr[i][0] = x*cos(th) - y*sin(th);
        arr[i][1] = x*sin(th) - y*cos(th);

        // printf("x, y for pt %d: %d, %d\n", i, arr[i][0], arr[i][1]);

    }
    return;
}