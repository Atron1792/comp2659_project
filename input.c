/*
File Name: input.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Encapsulates TOS keyboard polling and keyboard-character retrieval.
*/

#include <osbind.h>

#include "input.h"

int has_input(void)
{
    return Cconis();
}

char get_input(void)
{
    return (char)Cnecin();
}