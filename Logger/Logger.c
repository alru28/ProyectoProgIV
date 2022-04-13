#include "Logger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

void logTxt(char* tag, char* mensaje) {
	time_t tiempoRaw;
	struct tm * infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* stringTiempo = asctime(infoTiempo);
	stringTiempo[strlen(stringTiempo) - 1] = '\0';

	FILE* logs = fopen("../Logger/logs.txt", "a");
	fprintf(logs, "[%s][TAG: %s]: %s\n", stringTiempo, tag, mensaje);
}

void logConsola(char* tag, char* mensaje) {
	time_t tiempoRaw;
	struct tm* infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* stringTiempo = asctime(infoTiempo);
	stringTiempo[strlen(stringTiempo) - 1] = '\0';

	printf("[%s][TAG: %s]: %s\n", stringTiempo, tag, mensaje);
}