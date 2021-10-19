#include "archivos_texto.h"

void crear_txt(string name){
    fstream text(name, fstream::out | fstream:: binary);
    text.close();
}

void escribir(string texto, string nombre, bool modo){
    if(modo){
        fstream text(nombre, fstream::out);
        text <<texto;
        text.close();
    }else{
        fstream text(nombre,fstream::out | fstream::binary);
        text << texto;
        text.close();
    }
}

string leer(string nombre, bool modo){
    string datos;
    fstream text;
    unsigned long long tam;
    if(modo){
        text.open(nombre,fstream::in);
        if(text.is_open()){
            while(!text.eof()){
                datos.push_back(text.get());
            }
            datos.pop_back();
        }
        else cout << "El archivo no pudo ser abierto"<<endl;
    }
    else{
        text.open(nombre,fstream::in | fstream::binary | fstream::ate);
        if(text.is_open()){
            tam=text.tellg();
            text.seekg(0);
            for(unsigned long long i=0;i<tam;i++){
                datos.push_back(text.get());
            }
        }else cout << "El archivo no pudo ser abierto"<<endl;
    }
    text.close();
    return datos;
}
