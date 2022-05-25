#include "Logger.h"
#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>

using namespace std;

Logger::logConsola(const char* tag, const char* mensaje) {
	time_t tiempoRaw;
	struct tm* infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* stringTiempo = asctime(infoTiempo);
	stringTiempo[strlen(stringTiempo) - 1] = '\0';

	cout << "[" << stringTiempo << "][TAG: " << tag << "]: " << mensaje << endl;
}

Logger::logTxt(const char* tag, const char* mensaje) {
	time_t tiempoRaw;
	struct tm* infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* stringTiempo = asctime(infoTiempo);
	stringTiempo[strlen(stringTiempo) - 1] = '\0';

	ofstream fichero;
	fichero.open("logs.txt", ios::app | ios::out);
	fichero << "[" << stringTiempo << "][TAG: " << tag << "]: " << mensaje << endl;
	fichero.close();
}
