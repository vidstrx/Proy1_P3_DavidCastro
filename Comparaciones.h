#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Comparaciones {
	vector<string> lineas_archivo1;
	vector<string> lineas_archivo2;
	vector <string> parametros;
	int contador = 1;
	string nombreArchivo1, nombreArchivo2, nombreEjecutable;
	bool isMenu = false, isEstricto = false, isOrdenado = false, isInsensible = false;
	bool isEstadistica = false, isSilencioso = false, isCreditos = false;
public:
	Comparaciones(int argc, char* argv[]);
	~Comparaciones();
	void buscarArchivos();
	void compararArchivos();
	bool extraerLineasDeArchivos();
	void argumentos();
	void creditos();
	int ejecucionPrograma();
	int menu();
};

