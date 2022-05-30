#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;

//cd cliente/menu && g++ -o maintestparser.exe testParserManual.cpp

int main(){

    char bigString [500];
    strcpy(bigString, "1;2020-12-12;2021-11-11;$$$;|2;2020-12-12;2021-11-11;$$$;|");
    int i = 0;

    cout<<"LOTES ACTIVOS:"<<endl;

    //Get first token de barras
    char* tokenGrande = strtok(bigString, "|");
    char atributo[20];
    while(tokenGrande != NULL)
    {
        //cout << tokenGrande[1] << " " << tokenGrande[2] << " " << tokenGrande[3] << " " << tokenGrande[4] << endl;
        //cout << "End" << endl;
        i=0;
        for(int j=0; j<4; j++)
        {
                        
            switch (j)
            {
            case 0:
                strcpy(atributo, "ID: ");
                break;
            case 1:
                strcpy(atributo, "- Fecha de inicio: ");
                break;
            case 2:
                strcpy(atributo, "- Fecha de finalizacion: ");
                break;
            case 3:
                strcpy(atributo, "- Precio: ");
                break;
            default:
                break;
            }
            cout << " " << atributo;
            //PRINTEAR CHARS HASTA LLEGAR A ;
            while(tokenGrande[i] != ';')
            {
                cout << tokenGrande[i];
                i++;
            }
            i++;
        }
        cout<<endl;
        //Siguiente token
        tokenGrande = strtok(NULL, "|");
    }
    
}
