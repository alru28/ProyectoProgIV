#include <time.h>
#include <stdio.h>

void main() {
    time_t rawtime;
    struct tm* fechaRaw;
    char fecha[20];
    time(&rawtime);
    fechaRaw = localtime(&rawtime);
    printf("Fecha sin el formateo:%s\n", fecha);
    fechaRaw->tm_mday -= 0;
    mktime(fechaRaw);
    printf("Fecha raw:%s\n", fechaRaw);
    strftime(fecha, 80, "%Y-%m-%d", fechaRaw);
    printf("Fecha con el formateo:%s\n", fecha);
}