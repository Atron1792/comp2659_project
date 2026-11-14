/*
file name: input.h
authors: Muhammad Abdullah, Nicholas Christie, Rohan Pernitsky

Declares the keyboard polling interface used by the game.
*/

#ifndef INPUT_H
#define INPUT_H

/*----- Function: has_input -----

 PURPOSE: Checks whether a keyboard character is available without blocking.

 INPUT: None.

 OUTPUT: Nonzero when input is available; zero otherwise.
*/
int has_input(void);

/*----- Function: get_input -----

 PURPOSE: Reads one pending keyboard character without echoing it.

 INPUT: None.

 OUTPUT: The character read from the keyboard.

 ASSUMPTIONS: The caller has already confirmed input is available.
*/
char get_input(void);

#endif