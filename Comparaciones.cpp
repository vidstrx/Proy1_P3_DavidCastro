#include "Comparaciones.h"
// \x1b[96m = Cyan claro
// \x1b[0m = color normal de terminal
// \x1b[95m = Morado claro
// \x1b[93m = Amarillo claro
// \x1b[91m = Rojo claro
// \x1b[92m = Verde claro
// \x1b[90m = Negro claro
// \x1b[97m = Blanco claro

Comparaciones::Comparaciones(int argc, char* argv[]) {
	// empieza en 1 para no tomar en cuenta la direccion del proyecto
	// y agarrar solo los comandos despues de la direccion
	for (int indice = 1; indice < argc; indice++) 
		parametros.push_back(argv[indice]);
	insensible(parametros, 2);

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
		 } else if (isMenu) {
			 this->retorno = 0;
		 } else {
			 this->retorno = 2;
			 this->isMenu = true;
		 }
	} else if (this->contador > 2) {
		this->retorno = 1;
		this->isMenu = true;
	} else if (isEstricto && isOrdenado) {
		cout << "\x1b[91mModos 'estricto' y 'ordenado' son INCOMPATIBLES!\n\x1b[0m" << endl;
		this->retorno = 3;
		this->isMenu = true;
	} else if (isSilencioso && (isEstadistica || isCreditos)) {
		cout << "\x1b[91mModos 'silencioso' y 'estadistica' o 'creditos' son INCOMPATIBLES!\n\x1b[0m" << endl;
		this->retorno = 4;
		this->isMenu = true;
	}
}

void Comparaciones::menu() {
	cout << "\x1b[96mUso:\x1b[97m " << this->nombreEjecutable << " \x1b[95m[opciones]\x1b[0m \x1b[93marchivo1 archivo2\x1b[0m\n" << endl;
	cout << "\x1b[96mEste programa compara \'\x1b[93marchivo1\x1b[96m\' y \'\x1b[93marchivo2\x1b[96m\'; linea por linea,\nmostrando las lineas donde se encuentran \x1b[91mdiferencias\x1b[96m o \x1b[92msimilitudes.\x1b[0m\n" << endl;
	cout << "\x1b[95mOpciones:\x1b[0m\n" << endl;
	cout << "\x1b[95m-h \x1b[96m: Muestra la lista de opciones del programa (esta pantalla)" << endl;
	cout << "\x1b[95m-e \x1b[96m: Modo estricto (compara todo de forma inegra) \x1b[93m(incompatible con '\x1b[95m-s\x1b[93m')" << endl;
	cout << "\x1b[95m-s \x1b[96m: Modo ordenado (ordena el contenido antes de comparar) \x1b[93m(incompatible con '\x1b[95m-e\x1b[93m')" << endl;
	cout << "\x1b[95m-i \x1b[96m: Modo insensible (ignora las diferencias entre mayusculas y minusculas)" << endl;
	cout << "\x1b[95m-t \x1b[96m: Modo estadisticas (muestra el numero de lineas y caracteres) \x1b[93m(incompatible con '\x1b[95m-q\x1b[93m')" << endl;
	cout << "\x1b[95m-q \x1b[96m: Modo silencioso (no muestra las lineas que son iguales) \x1b[93m(incompatible con '\x1b[95m-t\x1b[93m' y '\x1b[95m-c\x1b[93m') " << endl;
	cout << "\x1b[95m-c \x1b[96m: Modo creditos (muestra version de programa, compilador y autor) \x1b[93m(incompatible con '\x1b[95m-q\x1b[93m')\x1b[0m" << endl;
}

