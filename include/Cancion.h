#pragma once 
#include <iostream>

using namespace std;

class Cancion {
protected:
    char* titulo;
    char* artista;
    double duracion;
    int anio;
    long tamanoBytes;
    int idAgregacion;
    static int contadorGlobal;

public:
    static int longitudCadena(const char* cad);
    static void copiarCadena(char* destino, const char* origen);
    static int compararCadenas(const char* cadena1, const char* cadena2);

    Cancion(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano);
    Cancion(const Cancion& otra);
    Cancion& operator=(const Cancion& otra);
    virtual ~Cancion();

    virtual void reproducir() = 0;
    virtual void mostrarFichaTecnica() const = 0;
    virtual Cancion* clonar() const = 0;

    const char* getTitulo() const;
    const char* getArtista() const;
    double getDuracion() const;
    int getAnio() const;
    long getTamanoBytes() const;
    int getIdAgregacion() const;

    bool operator<(const Cancion& otra) const;
    bool operator==(const Cancion& otra) const;
    friend ostream& operator<<(ostream& os, const Cancion& cancion);
};