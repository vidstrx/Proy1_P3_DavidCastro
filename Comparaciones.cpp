#include "Comparaciones.h"
#define CYAN "\x1b[96m" // \x1b[96m = Cyan claro
#define NORMAL "\x1b[0m" // \x1b[0m = color normal de terminal
#define MORADO "\x1b[95m" // \x1b[95m = Morado claro
#define AMARILLO "\x1b[93m" // \x1b[93m = Amarillo claro
#define ROJO "\x1b[91m" // \x1b[91m = Rojo claro
#define VERDE "\x1b[92m" // \x1b[92m = Verde claro
#define GRIS "\x1b[90m" // \x1b[90m = Negro claro
#define BLANCO "\x1b[97m" // \x1b[97m = Blanco claro

Comparaciones::Comparaciones(int argc, char* argv[]) {
	// empieza en 1 para no tomar en cuenta la direccion del proyecto
	// y agarrar solo los comandos despues de la direccion
	for (int indice = 1; indice < argc; indice++) 
		parametros.push_back(argv[indice]);

	// sacar el nombre del ejecutable
	string ruta = argv[0];
	string temporal; 
	// ciclo for para sacar el nombre del ejecutable desde el final de la ruta hasta que encuentre el primer '\'
	for (size_t indice = ruta.size(); indice > 0; indice--) {
		char letra = ruta[indice];
		if (letra == '\\') 
			break;
		temporal += letra; // guardar el nombre del ejecutable al reves temporalmente
	}
	// luego este ciclo for agrega las letras del nombre del ejecutable de forma correcta
	for (size_t indice = temporal.size(); indice > 0; indice--) {
		char letra = temporal[indice];
		this->nombreEjecutable += letra;
	}
}

void Comparaciones::getParametros() {
	for (int indice = 0; indice < parametros.size(); indice++) {
		if (parametros[indice][0] == '-') {
			if (parametros[indice].substr(0,2) == "-e")
				this->isEstricto = true;
			else if (parametros[indice].substr(0, 2) == "-s")
				this->isOrdenado = true;
			else if (parametros[indice].substr(0, 2) == "-i")
				this->isInsensible = true;
			else if (parametros[indice].substr(0, 2) == "-t")
				this->isEstadistica = true;
			else if (parametros[indice].substr(0, 2) == "-q")
				this->isSilencioso = true;
			else if (parametros[indice].substr(0, 2) == "-c")
				this->isCreditos = true;
			else if (parametros[indice].substr(0, 2) == "-h"){
				this->isMenu = true;
				this->isEstricto = false;
				this->isEstadistica = false;
				this->isCreditos = false;
				this->isOrdenado = false;
				this->isInsensible = false;
				break;
			} else {
				this->isMenu = true;
				this->retorno = 7;
				break;
			}
		} else {
			this->contador++;
			if (this->contador == 1) {
				this->nombreArchivo1 = parametros[indice];
			} else if (this->contador == 2) {
				this->nombreArchivo2 = parametros[indice];
			} else { // este es el caso en que llega a mas de 2, significa que se encontraron mas de 2 archivos
				break;
			}
		}
	}

	if (this->contador < 2) {
		 if (isCreditos) {
			 creditos();
			 this->isCreditos = false;
		 } else if (parametros.size() <= 2 || parametros.size() > 2){
			 if (!isMenu) {
				 this->retorno = 2;
				 this->isMenu = true;
			 }
		 }
	} else if (this->contador > 2) {
		this->retorno = 1;
		this->isMenu = true;
	} else if (isEstricto && isOrdenado) {
		cout << ROJO "Modos 'estricto' y 'ordenado' son INCOMPATIBLES!" NORMAL << endl;
		this->retorno = 3;
		this->isMenu = true;
	} else if (isSilencioso && (isEstadistica || isCreditos)) {
		cout << ROJO "Modos 'silencioso' y 'estadistica' o 'creditos' son INCOMPATIBLES!\n" NORMAL << endl;
		this->retorno = 4;
		this->isMenu = true;
	}
}

