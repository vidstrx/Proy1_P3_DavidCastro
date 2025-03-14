#include "Comparaciones.h"

Comparaciones::Comparaciones(int argc, char* argv[]) {
	// empieza en 1 para no tomar en cuenta la direccion del proyecto
	// y agarrar solo los comandos despues de la direccion
	for (int indice = 1; indice < argc; indice++) {
		argumentos.push_back(argv[indice]);
		cout << argumentos[indice-1] << endl; // se resta 1 para que empiece en la posicion 0 ya que ahi es donde se guarda el primer comando
	}

	// sacar el nombre del ejecutable
	string ruta = argv[0];
	string temp; 
	// ciclo for para sacar el nombre del ejecutable desde el final de la ruta hasta que encuentre el primer '\'
	for (size_t indice = ruta.size(); indice > 0; indice--) {
		char letra = ruta[indice];
		if (letra == '\\') {
			break;
		}
		temp += letra; // guardar el nombre del ejecutable al reves temporalmente
	}
	// luego este ciclo for agrega las letras del nombre del ejecutable de forma correcta
	for (size_t indice = temp.size(); indice > 0; indice--) {
		char letra = temp[indice];
		this->nombreEjecutable += letra;
	}
}


// \x1b[96m = Cyan claro
// \x1b[0m = color normal de terminal
// \x1b[95m = Morado claro
// \x1b[93m = Amarillo claro
// \x1b[91m = Rojo claro
// \x1b[92m = Verde claro
// \x1b[90m = Negro claro

void Comparaciones::menu() {
	cout << "\x1b[96mUso:\x1b[0m " << this->nombreEjecutable << " \x1b[95m[opciones]\x1b[0m \x1b[93marchivo1 archivo2\x1b[0m\n" << endl;
	cout << "\x1b[96mEste programa compara \'\x1b[93marchivo1\x1b[96m\' y \'\x1b[93marchivo2\x1b[96m\'; linea por linea,\nmostrando las lineas donde se encuentran \x1b[91mdiferencias\x1b[96m o \x1b[92msimilitudes.\x1b[0m\n" << endl;
	cout << "\x1b[95mOpciones:\x1b[0m\n" << endl;
	cout << "\x1b[95m-h \x1b[96m: Muestra la lista de opciones del programa (esta pantalla)" << endl;
	cout << "\x1b[95m-e \x1b[96m: Modo estricto (compara todo de forma inegra) \x1b[93m(incompatible con '\x1b[95m-s\x1b[93m')" << endl;
	cout << "\x1b[95m-s \x1b[96m: Modo ordenado (ordena el contenido antes de comparar) \x1b[93m(incompatible con '\x1b[95m-e\x1b[93m')" << endl;
	cout << "\x1b[95m-i \x1b[96m: Modo insensible (ignora las diferencias entre mayusculas y minusculas)" << endl;
	cout << "\x1b[95m-t \x1b[96m: Modo estadisticas (muestra el numero de lineas y caracteres) \x1b[93m(incompatible con '\x1b[95m-q\x1b[93m')" << endl;
	cout << "\x1b[95m-q \x1b[96m: Modo silencioso (no muestra las lineas que son iguales) \x1b[93m(incompatible con '\x1b[95m-t\x1b[93m')" << endl;
	cout << "\x1b[95m-c \x1b[96m: Modo creditos (muestra version de programa, compilador y autor) \x1b[93m(incompatible con '\x1b[95m-q\x1b[93m')\x1b[0m" << endl;
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
	// usar for para ambos archivos y comparar con los indices si son iguales o no las cadenas
}

int Comparaciones::ejecucionPrograma() {
	return 0;
}

Comparaciones::~Comparaciones() {

}
