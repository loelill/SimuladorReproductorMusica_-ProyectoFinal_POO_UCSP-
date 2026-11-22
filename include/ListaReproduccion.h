#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class ListaReproduccion {
    private:

        char* nombre;
        Cancion** canciones;
        int cantidadCanciones;
        int capacidad;
        void redimensionar();

    public:

        ListaReproduccion(const char* nom);
        ListaReproduccion(const ListaReproduccion& otra);
        ListaReproduccion& operator=(const ListaReproduccion& otra);
        ~ListaReproduccion();
        void agregarCancion(Cancion* cancion);
        void mostrarLista() const;
        const char* getNombre() const;
        int getCantidadCanciones() const;
        Cancion* getCancion(int indice) const;
};
