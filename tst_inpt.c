/*
File Name: tst_inpt.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Tests nonblocking keyboard detection and character retrieval.
*/

#include <stdio.h>

#include "input.h"

#define ESC_KEY 27

int main(void)
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