void Comparaciones::menu() {
	cout << CYAN "Uso: " BLANCO << this->nombreEjecutable << MORADO " [opciones]" AMARILLO " archivo1 archivo2\n" NORMAL << endl;
	cout << CYAN "Este programa compara \'" AMARILLO "archivo1" CYAN "\' y \'" AMARILLO "archivo2" CYAN "\'; linea por linea,\nmostrando las lineas donde se encuentran " ROJO "diferencias" CYAN " o " VERDE "similitudes.\n" NORMAL << endl;
	cout << MORADO "Opciones:\x1b[0m\n" << endl;
	cout << MORADO "-h " CYAN ": Muestra la lista de opciones del programa (esta pantalla)" << endl;
	cout << MORADO "-e " CYAN ": Modo estricto (compara todo de forma inegra) " AMARILLO "(incompatible con '" MORADO "-s" AMARILLO "')" << endl;
	cout << MORADO "-s " CYAN ": Modo ordenado (ordena el contenido antes de comparar) " AMARILLO "(incompatible con '" MORADO "-e" AMARILLO "')" << endl;
	cout << MORADO "-i " CYAN ": Modo insensible (ignora las diferencias entre mayusculas y minusculas)" << endl;
	cout << MORADO "-t " CYAN ": Modo estadisticas (muestra el numero de lineas y caracteres) " AMARILLO "(incompatible con '" MORADO "-q" AMARILLO "')" << endl;
	cout << MORADO "-q " CYAN ": Modo silencioso (no muestra las lineas que son iguales) " AMARILLO "(incompatible con '" MORADO "-t" AMARILLO "' y '" MORADO "-c" AMARILLO "') " << endl;
	cout << MORADO "-c " CYAN ": Modo creditos (muestra version de programa, compilador y autor) " AMARILLO "(incompatible con '" MORADO "-q" AMARILLO "')" NORMAL << endl;
}

bool Comparaciones::extraerLineasDeArchivos() {
	if (!isMenu) {
		string lineaTxt1, lineaTxt2;
		ifstream archivo1(nombreArchivo1);
		ifstream archivo2(nombreArchivo2);
		if (archivo1.fail()) {
			cout << ROJO "No encuentro el archivo1 (\'" << nombreArchivo1 << "\')!" NORMAL << endl;
			if (archivo2.fail())
				cout << ROJO "No encuentro el archivo2 (\'" << nombreArchivo2 << "\')!" NORMAL << endl;
			this->retorno = 5;
			this->isEstricto = false;
			this->isEstadistica = false;
			this->isCreditos = false;
			this->isOrdenado = false;
			this->isInsensible = false;
		} else if (archivo2.fail()) {
			cout << ROJO "No encuentro el archivo2 (\'" << nombreArchivo2 << "\')!" NORMAL << endl;
			this->retorno = 5;
			this->isEstricto = false;
			this->isEstadistica = false;
			this->isCreditos = false;
			this->isOrdenado = false;
			this->isInsensible = false;
		} else {
			/*archivo.eof() devuelve true si se llego hasta el final del archivo y false si aun
			no ha llegado al final. En el while se usa ! porque si no lo usamos entonces ambos
			archivos.eof() devolveran false porque al principio no han llegado hasta el final del archivo
			por lo que hara que no entre al ciclo, en cambio si negamos false sera true (!false = true).
			Ya cuando ambos archivos lleguen al final devolveran true pero al ser negado sera false
			(!true = false) haciendo que salga del ciclo. Haciendo esto hara que ambos vectores tengan el
			mismo tamaño y asi verificar cada linea*/
			while (!(archivo1.eof() && archivo2.eof())) {
				/*Estos if verifican si en alguno de los dos archivos ha llegado hasta el final,
				en caso de que se haya llegado entonces le pondra a la linea correspondiente EOF
				para indicar que ya no hay mas lineas en el archivo. Esto funciona si un archivo
				tiene mas lineas que el otro archivo pero si ambos tienen la misma cantidad de
				lineas entonces no entrara en ninguno nunca*/
				if (archivo1.eof())
					lineaTxt1 = "EOF";
				else if (archivo2.eof())
					lineaTxt2 = "EOF";
				getline(archivo1, lineaTxt1);
				getline(archivo2, lineaTxt2);
				this->lineas_archivo1.push_back(lineaTxt1);
				this->lineas_archivo2.push_back(lineaTxt2);
			}
			archivo1.close();
			archivo2.close();
			return true;
		}
	} else
		menu();
	return false;
}

