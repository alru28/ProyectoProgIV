#ifndef FORMATEADOR_H_
#define FORMATEADOR_H_
#include "../../Admin/BaseDatos/sqlite3.h"
#include "../../Admin/Lote/Lote.h"
#include "../../Admin/Objeto/Objeto.h"


//Formateador convierte lo que hay en C en el formato con separadores

char* formatearLotes();
char* formatearObjetos();

#endif /* FORMATEADOR_H_ */