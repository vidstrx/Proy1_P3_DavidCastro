#include "Comparaciones.h"
// \x1b[96m = Cyan claro
// \x1b[0m = color normal de terminal
// \x1b[95m = Morado claro
// \x1b[93m = Amarillo claro
// \x1b[91m = Rojo claro
// \x1b[92m = Verde claro
// \x1b[90m = Negro claro

Comparaciones::Comparaciones(int argc, char* argv[]) {
	// empieza en 1 para no tomar en cuenta la direccion del proyecto
	// y agarrar solo los comandos despues de la direccion
	for (int indice = 1; indice < argc; indice++) {
		parametros.push_back(argv[indice]);
		cout << parametros[indice-1] << endl; // se resta 1 para que empiece en la posicion 0 ya que ahi es donde se guarda el primer comando
	}

	// sacar el nombre del ejecutable
	string ruta = argv[0];
	string temporal; 
	// ciclo for para sacar el nombre del ejecutable desde el final de la ruta hasta que encuentre el primer '\'
	for (size_t indice = ruta.size(); indice > 0; indice--) {
		char letra = ruta[indice];
		if (letra == '\\') {
			break;
		}
		temporal += letra; // guardar el nombre del ejecutable al reves temporalmente
	}
	// luego este ciclo for agrega las letras del nombre del ejecutable de forma correcta
	for (size_t indice = temporal.size(); indice > 0; indice--) {
		char letra = temporal[indice];
		this->nombreEjecutable += letra;
	}
}

void Comparaciones::buscarArchivos() {
	for (int indice = 0; indice < parametros.size(); indice++) {
		if (parametros[indice] == "-e")
			this->isEstricto = true;
		else if (parametros[indice] == "-s")
			this->isOrdenado = true;
		else if (parametros[indice] == "-i")
			this->isInsensible = true;
		else if (parametros[indice] == "-t")
			this->isEstadistica = true;
		else if (parametros[indice] == "-q")
			this->isSilencioso = true;
		else if (parametros[indice] == "-c")
			this->isCreditos = true;
		else if (parametros[indice] == "-h"){
			this->isMenu = true;
			break;
		} else {
			if (contador == 1) {
				this->nombreArchivo1 = parametros[indice];
				this->contador++;
			} else if (contador == 2) {
				this->nombreArchivo2 = parametros[indice];
				this->contador++;
			} else {
				this->isMenu = true;
				break;
			}
		}
	}
}

int Comparaciones::menu() {
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
	return 0;
}

bool Comparaciones::extraerLineasDeArchivos() {
	buscarArchivos();
	if (!isMenu) {
		string lineaTxt1, lineaTxt2;
		ifstream archivo1(nombreArchivo1);
		ifstream archivo2(nombreArchivo2);
		if (archivo1.fail()) {
			argumentos();
			cout << "\x1b[91mNo encuentro el archivo1 (\'" << nombreArchivo1 << "\')!" << endl;
			if (archivo2.fail())
				cout << "\x1b[91mNo encuentro el archivo2 (\'" << nombreArchivo2 << "\')!\x1b[0m" << endl;
		} else if (archivo2.fail()) {
			argumentos();
			cout << "\x1b[91mNo encuentro el archivo2 (\'" << nombreArchivo2 << "\')!\x1b[0m" << endl;
		} else {
			argumentos();
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

void Comparaciones::compararArchivos() {
	if (extraerLineasDeArchivos()) {
		cout << "\n\x1b[96mCOMPARACION: \x1b[0m\n" << endl;
		for (int indice = 0; indice < lineas_archivo1.size(); indice++) {
			if (lineas_archivo1[indice] == lineas_archivo2[indice])
				cout << "	\x1b[92m" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' == " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'\x1b[0m" << endl;
			else
				cout << "	\x1b[91m" << nombreArchivo1 << ": \'" << lineas_archivo1[indice] << "\' != " << nombreArchivo2 << ": \'" << lineas_archivo2[indice] << "\'\x1b[0m" << endl;
		}
		cout << endl;
		// usar for para ambos archivos y comparar con los indices si son iguales o no las cadenas
	}
}

int Comparaciones::ejecucionPrograma() {
	compararArchivos();
	//creditos();
	return 0;
}

void Comparaciones::argumentos() {
	cout << "\n\x1b[96mARGUMENTOS: \n" << endl;
	cout << "	\x1b[90mEstricto: " << (this->isEstricto ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mOrdenado: " << (this->isOrdenado ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mInsensible: " << (this->isInsensible ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mEstadistica: " << (this->isEstadistica ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mSilencioso: " << (this->isSilencioso ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mCreditos: " << (this->isCreditos ? "\x1b[92mSI" : "\x1b[95mNO") << endl;
	cout << "	\x1b[90mArchivo1: \x1b[0m" << this->nombreArchivo1 << endl;
	cout << "	\x1b[90mArchivo2: \x1b[0m" << this->nombreArchivo2 << endl;
}

void Comparaciones::creditos() {
	cout << "\n\x1b[96mCREDITOS: \n" << endl;
	cout << "	\x1b[90mPrograma: \x1b[92m" << nombreEjecutable << endl;
	cout << "	\x1b[90mVersion: \x1b[93m 1.1" << endl;
	cout << "	\x1b[90mProyecto: \x1b[95mProgramacion III - Parte I\n" << endl;

	cout << "	\x1b[90mLenguaje: \x1b[92mC++" << endl;
	cout << "	\x1b[90mCompilador: \x1b[93mMicrosoft Visual Studio Community 2022 (64 - bit)" << endl;
	cout << "	\x1b[90mVersion: \x1b[95m17.13.0\n" << endl;

	cout << "	\x1b[90mAutor: \x1b[92mDavid Castro" << endl;
	cout << "	\x1b[90mCorreo: \x1b[93mdavid_castro@unitec.edu" << endl;
	cout << "	\x1b[90mFecha: \x1b[95m2025-03-20\x1b[0m" << endl;
}

Comparaciones::~Comparaciones() {

}