void Comparaciones::argumentos() {
	cout << CYAN "\nARGUMENTOS: \n" << endl;
	cout << GRIS   "	   Estricto: " << (this->isEstricto ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	   Ordenado: " << (this->isOrdenado ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	 Insensible: " << (this->isInsensible ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	Estadistica: " << (this->isEstadistica ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	 Silencioso: " << (this->isSilencioso ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	   Creditos: " << (this->isCreditos ? VERDE "SI" : MORADO "NO") << endl;
	cout << GRIS   "	   Archivo1: " BLANCO << this->nombreArchivo1 << endl;
	cout << GRIS   "	   Archivo2: " BLANCO << this->nombreArchivo2 << endl << endl;
}

void Comparaciones::comparacion() {
	int contador = 0;
	cout << CYAN "\nCOMPARACION: \n" NORMAL << endl;
	for (int indice = 0; indice < lineas_archivo1.size(); indice++) {
		if (lineas_archivo1[indice] == lineas_archivo2[indice]) {
			cout << VERDE "	" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' == " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'" NORMAL << endl;
			contador++;
		} else 
			cout << ROJO "	" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' != " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'" NORMAL << endl;
	}

	if (contador == lineas_archivo1.size())
		this->sonIguales = true;
	else 
		this->sonIguales = false;
	conclusion();		
}

/* el contador de este metodo solo es para saber cuantas veces entro para poder imprimir la informacion una sola vez y
se deja por defecto el numero 1, osea si es 1 entonces imprimira, si es otro numero entonces no imprimira*/
void Comparaciones::ordenacion(vector<string>& lineasArchivo, int contador) {
	int posicionEOF = 0;
	if (contador == 1) {
		cout << AMARILLO "	Archivo1: " NORMAL "\'desorden -> orden\'" << endl;
		cout << AMARILLO "	Archivo2: " NORMAL "\'desorden -> orden\'" << endl;
	}
	for (int indice = 0; indice < lineasArchivo.size(); indice++) {
		if (lineasArchivo[indice] == "EOF") {
			posicionEOF = indice;
			break;
		}
	}
	if (posicionEOF == 0)
		sort(lineasArchivo.begin(), lineasArchivo.end());
	else
		sort(lineasArchivo.begin(), (lineasArchivo.begin() + posicionEOF));
}

/* el contador de este metodo solo es para saber cuantas veces entro para poder imprimir la informacion una sola vez y
se deja por defecto el numero 1, osea si es 1 entonces imprimira, si es otro numero entonces no imprimira*/
void Comparaciones::insensible(vector<string>& lineasArchivo, int contador) {
	string temporal;
	if (contador == 1) {
		cout << AMARILLO "	Archivo1: " NORMAL "\'mayusculas -> minusculas\'" << endl;
		cout << AMARILLO "	Archivo2: " NORMAL "\'mayusculas -> minusculas\'" << endl;
	}
	for (int indice = 0; indice < lineasArchivo.size(); indice++) {
		for (char letra : lineasArchivo[indice]) {
			letra = tolower(letra);
			temporal += letra;
		}
		lineasArchivo[indice] = temporal;
		temporal = "";
	}
}

void Comparaciones::silencioso() {
	vector<int> posiciones;
	for (int indice = 0; indice < lineas_archivo1.size(); indice++) {
		if (lineas_archivo1[indice] != lineas_archivo2[indice]) 
			posiciones.push_back(indice);
	}

	if (!posiciones.empty()) {
		cout << CYAN "\nCOMPARACION: \n" NORMAL << endl;
		this->sonIguales = false;
		for (int indice = 0; indice < posiciones.size(); indice++) 
			cout << ROJO "	" << nombreArchivo1 << ": \'" << lineas_archivo1[posiciones[indice]] << "\' != " << nombreArchivo2 << ": \'" << lineas_archivo2[posiciones[indice]] << "\'" NORMAL << endl;
		conclusion();
	}
}

void Comparaciones::estadisticas() {
	getNumeroLineas_Caracteres(lineas_archivo1, 0, 0);
	cout << GRIS "	 Archivo 1: " AMARILLO << this->nombreArchivo1 << endl;
	cout << GRIS "	    Lineas: " VERDE << this->numeroLineas << endl;
	cout << GRIS "	Caracteres: " MORADO << this->numeroCaracteres << '\n' << endl;

	getNumeroLineas_Caracteres(lineas_archivo2, 0, 0);
	cout << GRIS "	 Archivo 2: " AMARILLO << this->nombreArchivo2 << endl;
	cout << GRIS "	    Lineas: " VERDE << this->numeroLineas << endl;
	cout << GRIS "	Caracteres: " MORADO << this->numeroCaracteres << NORMAL << endl;
}

void Comparaciones::creditos() {
	cout << CYAN "\nCREDITOS: \n" << endl;
	cout << GRIS "	  Programa: " VERDE << this->nombreEjecutable << endl;
	cout << GRIS "	   Version: " AMARILLO "1.1" << endl;
	cout << GRIS "	  Proyecto: " MORADO "Programacion III - Parte I\n" << endl;

	cout << GRIS "	  Lenguaje: " VERDE "C++" << endl;
	cout << GRIS "	Compilador: " AMARILLO "Microsoft Visual Studio Community 2022 (64 - bit)" << endl;
	cout << GRIS "	   Version: " MORADO "17.13.0\n" << endl;

	cout << GRIS "	     Autor: " VERDE "David Castro" << endl;
	cout << GRIS "	    Correo: " AMARILLO "david_castro@unitec.edu" << endl;
	cout << GRIS "	     Fecha: " MORADO "2025-03-20\x1b[0m" << endl;
}

void Comparaciones::conclusion() {
	cout << CYAN "\nCONCLUSION: \n" << endl;
	if (this->sonIguales) {
		cout << VERDE "	Los archivos '" << nombreArchivo1 << "' y '" << nombreArchivo2 << "' tienen el MISMO contenido!" << NORMAL << endl;
		this->retorno = 0;
	} else {
		cout << ROJO "	Los archivos '" << nombreArchivo1 << "' y '" << nombreArchivo2 << "' tienen DIFERENTE contenido!" << NORMAL << endl;
		this->retorno = 6;
	}
}

void Comparaciones::getNumeroLineas_Caracteres(vector<string> lineasArchivo, int lineaInicial, size_t caracterInicial) {
	for (int indice = 0; indice < lineasArchivo.size(); indice++) {
		if (!(lineasArchivo[indice] == "EOF")) {
			this->numeroLineas = (lineaInicial+=1);
			this->numeroCaracteres = (caracterInicial+=lineasArchivo[indice].size());
		} else
			break;
	}
}

int Comparaciones::ejecucionPrograma() {
	getParametros();
	if (isSilencioso) {
		extraerLineasDeArchivos();
		if (isOrdenado) {
			ordenacion(lineas_archivo1, 2);
			ordenacion(lineas_archivo2, 2);
		}
		if (isInsensible) {
			insensible(lineas_archivo1, 2);
			insensible(lineas_archivo2, 2);
		}
		silencioso();
	} else if (!isMenu) {
		if (!(this->contador < 2)) {
			argumentos();
			bool seExtrajo = extraerLineasDeArchivos();
		
			if (isInsensible) {
				cout << CYAN "\nCONVERSION: \n" NORMAL << endl;
				insensible(lineas_archivo1);
				insensible(lineas_archivo2,2);
			}
			
			if (isOrdenado) {
				cout << CYAN "\nORGANIZACION: \n" NORMAL << endl;
				ordenacion(lineas_archivo1);
				ordenacion(lineas_archivo2,2);
			}

			if (seExtrajo)
				comparacion();
			if (isEstadistica) {
				cout <<  CYAN "\nESTADISTICAS: \n" << endl;
				estadisticas();
			}
			if (isCreditos) 
				creditos();
		}
	} else
		menu();
	return this->retorno;
}

Comparaciones::~Comparaciones() {
}
