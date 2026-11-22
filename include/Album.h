#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class Album {
private:
    char* titulo;
    char* nombreArtista;
    int anioLanzamiento;
    Cancion** pistas;
    int cantidadPistas;
    int capacidad;

    void redimensionar();

public:
    Album(const char* tit, const char* art, int anio);
    Album(const Album& otro);
    Album& operator=(const Album& otro);
    ~Album();

    void agregarPista(Cancion* pista);
    void mostrarAlbum() const;
    double calcularDuracionTotal() const;

    const char* getTitulo() const;
    int getCantidadPistas() const;
    Cancion* getPista(int indice) const;
};