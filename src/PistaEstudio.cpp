#include "PistaEstudio.h"

PistaEstudio::PistaEstudio(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* est)
    : Cancion(tit, art, dur, anioLanzamiento, tamano) {
    int len = longitudCadena(est);
    estudio = new char[len + 1];
    copiarCadena(estudio, est);
}

PistaEstudio::PistaEstudio(const PistaEstudio& otra) : Cancion(otra) {
    int len = longitudCadena(otra.estudio);
    estudio = new char[len + 1];
    copiarCadena(estudio, otra.estudio);
}

PistaEstudio& PistaEstudio::operator=(const PistaEstudio& otra) {
    if (this != &otra) {
        Cancion::operator=(otra);
        delete[] estudio;
        int len = longitudCadena(otra.estudio);
        estudio = new char[len + 1];
        copiarCadena(estudio, otra.estudio);
    }
    return *this;
}

PistaEstudio::~PistaEstudio() {
    delete[] estudio;
}

void PistaEstudio::reproducir() {
    cout << "[ESTUDIO] Reproduciendo: " << *this << endl;
}

void PistaEstudio::mostrarFichaTecnica() const {
    cout << "------ ESTUDIO ------" << endl;
    cout << "Titulo   : " << titulo << endl;
    cout << "Artista  : " << artista << endl;
    cout << "Anio     : " << anio << endl;
    cout << "Duracion : " << duracion << " s" << endl;
    cout << "Tamano   : " << tamanoBytes << " bytes" << endl;
    cout << "Estudio  : " << estudio << endl;
}

Cancion* PistaEstudio::clonar() const {
    return new PistaEstudio(*this);
}

const char* PistaEstudio::getEstudio() const {
    return estudio;
}