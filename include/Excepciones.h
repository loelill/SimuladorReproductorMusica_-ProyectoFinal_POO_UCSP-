#pragma once
#include "Cancion.h"

class ExcepcionReproductor {
protected:
    char* mensaje;

public:
    ExcepcionReproductor(const char* msg) {
        int len = Cancion::longitudCadena(msg);
        mensaje = new char[len + 1];
        Cancion::copiarCadena(mensaje, msg);
    }

    ExcepcionReproductor(const ExcepcionReproductor& otra) {
        int len = Cancion::longitudCadena(otra.mensaje);
        mensaje = new char[len + 1];
        Cancion::copiarCadena(mensaje, otra.mensaje);
    }

    ExcepcionReproductor& operator=(const ExcepcionReproductor& otra) {
        if (this != &otra) {
            delete[] mensaje;
            int len = Cancion::longitudCadena(otra.mensaje);
            mensaje = new char[len + 1];
            Cancion::copiarCadena(mensaje, otra.mensaje);
        }
        return *this;
    }

    virtual ~ExcepcionReproductor() {
        delete[] mensaje;
    }

    const char* obtenerMensaje() const {
        return mensaje;
    }
};

class ExcepcionArchivoInvalido : public ExcepcionReproductor {
public:
    ExcepcionArchivoInvalido(const char* msg) : ExcepcionReproductor(msg) {}
};

class ExcepcionMemoriaVacia : public ExcepcionReproductor {
public:
    ExcepcionMemoriaVacia(const char* msg) : ExcepcionReproductor(msg) {}
};