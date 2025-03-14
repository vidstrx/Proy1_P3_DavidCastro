#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Comparaciones {
	vector<string> lineas_archivo1;
	vector<string> lineas_archivo2;
	vector <string> argumentos;
	string nombreEjecutable;
public:
	Comparaciones(int argc, char* argv[]);
	~Comparaciones();
	void compararArchivos();
	int ejecucionPrograma();
	void menu();
};

