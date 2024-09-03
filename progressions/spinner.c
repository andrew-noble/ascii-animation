#include <stdio.h>
#include <unistd.h>
#include <string.h>

//array of characters
const char frames[8] = {'-', '/', '|', '\\', '-', '/', '|', '\\'};


int main() {
    int i;

    // Hide cursor
    printf("\e[?25l"); 

    for (i = 0; i < 16; i++) {
        printf("\r%c", frames[i % 8]); //the %c is necessary to specify that we're printing a character, \r is the carriage return. Modulo makes it double back over the frames
        fflush(stdout); //this forces printing to the console (stdout is normally buffered)
        usleep(250000);
    }

    // Show cursor
    printf("\e[?25h\n");

    return 0;
}

