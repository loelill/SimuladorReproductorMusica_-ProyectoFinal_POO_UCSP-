#pragma once
#include "Cancion.h"

class ColaReproduccion {
private:
    Cancion** canciones;
    int cantidad;
    int capacidad;
    int posicionActual;
    void redimensionar();
public:
    ColaReproduccion();
    ColaReproduccion(const ColaReproduccion& otra);
    ColaReproduccion& operator=(const ColaReproduccion& otra);
    ~ColaReproduccion();

    bool agregar(Cancion* cancion);
    bool eliminar(int indice);
    bool mover(int origen, int destino);
    bool seleccionar(int indice);
    bool siguiente();
    bool anterior();
    void vaciar();

    Cancion* obtenerActual() const;
    Cancion* obtenerEn(int indice) const;
    int getCantidad() const;
    int getPosicionActual() const;
    bool estaVacia() const;
    void mostrarCola() const;
};
