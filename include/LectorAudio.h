#pragma once
struct DatosAudio {
    char titulo[128];
    char artista[128];
    char album[128];
    int anio;
    double duracion;
    long tamanoBytes;

    DatosAudio() {
        for (int i = 0; i < 128; i++) {
            *(titulo + i) = '\0';
            *(artista + i) = '\0';
            *(album + i) = '\0';
        }
        anio = 0;
        duracion = 0;
        tamanoBytes = 0;
    }
};

class LectorAudio {
public:
    virtual bool leer(const char* ruta, DatosAudio& datos) const = 0;
    virtual ~LectorAudio() {}
};
