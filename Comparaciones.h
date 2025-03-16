#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Comparaciones {
	vector<string> lineas_archivo1;
	vector<string> lineas_archivo2;
	vector <string> parametros;
	int contador = 1, retorno = 0, numeroLineas = 0;
	size_t numeroCaracteres = 0;
	string nombreArchivo1, nombreArchivo2, nombreEjecutable;
	bool isMenu = false, isEstricto = false, isOrdenado = false, isInsensible = false;
	bool isEstadistica = false, isSilencioso = false, isCreditos = false, sonIguales = false;
public:
	Comparaciones(int argc, char* argv[]);
	~Comparaciones();
	int menu();
	void getParametros();
	void comparacion();
	void ordenacion(vector<string>& lineasArchivo, int contador = 1);
	void insensible(vector<string>& lineasArchivo, int contador = 1);
	void estadisticas();
	void silencioso();
	void argumentos();
	void creditos();
	// otros metodos de ayuda
	int ejecucionPrograma();
	bool extraerLineasDeArchivos();
	void getNumeroLineas_Caracteres(vector<string> lineasArchivo, int lineaInicial, size_t caracterLineal);
};

