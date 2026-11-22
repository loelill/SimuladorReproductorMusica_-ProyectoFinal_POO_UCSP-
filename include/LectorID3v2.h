#pragma once
#include "LectorAudio.h"

class LectorID3v2 : public LectorAudio {
private:
    bool leerNumero(const char* bytes, int base, unsigned long& numero) const;
    bool esIdentificador(const char* texto) const;
    bool esCampo(const char* texto, const char* nombre) const;
    void copiarTexto(char* destino, int capacidad, const char* origen, unsigned long longitud) const;
    int convertirAnio(const char* texto) const;
    double convertirDuracion(const char* texto) const;
public:
    bool leer(const char* ruta, DatosAudio& datos) const override;
};
