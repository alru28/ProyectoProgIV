#ifndef FORMATEADOR_H_
#define FORMATEADOR_H_
#include "../../Admin/BaseDatos/sqlite3.h"
#include "../../Admin/Lote/Lote.h"

//Formateador convierte lo que hay en C en el formato con separadores

char* formatearLotes(sqlite3 *db);

#endif /* FORMATEADOR_H_ */