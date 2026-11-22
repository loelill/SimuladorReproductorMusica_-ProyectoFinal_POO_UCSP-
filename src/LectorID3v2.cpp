#include "LectorID3v2.h"
#include <fstream>
#include <climits>
using namespace std;

bool LectorID3v2::leerNumero(const char* bytes, int base, unsigned long& numero) const {
    numero = 0;
    const char* p = bytes;
    for (int i = 0; i < 4; i++) {
        unsigned char valor = static_cast<unsigned char>(*p);
        if (valor >= base) return false;
        numero = numero * base + valor;
        p++;
    }
    return true;
}

bool LectorID3v2::esIdentificador(const char* texto) const {
    const char* p = texto;
    for (int i = 0; i < 4; i++) {
        bool letra = (*p >= 'A' && *p <= 'Z');
        bool numero = (*p >= '0' && *p <= '9');
        if (!letra && !numero) return false;
        p++;
    }
    return true;
}

bool LectorID3v2::esCampo(const char* texto, const char* nombre) const {
    for (int i = 0; i < 4; i++) {
        if (*(texto + i) != *(nombre + i)) return false;
    }
    return true;
}

void LectorID3v2::copiarTexto(char* destino, int capacidad, const char* origen, unsigned long longitud) const {
    if (capacidad <= 0) return;
    *destino = '\0';
    if (longitud < 2) return;

    unsigned char codificacion = static_cast<unsigned char>(*origen);
    const char* entrada = origen + 1;
    const char* fin = origen + longitud;
    char* salida = destino;
    char* limiteSalida = destino + capacidad - 1;

    if (codificacion == 0 || codificacion == 3) {
        while (entrada < fin && *entrada != '\0') {
            unsigned char letra = static_cast<unsigned char>(*entrada);
            if (codificacion == 0 && letra >= 128) {
                if (limiteSalida - salida < 2) break;
                *salida++ = static_cast<char>(192 + letra / 64);
                *salida++ = static_cast<char>(128 + letra % 64);
            } else {
                if (salida >= limiteSalida) break;
                *salida++ = *entrada;
            }
            entrada++;
        }
    } else if (codificacion == 1 || codificacion == 2) {
        bool littleEndian = false;
        if (codificacion == 1) {
            if (fin - entrada < 2) return;
            unsigned char primero = static_cast<unsigned char>(*entrada);
            unsigned char segundo = static_cast<unsigned char>(*(entrada + 1));
            if (primero == 255 && segundo == 254) littleEndian = true;
            else if (primero != 254 || segundo != 255) return;
            entrada += 2;
        }

        while (fin - entrada >= 2) {
            unsigned char a = static_cast<unsigned char>(*entrada++);
            unsigned char b = static_cast<unsigned char>(*entrada++);
            int letra = littleEndian ? b * 256 + a : a * 256 + b;
            if (letra == 0) break;
            if (letra < 128) {
                if (salida >= limiteSalida) break;
                *salida++ = static_cast<char>(letra);
            } else if (letra <= 255) {
                if (limiteSalida - salida < 2) break;
                *salida++ = static_cast<char>(192 + letra / 64);
                *salida++ = static_cast<char>(128 + letra % 64);
            } else {
                if (salida >= limiteSalida) break;
                *salida++ = '?';
            }
        }
    }
    while (salida > destino && *(salida - 1) == ' ') salida--;
    *salida = '\0';
}

int LectorID3v2::convertirAnio(const char* texto) const {
    int anio = 0;
    const char* p = texto;
    for (int i = 0; i < 4; i++) {
        if (*p < '0' || *p > '9') return 0;
        anio = anio * 10 + (*p - '0');
        p++;
    }
    return anio;
}

double LectorID3v2::convertirDuracion(const char* texto) const {
    double ms = 0;
    const char* p = texto;
    if (*p == '\0') return 0;
    while (*p != '\0') {
        if (*p < '0' || *p > '9') return 0;
        ms = ms * 10 + (*p - '0');
        if (ms > 360000000) return 0;
        p++;
    }
    return ms / 1000.0;
}

bool LectorID3v2::leer(const char* ruta, DatosAudio& datos) const {
    if (ruta == nullptr || *ruta == '\0') return false;
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) return false;

    archivo.seekg(0, ios::end);
    streamoff total = archivo.tellg();
    if (total < 10 || total > LONG_MAX) return false;
    long tamanoArchivo = static_cast<long>(total);
    archivo.seekg(0, ios::beg);

    char cabecera[10];
    archivo.read(cabecera, 10);
    if (!archivo) return false;
    if (*cabecera != 'I' || *(cabecera + 1) != 'D' || *(cabecera + 2) != '3') return false;

    unsigned char version = static_cast<unsigned char>(*(cabecera + 3));
    if (version != 3 && version != 4) return false;

    unsigned char opciones = static_cast<unsigned char>(*(cabecera + 5));
    if ((opciones & 128) != 0 || (opciones & 64) != 0) return false;

    unsigned long tamanoEtiqueta = 0;
    if (!leerNumero(cabecera + 6, 128, tamanoEtiqueta)) return false;
    if (tamanoEtiqueta == 0 || tamanoEtiqueta > 4UL * 1024 * 1024) return false;
    unsigned long disponibles = static_cast<unsigned long>(tamanoArchivo - 10);
    if (tamanoEtiqueta > disponibles) return false;
    char* etiqueta = new char[tamanoEtiqueta];
    archivo.read(etiqueta, tamanoEtiqueta);
    if (!archivo) {
        delete[] etiqueta;
        return false;
    }

    DatosAudio temporal;
    temporal.tamanoBytes = tamanoArchivo;
    bool encontrado = false;
    const char* campo = etiqueta;
    const char* finEtiqueta = etiqueta + tamanoEtiqueta;
  
    while (finEtiqueta - campo >= 10) {
        if (!esIdentificador(campo)) break;
        unsigned long longitud = 0;
        int base = (version == 3) ? 256 : 128;
        if (!leerNumero(campo + 4, base, longitud)) break;
        unsigned long espacio = static_cast<unsigned long>(finEtiqueta - campo - 10);
        if (longitud == 0 || longitud > espacio) break;

        bool titulo = esCampo(campo, "TIT2");
        bool artista = esCampo(campo, "TPE1");
        bool album = esCampo(campo, "TALB");
        bool anio = esCampo(campo, "TYER") || esCampo(campo, "TDRC");
        bool duracion = esCampo(campo, "TLEN");

        if (*(campo + 9) == 0 && (titulo || artista || album || anio || duracion)) {
            char texto[128];
            copiarTexto(texto, 128, campo + 10, longitud);
            if (*texto != '\0') {
                if (titulo) copiarTexto(temporal.titulo, 128, campo + 10, longitud);
                if (artista) copiarTexto(temporal.artista, 128, campo + 10, longitud);
                if (album) copiarTexto(temporal.album, 128, campo + 10, longitud);
                if (anio) temporal.anio = convertirAnio(texto);
                if (duracion) temporal.duracion = convertirDuracion(texto);
                encontrado = true;
            }
        }
        campo += 10 + longitud;
    }

    delete[] etiqueta;
    if (!encontrado) return false;
    datos = temporal;
    return true;
}
