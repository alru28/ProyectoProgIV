#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;

//cd cliente/menu && g++ -o maintestparser.exe testParserManual.cpp

int main(){

    char bigString [500];
    strcpy(bigString, "1;2020-12-12;2021-11-11;$$$|2;2020-12-12;2021-11-11;$$$|#");
    int i = 0;

    cout<<"LOTES ACTIVOS:"<<endl;

    //Get first token de barras
    char* tokenGrande = strtok(bigString, "|");
    while(tokenGrande != NULL)
    {
        while(tokenGrande[i] != ';'){
            cout<<tokenGrande[i];
            i++;
        }

        //Siguiente token
        tokenGrande = strtok(NULL, "|");
    }
    
}
