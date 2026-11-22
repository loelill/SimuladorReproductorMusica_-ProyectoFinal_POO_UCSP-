#include "Album.h"

Album::Album(const char* tit, const char* art, int anio)
    : anioLanzamiento(anio), cantidadPistas(0), capacidad(4) {
    
    int lenTit = Cancion::longitudCadena(tit);
    titulo = new char[lenTit + 1];
    Cancion::copiarCadena(titulo, tit);

    int lenArt = Cancion::longitudCadena(art);
    nombreArtista = new char[lenArt + 1];
    Cancion::copiarCadena(nombreArtista, art);

    pistas = new Cancion*[capacidad];
}

Album::Album(const Album& otro)
    : anioLanzamiento(otro.anioLanzamiento), cantidadPistas(otro.cantidadPistas), capacidad(otro.capacidad) {
    
    int lenTit = Cancion::longitudCadena(otro.titulo);
    titulo = new char[lenTit + 1];
    Cancion::copiarCadena(titulo, otro.titulo);

    int lenArt = Cancion::longitudCadena(otro.nombreArtista);
    nombreArtista = new char[lenArt + 1];
    Cancion::copiarCadena(nombreArtista, otro.nombreArtista);

    pistas = new Cancion*[capacidad];
    for (int i = 0; i < cantidadPistas; i++) {
        *(pistas + i) = (*(otro.pistas + i))->clonar();
    }
}

Album& Album::operator=(const Album& otro) {
    if (this != &otro) {
        for (int i = 0; i < cantidadPistas; i++) {
            delete *(pistas + i);
        }
        delete[] pistas;
        delete[] titulo;
        delete[] nombreArtista;

        anioLanzamiento = otro.anioLanzamiento;
        cantidadPistas = otro.cantidadPistas;
        capacidad = otro.capacidad;

        int lenTit = Cancion::longitudCadena(otro.titulo);
        titulo = new char[lenTit + 1];
        Cancion::copiarCadena(titulo, otro.titulo);

        int lenArt = Cancion::longitudCadena(otro.nombreArtista);
        nombreArtista = new char[lenArt + 1];
        Cancion::copiarCadena(nombreArtista, otro.nombreArtista);

        pistas = new Cancion*[capacidad];
        for (int i = 0; i < cantidadPistas; i++) {
            *(pistas + i) = (*(otro.pistas + i))->clonar();
        }
    }
    return *this;
}

Album::~Album() {
    for (int i = 0; i < cantidadPistas; i++) {
        delete *(pistas + i);
    }
    delete[] pistas;
    delete[] titulo;
    delete[] nombreArtista;
}

void Album::redimensionar() {
    capacidad *= 2;
    Cancion** nuevoArreglo = new Cancion*[capacidad];
    for (int i = 0; i < cantidadPistas; i++) {
        *(nuevoArreglo + i) = *(pistas + i);
    }
    delete[] pistas;
    pistas = nuevoArreglo;
}

void Album::agregarPista(Cancion* pista) {
    if (pista == nullptr) return;
    if (cantidadPistas == capacidad) {
        redimensionar();
    }
    *(pistas + cantidadPistas) = pista;
    cantidadPistas++;
}

void Album::mostrarAlbum() const {
    cout << "==========================================" << endl;
    cout << "ALBUM: " << titulo << " (" << anioLanzamiento << ")" << endl;
    cout << "Artista: " << nombreArtista << " | Pistas: " << cantidadPistas << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < cantidadPistas; i++) {
        cout << " [" << (i + 1) << "] " << *(*(pistas + i)) << endl;
    }
    cout << "Duracion total: " << calcularDuracionTotal() << "s" << endl;
    cout << "==========================================" << endl;
}

double Album::calcularDuracionTotal() const {
    double total = 0.0;
    for (int i = 0; i < cantidadPistas; i++) {
        total += (*(pistas + i))->getDuracion();
    }
    return total;
}

const char* Album::getTitulo() const {
    return titulo;
}

int Album::getCantidadPistas() const {
    return cantidadPistas;
}

Cancion* Album::getPista(int indice) const {
    if (indice < 0 || indice >= cantidadPistas) return nullptr;
    return *(pistas + indice);
}