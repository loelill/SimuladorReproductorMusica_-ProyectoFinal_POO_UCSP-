#include "Cancion.h"

int Cancion::contadorGlobal = 0;

int Cancion::longitudCadena(const char* cad) {
    if (cad == nullptr) return 0;
    int len = 0;
    while (*(cad + len) != '\0') {
        len++;
    }
    return len;
}

void Cancion::copiarCadena(char* destino, const char* origen) {
    if (destino == nullptr) return;
    if (origen == nullptr) {
        *destino = '\0';
        return;
    }
    int i = 0;
    while (*(origen + i) != '\0') {
        *(destino + i) = *(origen + i);
        i++;
    }
    *(destino + i) = '\0';
}

int Cancion::compararCadenas(const char* cad1, const char* cad2) {
    if (cad1 == nullptr && cad2 == nullptr) return 0;
    if (cad1 == nullptr) return -1;
    if (cad2 == nullptr) return 1;

    int i = 0;
    while (*(cad1 + i) != '\0' && *(cad2 + i) != '\0') {
        if (*(cad1 + i) != *(cad2 + i)) {
            return *(cad1 + i) - *(cad2 + i);
        }
        i++;
    }
    return *(cad1 + i) - *(cad2 + i);
}

Cancion::Cancion(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano)
    : duracion(dur), anio(anioLanzamiento), tamanoBytes(tamano) {
    contadorGlobal++;
    idAgregacion = contadorGlobal;
    
    int lenTit = longitudCadena(tit);
    titulo = new char[lenTit + 1];
    copiarCadena(titulo, tit);

    int lenArt = longitudCadena(art);
    artista = new char[lenArt + 1];
    copiarCadena(artista, art);
}

Cancion::Cancion(const Cancion& otra)
    : duracion(otra.duracion), anio(otra.anio), tamanoBytes(otra.tamanoBytes), idAgregacion(otra.idAgregacion) {
    
    int lenTit = longitudCadena(otra.titulo);
    titulo = new char[lenTit + 1];
    copiarCadena(titulo, otra.titulo);

    int lenArt = longitudCadena(otra.artista);
    artista = new char[lenArt + 1];
    copiarCadena(artista, otra.artista);
}

Cancion& Cancion::operator=(const Cancion& otra) {
    if (this != &otra) {
        delete[] titulo;
        delete[] artista;

        duracion = otra.duracion;
        anio = otra.anio;
        tamanoBytes = otra.tamanoBytes;
        idAgregacion = otra.idAgregacion;

        int lenTit = longitudCadena(otra.titulo);
        titulo = new char[lenTit + 1];
        copiarCadena(titulo, otra.titulo);

        int lenArt = longitudCadena(otra.artista);
        artista = new char[lenArt + 1];
        copiarCadena(artista, otra.artista);
    }
    return *this;
}

Cancion::~Cancion() {
    delete[] titulo;
    delete[] artista;
}

const char* Cancion::getTitulo() const { return titulo; }
const char* Cancion::getArtista() const { return artista; }
double Cancion::getDuracion() const { return duracion; }
int Cancion::getAnio() const { return anio; }
long Cancion::getTamanoBytes() const { return tamanoBytes; }
int Cancion::getIdAgregacion() const { return idAgregacion; }

bool Cancion::operator<(const Cancion& otra) const {
    return compararCadenas(this->titulo, otra.titulo) < 0;
}

bool Cancion::operator==(const Cancion& otra) const {
    return compararCadenas(this->titulo, otra.titulo) == 0 &&
           compararCadenas(this->artista, otra.artista) == 0;
}

ostream& operator<<(ostream& os, const Cancion& c) {
    os << "[#" << c.idAgregacion << "] \"" << c.titulo << "\" - " << c.artista 
       << " (" << c.duracion << "s | " << c.anio << ")";
    return os;
}