#pragma once
#include "Cancion.h"
#include <iostream>

using namespace std;

class PistaEnVivo : public Cancion {
    private:

        char* lugar;

    public:

        PistaEnVivo(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* lug);
        PistaEnVivo(const PistaEnVivo& otra);
        PistaEnVivo& operator=(const PistaEnVivo& otra);
        ~PistaEnVivo();

        void reproducir() override;
        void mostrarFichaTecnica() const override;
        Cancion* clonar() const override;

        const char* getLugar() const;
};
