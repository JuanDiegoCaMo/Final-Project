#ifndef ARCHIVOS_TEXTO_H
#define ARCHIVOS_TEXTO_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void crear_txt(string name);
void escribir(string texto, string nombre, bool modo);
string leer(string nombre, bool modo);

#endif // ARCHIVOS_TEXTO_H
