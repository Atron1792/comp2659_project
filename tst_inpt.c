/*
File Name: tst_inpt.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Tests nonblocking keyboard detection and character retrieval.
*/

#include <stdio.h>

#include "input.h"

#define ESC_KEY 27

/*----- Function: main -----

 PURPOSE: Displays keyboard characters until Escape is received.

 INPUT: None

 OUTPUT: int - Zero after Escape is read.

 ASSUMPTIONS: Keyboard input is available through Cconis/Cnecin.
*/
int main()
{
    char key;

    printf("Input test: press keys to display their values.\n");
    printf("Press Escape to exit.\n");

    while (1) {
        if (has_input()) {
            key = get_input();
            printf("Character: '%c', value: %u\n", key, (unsigned int)key);

            if ((unsigned char)key == ESC_KEY) {
                break;
            }
        }
    }
    return 0;
}