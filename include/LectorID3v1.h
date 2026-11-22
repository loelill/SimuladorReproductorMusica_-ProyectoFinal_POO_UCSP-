#pragma once
#include "LectorAudio.h"

class LectorID3v1 : public LectorAudio {
private:
    void copiarCampo(char* destino, int capacidad, const char* origen, int longitud) const;
    int convertirAnio(const char* origen) const;
public:
    bool leer(const char* ruta, DatosAudio& datos) const override;
};
