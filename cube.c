#include <stdio.h>
#include <unistd.h>
#include <string.h>

//notes for now:
//relevant ANSI escape codes:
    // \e[H   : move cursor to home
    // \e[2J  : clear entire screen
    // \e[{line};{column}H  : move to a certain line and column coordinate
