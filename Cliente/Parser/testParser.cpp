#include "../../Cliente/Clases/clases.h"
#include "Parser.h"
#include <iostream>
using namespace std;

int main(void)
{
	char* texto = "1;Casa y jardin;Casi nuevo;Mecedora negra;20;4;|12;Casa y jardin;Nuevo;Mesita de cristal;200;3;1;|";

    Objeto* arrayObjetos = parseObjetos(texto);

    imprimirObjeto(arrayObjetos[0]);

	return 0;
}

