#include "Parser.h"

Lote* parseLotes(char* bruto)
{
    char temp[100];
    int cont = 0;
    while(bruto[cont] != '¬') cont++; //Contar numero de separadores (que es el numero de elementos)
    Lote arrLotes[cont]; //Declaramos array de elementos

    int i=0;
    
     while (bruto[i] != '¬') //Recorrer todo mirando que no se ha acabado el texto
     {
        Lote temp;  //Si estamos aqui es porque acaba de empezar un objeto
        if(bruto[i] != '|') //Estamos dentro de un objeto
        {
            int contAtributo = 0;
            if(bruto[i] != ';') //Estamos dentro de un atributo de ese objeto
            {
                //Vamos a parsear todo el texto y luego un case switch para ver en que atributo meter el atributo

            }
            //Aqui metemos temp en el array de Lotes
        }
        i++;
     } 
    
    
}