#include <stdio.h>
#include <unistd.h>
#include <string.h>

//desired functionality:
    //rotates a square (of fixed size, for now), about its, lets say, bottom left hand corner. 15 degrees per frame

//parts:
    //create an array describing all the points in the square. It will be two lists: one of x coords, one of y coords
    //animate function: All it does is loop through the (x,y) pts and print them in the correct spots in the terminal. 
    //rotate function: performs linear transformation math to move every point by 15 deg. See: https://en.wikipedia.org/wiki/Rotation_matrix
    //in main, in while loop:
        //call animation function
        //call rotate function, passing it a ref to the array
        //sleep

int animate() {}
int rotate() {}
int main() {}