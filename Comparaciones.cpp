#include "Comparaciones.h"

void Comparaciones::menu(char* argv[]) {
	string ruta(argv[0]);
	
	cout << "Uso: " << argv[0] << " [opciones] archivo1 archivo2" << endl;
}

void Comparaciones::compararArchivos() {
	string linea;
	ifstream archivo1("archivo1.txt");
	ifstream archivo2("archivo2.txt");
	while (getline(archivo1, linea)) {
		lineas_archivo1.push_back(linea);
	}
	archivo1.close();

	while (getline(archivo2, linea)) {
		lineas_archivo2.push_back(linea);
	}
	archivo2.close();

}

int Comparaciones::ejecucionPrograma() {
	return 0;
}

Comparaciones::~Comparaciones() {

}