bool Comparaciones::extraerLineasDeArchivos() {
	if (!isMenu) {
		string lineaTxt1, lineaTxt2;
		ifstream archivo1(nombreArchivo1);
		ifstream archivo2(nombreArchivo2);
		if (archivo1.fail()) {
			cout << "\x1b[91mNo encuentro el archivo1 (\'" << nombreArchivo1 << "\')!" << endl;
			if (archivo2.fail())
				cout << "\x1b[91mNo encuentro el archivo2 (\'" << nombreArchivo2 << "\')!\x1b[0m" << endl;
			this->retorno = 5;
			this->isEstricto = false;
			this->isEstadistica = false;
			this->isCreditos = false;
			this->isOrdenado = false;
			this->isInsensible = false;
		} else if (archivo2.fail()) {
			cout << "\x1b[91mNo encuentro el archivo2 (\'" << nombreArchivo2 << "\')!\x1b[0m" << endl;
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
	cout << "\n\x1b[96mARGUMENTOS: \n" << endl;
	cout << "	\x1b[90m   Estricto: " << (this->isEstricto ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90m   Ordenado: " << (this->isOrdenado ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90m Insensible: " << (this->isInsensible ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mEstadistica: " << (this->isEstadistica ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90m Silencioso: " << (this->isSilencioso ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90m   Creditos: " << (this->isCreditos ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90m   Archivo1: \x1b[97m" << this->nombreArchivo1 << endl;
	cout << "	\x1b[90m   Archivo2: \x1b[97m" << this->nombreArchivo2 << endl << endl;
}

void Comparaciones::comparacion() {
	int contador = 0;
	cout << "\n\x1b[96mCOMPARACION: \x1b[0m\n" << endl;
	for (int indice = 0; indice < lineas_archivo1.size(); indice++) {
		if (lineas_archivo1[indice] == lineas_archivo2[indice]) {
			cout << "	\x1b[92m" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' == " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'\x1b[0m" << endl;
			contador++;
		} else 
			cout << "	\x1b[91m" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' != " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'\x1b[0m" << endl;
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
		cout << "	\x1b[93mArchivo1: \x1b[0m\'desorden -> orden\'" << endl;
		cout << "	\x1b[93mArchivo2: \x1b[0m\'desorden -> orden\'" << endl;
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
		cout << "	\x1b[93mArchivo1: \x1b[0m\'mayusculas -> minusculas\'" << endl;
		cout << "	\x1b[93mArchivo2: \x1b[0m\'mayusculas -> minusculas\'" << endl;
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
		cout << "\n\x1b[96mCOMPARACION: \x1b[0m\n" << endl;
		this->sonIguales = false;
		for (int indice = 0; indice < posiciones.size(); indice++) 
			cout << "	\x1b[91m" << nombreArchivo1 << ": \'" << lineas_archivo1[posiciones[indice]] << "\' != " << nombreArchivo2 << ": \'" << lineas_archivo2[posiciones[indice]] << "\'\x1b[0m" << endl;
		conclusion();
	}
}

void Comparaciones::estadisticas() {
	getNumeroLineas_Caracteres(lineas_archivo1, 0, 0);
	cout << "	\x1b[90m Archivo 1: \x1b[92m" << this->nombreArchivo1 << endl;
	cout << "	\x1b[90m    Lineas: \x1b[93m" << this->numeroLineas << endl;
	cout << "	\x1b[90mCaracteres: \x1b[95m" << this->numeroCaracteres << '\n' << endl;

	getNumeroLineas_Caracteres(lineas_archivo2, 0, 0);
	cout << "	\x1b[90m Archivo 2: \x1b[92m" << this->nombreArchivo2 << endl;
	cout << "	\x1b[90m    Lineas: \x1b[93m" << this->numeroLineas << endl;
	cout << "	\x1b[90mCaracteres: \x1b[95m" << this->numeroCaracteres << "\x1b[0m" << endl;
}

void Comparaciones::creditos() {
	cout << "\n\x1b[96mCREDITOS: \n" << endl;
	cout << "	\x1b[90m  Programa: \x1b[92m" << this->nombreEjecutable << endl;
	cout << "	\x1b[90m   Version: \x1b[93m 1.1" << endl;
	cout << "	\x1b[90m  Proyecto: \x1b[95mProgramacion III - Parte I\n" << endl;

	cout << "	\x1b[90m  Lenguaje: \x1b[92mC++" << endl;
	cout << "	\x1b[90mCompilador: \x1b[93mMicrosoft Visual Studio Community 2022 (64 - bit)" << endl;
	cout << "	\x1b[90m   Version: \x1b[95m17.13.0\n" << endl;

	cout << "	\x1b[90m     Autor: \x1b[92mDavid Castro" << endl;
	cout << "	\x1b[90m    Correo: \x1b[93mdavid_castro@unitec.edu" << endl;
	cout << "	\x1b[90m     Fecha: \x1b[95m2025-03-20\x1b[0m" << endl;
}

void Comparaciones::conclusion() {
	cout << "\n\x1b[96mCONCLUSION: \n" << endl;
	if (this->sonIguales) {
		cout << "	\x1b[92mLos archivos '" << nombreArchivo1 << "' y '" << nombreArchivo2 << "' tienen el MISMO contenido!" << "\x1b[0m" << endl;
		this->retorno = 0;
	} else {
		cout << "	\x1b[91mLos archivos '" << nombreArchivo1 << "' y '" << nombreArchivo2 << "' tienen DIFERENTE contenido!" << "\x1b[0m" << endl;
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
				cout << "\n\x1b[96mCONVERSION: \x1b[0m\n" << endl;
				insensible(lineas_archivo1);
				insensible(lineas_archivo2,2);
			}
			
			if (isOrdenado) {
				cout << "\n\x1b[96mORGANIZACION: \x1b[0m\n" << endl;
				ordenacion(lineas_archivo1);
				ordenacion(lineas_archivo2,2);
			}

			if (seExtrajo)
				comparacion();
			if (isEstadistica) {
				cout << "\n\x1b[96mESTADISTICAS: \n" << endl;
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
