#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class Artista {
    private:
        char* nombre;
        char* paisOrigen;
        Cancion** obras;
        int cantidadObras;
        int capacidad;

        void redimensionar();

    public:
        Artista(const char* nom, const char* pais);
        Artista(const Artista& otro);
        Artista& operator=(const Artista& otro);
        ~Artista();

        void agregarObra(Cancion* cancion);
        void mostrarDiscografia()const;

        const char* getNombre()const;
        const char* getPaisOrigen()const;
        int getCantidadObras()const;
};
