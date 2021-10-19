#include "Metodo_2.h"

string text2bin(string texto)
{
    string binario,aux;
    for(unsigned long long i=0;i<texto.length();i++){
        aux=int2bin(texto[i]);
        binario.append(aux);
    }
    return binario;
}

string int2bin(char letra)
{
    string binario;
    for(int i=0;i<8;i++){
        binario.push_back(((letra<<i)&0b10000000)/128);
    }
    return binario;
}

string reglas_codifica(string binario, int semilla, bool dir)
{
    string pedazo,datos;
    for(unsigned long long i=0;i<binario.length();i++){
        pedazo.push_back(binario[i]);
        if((i+1)%semilla==0 || i==binario.length()-1){
            pedazo=metodo2(pedazo,dir);
            datos.append(pedazo);
            pedazo.clear();
        }
    }
    return datos;
}

string metodo2(string pedazo,bool dir)
{
    string datos;
    if(dir){
        datos.push_back(pedazo[pedazo.length()-1]);
        for(unsigned long long i=0;i<pedazo.length()-1;i++){
            datos.push_back(pedazo[i]);
        }
    }else{
        for(unsigned long long i=1;i<pedazo.length();i++){
            datos.push_back(pedazo[i]);
        }
        datos.push_back(pedazo[0]);
    }
    return datos;
}

string bin2text(string binario)
{
    string datos,pedazo;
    for(unsigned long long i=0;i<binario.length();i++){
        pedazo.push_back(binario[i]);
        if((i+1)%8==0){
            datos.push_back(conv_letra(pedazo));
            pedazo.clear();
        }
    }
    return datos;
}

char conv_letra(string pedazo)
{
    char l=0;
    for(unsigned long long i=0,j=128;i<pedazo.length();i++, j/=2){
        l+=j*pedazo[i];
    }
    return l;
}
