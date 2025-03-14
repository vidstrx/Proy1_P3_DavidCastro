#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class Comparaciones {
	vector<string> lineas_archivo1;
	vector<string> lineas_archivo2;
	friend int main(int argc, char* argv[]);
public:
	~Comparaciones();
	void compararArchivos();
	int ejecucionPrograma();
	void menu(char* argv[]);
};

