#include "Objeto.h"
#include <stdio.h>

int main(void){
    Objeto o2 = {1, "as", "estado", "descr", 12, 34, 56};
    imprimirObjeto(o2);

    Objeto o1 = crearObjeto();
    imprimirObjeto(o1);
}