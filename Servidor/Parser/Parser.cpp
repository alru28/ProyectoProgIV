#include "Parser.h"

Lote* parseLotes(char* bruto)
{
    char temp[100];
    int i = 0;
    int cont = 0;

    while(bruto[i] != '¬') //Recorrer todo el string
    {
        if(bruto[i] == '|') cont++; //Contar barras
        i++;
    }
    Lote arrLotes[cont]; //Declaramos array de elementos

    i = 0;
    int cuentaLotes = 0;

    while(bruto[i] != '¬')
    {
        int cuentaAtributos = 0; //Empezamos desde el primer atributo

        while(bruto[i] != '|') //Estamos dentro de un objeto
        {
            char* atr = {'\0'}; //Creamos/vaciamos la variable de texto donde va el atributo que vamos a parsear

            do //Estamos dentro de un atributo
            {
                //Meter caracter en atr
                i++;
            }while(bruto[i] != ';');

            //Asignar atributo a atributo correspondiente con case switch
            switch(cuentaAtributos)
            {
                case(0):
                    //Meter en atributo 1
                    break;
                case(1):
                    //Meter en atributo 2
                    break;
                case(2):
                    //Meter en atributo 3
                    break;
                case(3):
                    //Meter en atributo 4
                    break;
                case(4):
                    //Meter en atributo 5
                    break;
                case(5):
                    //Meter en atributo 6
                    break;
                case(6):
                    //Meter en atributo 7
            }
            cuentaAtributos++; //A por el siguiente atributoooo
            //Al llegar aqui, hemos metido el atributo. Si nos encontramos con una | va a salir y hacer i++, lo que lleva a encontrarse o | o ¬, cubiertos los dos casos.
            //Si nos encontramos con algo que no sea barra, va a ser un ;, vamos hacia arriba, reseteamos el atributo temporal. Con do while forzamos a hacer al menos un i++ para no toparnos de primeras con ;, lo que lo sacaria del bucle, jejej solucionado????
        }

        i++;
    }
}





















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

