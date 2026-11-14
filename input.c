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