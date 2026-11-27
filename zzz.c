#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>
#include "TYPES.H"

int main() {
	char key = '\0';
	
	while (key == '\0') {
		if (Cconis()) {
			key = (char)Cnecin();
		}
	}
	
	printf("%d\n", (int)key);
	printf("%d\n", key == '\x1b');
	return 0;
}
