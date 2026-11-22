#include "../include/GestorPersistencia.h"

GestorPersistencia::GestorPersistencia(const char* rutaBib, const char* rutaLog) {
    int lenBib = Cancion::longitudCadena(rutaBib);
    rutaBiblioteca = new char[lenBib + 1];
    Cancion::copiarCadena(rutaBiblioteca, rutaBib);

    int lenLog = Cancion::longitudCadena(rutaLog);
    rutaLogBenchmark = new char[lenLog + 1];
    Cancion::copiarCadena(rutaLogBenchmark, rutaLog);
}

GestorPersistencia::GestorPersistencia(const GestorPersistencia& otro) {
    int lenBib = Cancion::longitudCadena(otro.rutaBiblioteca);
    rutaBiblioteca = new char[lenBib + 1];
    Cancion::copiarCadena(rutaBiblioteca, otro.rutaBiblioteca);

    int lenLog = Cancion::longitudCadena(otro.rutaLogBenchmark);
    rutaLogBenchmark = new char[lenLog + 1];
    Cancion::copiarCadena(rutaLogBenchmark, otro.rutaLogBenchmark);
}

GestorPersistencia& GestorPersistencia::operator=(const GestorPersistencia& otro) {
    if (this != &otro) {
        delete[] rutaBiblioteca;
        delete[] rutaLogBenchmark;

        int lenBib = Cancion::longitudCadena(otro.rutaBiblioteca);
        rutaBiblioteca = new char[lenBib + 1];
        Cancion::copiarCadena(rutaBiblioteca, otro.rutaBiblioteca);

        int lenLog = Cancion::longitudCadena(otro.rutaLogBenchmark);
        rutaLogBenchmark = new char[lenLog + 1];
        Cancion::copiarCadena(rutaLogBenchmark, otro.rutaLogBenchmark);
    }
    return *this;
}

GestorPersistencia::~GestorPersistencia() {
    delete[] rutaBiblioteca;
    delete[] rutaLogBenchmark;
}

bool GestorPersistencia::guardarBiblioteca(Cancion** lista, int cantidad) const {
    if (lista == nullptr || cantidad < 0) return false;

    ofstream archivo(rutaBiblioteca);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << cantidad << "\n";
    for (int i = 0; i < cantidad; i++) {
        Cancion* c = *(lista + i);
        if (c != nullptr) {
            archivo << c->getTitulo() << "|"
                    << c->getArtista() << "|"
                    << c->getDuracion() << "|"
                    << c->getAnio() << "|"
                    << c->getTamanoBytes() << "\n";
        }
    }

    archivo.close();
    return true;
}

bool GestorPersistencia::registrarBenchmark(const char* algoritmo, int cantidadElementos, double tiempoMs) const {
    ofstream archivo(rutaLogBenchmark, ios::app);
    if (!archivo.is_open()) {
        return false;
    }

    archivo << "Algoritmo: " << algoritmo
            << " | Elementos: " << cantidadElementos
            << " | Tiempo: " << tiempoMs << " ms\n";

    archivo.close();
    return true;
}

void GestorPersistencia::mostrarLogBenchmark() const {
    ifstream archivo(rutaLogBenchmark);
    if (!archivo.is_open()) {
        cout << "No se encontro registro de benchmark en: " << rutaLogBenchmark << endl;
        return;
    }

    cout << "=== HISTORIAL DE BENCHMARK ===" << endl;
    char buffer[256];
    while (archivo.getline(buffer, 256)) {
        cout << buffer << endl;
    }
    cout << "==============================" << endl;

    archivo.close();
}

const char* GestorPersistencia::getRutaBiblioteca() const {
    return rutaBiblioteca;
}

const char* GestorPersistencia::getRutaLogBenchmark() const {
    return rutaLogBenchmark;
}