/*
File Name: tst_efct.c
Authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Provides an interactive test driver for gameplay sound effects.
*/

#include <osbind.h>
#include <stdio.h>

#include "effects.h"
#include "psg.h"

/*----- Function: tstJumpEffect -----

 PURPOSE: Exercises the jump sound effect.

 INPUT: None.

 OUTPUT: None.
*/
static void tstJumpEffect()
{
    playJumpEffect();
}

/*----- Function: tstCollisionEffect -----

 PURPOSE: Exercises the collision sound effect.

 INPUT: None.

 OUTPUT: None.
*/
static void tstCollisionEffect()
{
    playCollisionEffect();
}

/*----- Function: main -----

 PURPOSE: Runs the effects-module test cases.

 INPUT: None.

 OUTPUT: Returns zero after the test cases complete.
*/
int main()
{
    Cconin();
    tstJumpEffect();
    Cconin();
    tstCollisionEffect();
    printf("EFFECTS TESTS COMPLETE.\n");
    return 0;
}