#include "Parser.h"


Objeto* parseObjetos(char* bruto)
{
    char atr[100];
    int i = 0;
    int cont = 0;

    while(bruto[i] != '¬') //Recorrer todo el string
    {
        if(bruto[i] == '|') cont++; //Contar barras
        i++;
    }

    Objeto arrObjetos[cont]; //Declaramos array de elementos

    i = 0;
    int cuentaObjetos = 0;

    while(bruto[i] != '¬')
    {
        int cuentaAtributos = 0; //Empezamos desde el primer atributo

        while(bruto[i] != '|') //Estamos dentro de un objeto
        {
            char* atr = {'\0'}; //Creamos/vaciamos la variable de texto donde va el atributo que vamos a parsear

            do //Estamos dentro de un atributo
            {
                //Meter caracter en atr
                strcat(atr, (char*)bruto[i]);
                i++;
            }while(bruto[i] != ';');

            //Asignar atributo a atributo correspondiente con case switch
            switch(cuentaAtributos)
            {
                case(0):
                    arrObjetos[cuentaObjetos].ID_Objeto = (int) atr;
                    break;
                case(1):
                    strcpy(arrObjetos[cuentaObjetos].Categoria, atr);
                    break;
                case(2):
                    strcpy(arrObjetos[cuentaObjetos].Estado, atr);
                    break;
                case(3):
                    strcpy(arrObjetos[cuentaObjetos].Descripcion, atr);
                    break;
                case(4):
                    arrObjetos[cuentaObjetos].PrecioSalida = (int) atr;
                    break;
                case(5):
                    arrObjetos[cuentaObjetos].ID_Subastador = (int) atr;
                    break;
                case(6):
                    arrObjetos[cuentaObjetos].ID_Lote = (int) atr;
                    break;
            }
            cuentaAtributos++; //A por el siguiente atributoooo
            //Al llegar aqui, hemos metido el atributo. Si nos encontramos con una | va a salir y hacer i++, lo que lleva a encontrarse o | o ¬, cubiertos los dos casos.
            //Si nos encontramos con algo que no sea barra, va a ser un ;, vamos hacia arriba, reseteamos el atributo temporal. Con do while forzamos a hacer al menos un i++ para no toparnos de primeras con ;, lo que lo sacaria del bucle, jejej solucionado????
        }
        cuentaObjetos++; //Siguiente objetoooo
        i++;
    }
    return arrObjetos;
}



//1;Casa y jardin;Casi nuevo;Mecedora negra;20;4;|12;Casa y jardin;Nuevo;Mesita de cristal;200;3;1;|


















/*
Lote* parseLotes(char* bruto)
{
    char temp[100];
    int cont = 0;
    while(bruto[cont] != '¬') cont++; //Contar numero de separadores (que es el numero de elementos)
    Lote arrLotes[cont]; //Declaramos array de elementos

    int i=0; //Contar caracteres
    int j=0; //Contar lotes
    
     while (bruto[i] != '¬') //Recorrer todo mirando que no se ha acabado el texto
     {
        Lote temp;  //Si estamos aqui es porque acaba de empezar un objeto -  no hace falta crear un objeto, solo con poner arrLotes[1][1] deberia servir quiero pensar
        int contAtributo = 0;
        if(bruto[i] == '|' || i==0) //Estamos dentro de un objeto - problema el primero de todos, si i==0 funciona? lol
        {
            if(i!=0) i++; //Pasamos de | al primer caracter del primer atributo, menos en caso de que sea el primer caracter
            char atributoTemp[60] = {'\0'}; //Inicializamos la variable donde vamos a meter el texto que vamos leyendo
            while(bruto[i] != ';') //Estamos dentro de un atributo de ese objeto
            {
                //Vamos a parsear todo el texto y luego un case switch para ver en que atributo meter el atributo
                strcat(atributoTemp, (char*) bruto[i]);
                i++;
            }
            //Se ha acabado de parsear un atributo, ahora lo metemos en el atributo correspondiente y pasamos al siguiente.
            switch(contAtributo)
            {
                case(0):
                    temp.idLote = (int)atributoTemp;
                    break;
                case(1):
                    temp.fechaCom = (int)atributoTemp;
                    break;
                case(2):
                    temp.fechaFin = (int)atributoTemp;
                    break;
                case(3):
                    strcpy(temp.estado, (char*) atributoTemp);
                case(4):
                    temp.avgPrecio = (int)atributoTemp;
                case(5):
                    //jajajaj esta es de mofa
            }
            //Aqui acabas de acabar de crear un atributo, por lo que vas al siguiente, pero esta mal porque te acabas el if y pasarias a hacer i++, sales al while y buscaria si estas en | o 0. Si pongo que tambien vale que sea punto y coma? no
            contAtributo++;
        }
        //Aqui metemos temp en el array de Lotes - igual no hace falta si asignamos directamente al atributo
        i++;
     } 
    
    
}
*/

// atr1;atr2;atr3;|atr1;atr2;atr3;|¬

