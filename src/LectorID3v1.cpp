#include "LectorID3v1.h"
#include <fstream>
#include <climits>
using namespace std;

void LectorID3v1::copiarCampo(char* destino, int capacidad, const char* origen, int longitud) const {
    if (capacidad <= 0 || longitud < 0) return;
    const char* fin = origen + longitud;
    while (fin > origen && (*(fin - 1) == ' ' || *(fin - 1) == '\0')) {
        fin--;
    }
    char* salida = destino;
    const char* entrada = origen;
    while (entrada < fin && salida < destino + capacidad - 1) {
        *salida = *entrada;
        salida++;
        entrada++;
    }
    *salida = '\0';
}

int LectorID3v1::convertirAnio(const char* origen) const {
    int anio = 0;
    const char* p = origen;
    for (int i = 0; i < 4; i++) {
        if (*p < '0' || *p > '9') return 0;
        anio = anio * 10 + (*p - '0');
        p++;
    }
    return anio;
}

bool LectorID3v1::leer(const char* ruta, DatosAudio& datos) const {
    if (ruta == nullptr || *ruta == '\0') return false;

    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) return false;

    archivo.seekg(0, ios::end);
    streamoff total = archivo.tellg();
    if (total < 128 || total > LONG_MAX) return false;
    long tamano = static_cast<long>(total);

    archivo.seekg(-128, ios::end);
    char buffer[128];
    archivo.read(buffer, 128);
    if (!archivo) return false;

    if (*buffer != 'T' || *(buffer + 1) != 'A' || *(buffer + 2) != 'G') return false;

    DatosAudio temporal;
    copiarCampo(temporal.titulo, 128, buffer + 3, 30);
    copiarCampo(temporal.artista, 128, buffer + 33, 30);
    copiarCampo(temporal.album, 128, buffer + 63, 30);
    temporal.anio = convertirAnio(buffer + 93);
    temporal.tamanoBytes = tamano;

    datos = temporal;
    return true;
}
