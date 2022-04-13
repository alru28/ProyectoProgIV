#include "config.h"
#include <stdio.h>
int main() {
	char** strings = cargarConfig("config.txt");
	printf("\n\nIntento imprimir todas las strings del config:");
	for (int i = 0; i < 5; i++) {
		printf("\n%s", strings[i]);
	}

}