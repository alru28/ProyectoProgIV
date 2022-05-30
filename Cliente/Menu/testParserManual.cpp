#include <iostream>
#include "string.h"

using namespace std;

//cd cliente/menu && g++ -o maintestparser.exe testParserManual.cpp

int main(){
    char* bigString;
    
    cout<<"LOTES ACTIVOS:"<<endl;
    char *lote = strtok(bigString, "|");
    char idLote [20];
    char fechaIni [20];
    char fechaFin[20];
    char dollars[20];

    
    
    while(strcmp(lote ,"#") !=0){

        strcpy(idLote, strtok(lote, ";"));
        strcpy(fechaIni , strtok(NULL, ";"));
        strcpy(fechaFin , strtok(NULL, ";"));
        strcpy(dollars , strtok(NULL, ";"));
        cout <<"Lote "<< idLote << ". " <<fechaIni << " - " << fechaFin << ". Precio: " << dollars << endl;
        lote = strtok(NULL, "|");
    }


}