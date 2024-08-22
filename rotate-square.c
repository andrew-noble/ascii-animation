#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LEN 16 //side LENgth of square
#define ORIGIN_L 12
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


int main() {
    int coords[LEN * LEN][2];

    printf("\e[?25l"); //hide cursor

    populate(coords);
    paint(coords);

    printf("\e[?25h\n"); //show cursor

    return 0;
}

void populate(int arr[LEN * LEN][2]) {
    for (int pt = 0; pt < LEN * LEN; pt++) { //loop 16 times to create 16 different x-y pairs
        arr[pt][0] = pt % LEN; //produces a cycle through 0,1,2,3,0,1,2...

        //took me an eternity to figure this out. Here, we intentionally ignore the remainder through integer division. Effectively doing a "floor division".
        arr[pt][1] = (pt / LEN);  //prodcuces 0000111122223333

        // printf("x, y for pt %d: %d, %d\n", pt, arr[pt][0], arr[pt][1]);
    }

    return;
}

void paint(int arr[LEN*4][2]) {
    printf("\e[2J"); //clear entire screen

    //TODO: command to move the cursor to desired origin
    printf("\e[%d;%dH", ORIGIN_L, ORIGIN_C);

    for (int i = 0; i < LEN * LEN; i++) { //loop through points
        printf("\e[%d;%dH", arr[i][1] + ORIGIN_L, arr[i][0] + ORIGIN_C); //move cursor to line:column and print, and we pass in the current coordinate from coords, relative to origin
        putchar('.');
        fflush(stdout);
    }

    return;
}

int rotate() {}