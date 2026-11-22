#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class PistaEstudio : public Cancion {
    private:

        char* estudio;

    public:

        PistaEstudio(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* est);
        PistaEstudio(const PistaEstudio& otra);
        PistaEstudio& operator=(const PistaEstudio& otra);
        ~PistaEstudio();

        void reproducir() override;
        void mostrarFichaTecnica() const override;
        Cancion* clonar() const override;

        const char* getEstudio() const;
};
