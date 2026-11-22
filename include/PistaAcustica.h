#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class PistaAcustica : public Cancion {
    private:

        char* instrumento;

    public:

        PistaAcustica(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* inst);
        PistaAcustica(const PistaAcustica& otra);
        PistaAcustica& operator=(const PistaAcustica& otra);
        ~PistaAcustica();

        void reproducir() override;
        void mostrarFichaTecnica() const override;
        Cancion* clonar() const override;

        const char* getInstrumento() const;
};
