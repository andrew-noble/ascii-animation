#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define dims 2
#define len 4

//desired functionality:
    //rotates a square (of fixed size, for now), about its, lets say, bottom left hand corner. 15 degrees per frame

//parts:
    //create an array describing all the points in the square. It will be a list of 2-element lists (x and y coords)
    //animate function: All it does is loop through the (x,y) pts and print them in the correct spots in the terminal. 
    //rotate function: performs linear transformation math to move every point by 15 deg. See: https://en.wikipedia.org/wiki/Rotation_matrix
    //in main, in while loop:
        //call animation function
        //call rotate function, passing it a ref to the array
        //sleep

int coords[len*4][2]; //instantiate the coordinate vector. rows = points, cols = x and y dims

int init(int arr[len*4][2]) {
    for (int pt = 0; pt < len * 4; pt++) { //loop 16 times to create 16 different x-y pairs
        arr[pt][0] = pt % 4; //produces a cycle through 0,1,2,3,0,1,2...

        //took me an eternity to figure this out. Here, we intentionally ignore the remainder through integer division. Effectively doing a "floor division".
        arr[pt][1] = (pt / 4);  //prodcuces 0000111122223333
        
        // printf("x, y for pt %d: %d, %d\n", pt, arr[pt][0], arr[pt][1]);
    }
    return 0;
}

int animate() {}
int rotate() {}
int main() {
    init(coords);

    return 0;
}