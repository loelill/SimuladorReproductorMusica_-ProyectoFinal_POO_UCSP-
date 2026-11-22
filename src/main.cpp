#include "Cancion.h"
#include "PistaEstudio.h"
#include "PistaAcustica.h"
#include "PistaEnVivo.h"
#include "Album.h"
#include "Artista.h"
#include "ListaReproduccion.h"
#include "ColaReproduccion.h"
#include "LectorID3v1.h"
#include "LectorID3v2.h"
#include "MotorOrdenamiento.h"
#include "GestorPersistencia.h"
#include "Excepciones.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void redimensionarCatalogo(Cancion**& catalogo, int& capacidad, int cantidad) {
    capacidad *= 2;
    Cancion** nuevo = new Cancion*[capacidad];
    for (int i = 0; i < cantidad; i++) {
        *(nuevo + i) = *(catalogo + i);
    }
    delete[] catalogo;
    catalogo = nuevo;
}

void mostrarCatalogo(Cancion** catalogo, int cantidad) {
    cout << "\n=== BIBLIOTECA GENERAL (" << cantidad << " pistas) ===" << endl;
    if (cantidad == 0) {
        cout << "La biblioteca esta vacia." << endl;
        return;
    }
    for (int i = 0; i < cantidad; i++) {
        cout << " [" << (i + 1) << "] " << *(*(catalogo + i)) << endl;
    }
}

int main() {
    int capacidad = 10;
    int totalCanciones = 0;
    Cancion** biblioteca = new Cancion*[capacidad];

    ColaReproduccion cola;
    ListaReproduccion playlist("Favoritas del Grupo");
    Album albumDemo("Coleccion Principal", "Varios Artistas", 2026);
    Artista artistaDemo("Artistas Varios", "Internacional");
    GestorPersistencia persistencia("data/biblioteca.txt", "data/benchmark.txt");

    LectorID3v2 lectorV2;
    LectorID3v1 lectorV1;

    int opcion = -1;
    while (opcion != 0) {
        cout << "\n==============================================" << endl;
        cout << "  SIMULADOR DE REPRODUCTOR DE MUSICA - POO C++" << endl;
        cout << "==============================================" << endl;
        cout << " 1. Cargar cancion desde archivo MP3 real (ID3 / Lotes)" << endl;
        cout << " 2. Registrar cancion manualmente" << endl;
        cout << " 3. Mostrar biblioteca general y ficha tecnica" << endl;
        cout << " 4. Gestionar Cola de Reproduccion" << endl;
        cout << " 5. Ver Playlist, Album y Artista" << endl;
        cout << " 6. Ordenar biblioteca (Alfabetico / Tiempo / Fecha / Agregacion)" << endl;
        cout << " 7. Guardar biblioteca e historial en disco" << endl;
        cout << " 0. Salir y liberar memoria" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        try {
            if (opcion == 1) {
                cout << "\nSeleccione lote de carga:" << endl;
                cout << " 1. Archivo individual (ruta manual)" << endl;
                cout << " 2. Pack 10 canciones " << endl;
                cout << " 3. Pack 20 canciones " << endl;
                cout << " 4. Pack 30 canciones " << endl;
                cout << " 5. Pack 50 canciones " << endl;
                cout << "Opcion: ";
                int modo = 2;
                cin >> modo;
                limpiarBuffer();

                const char* bases[10] = {
                    "counting_stars.mp3",
                    "eternity.mp3",
                    "firework.mp3",
                    "gone_gone_gone.mp3",
                    "happier.mp3",
                    "payphone.mp3",
                    "shut_up_and_dance.mp3",
                    "soldier_poet_king.mp3",
                    "the_water_is_fine.mp3",
                    "touch.mp3"
                };

                int cantidadAProcesar = 1;
                if (modo == 2) cantidadAProcesar = 10;
                else if (modo == 3) cantidadAProcesar = 20;
                else if (modo == 4) cantidadAProcesar = 30;
                else if (modo == 5) cantidadAProcesar = 50;

                if (modo >= 2 && modo <= 5 && totalCanciones > 0) {
                    cola.vaciar();
                    for (int i = 0; i < totalCanciones; i++) {
                        delete *(biblioteca + i);
                    }
                    totalCanciones = 0;
                    cout << "Biblioteca reiniciada para cargar el nuevo lote de " << cantidadAProcesar << " pistas." << endl;
                }

                char rutaActual[256];
                if (modo == 1) {
                    cout << "Ingrese la ruta del MP3 (ejemplo-> data/musica/eternity.mp3): ";
                    cin.getline(rutaActual, 256);
                }

                int cargadasEnLote = 0;
                for (int i = 0; i < cantidadAProcesar; i++) {
                    if (modo >= 2 && modo <= 5) {
                        int numPista = i + 1;
                        char prefijo[64];
                        if (cantidadAProcesar == 10) Cancion::copiarCadena(prefijo, "data/pack_10/pista_");
                        else if (cantidadAProcesar == 20) Cancion::copiarCadena(prefijo, "data/pack_20/pista_");
                        else if (cantidadAProcesar == 30) Cancion::copiarCadena(prefijo, "data/pack_30/pista_");
                        else Cancion::copiarCadena(prefijo, "data/pack_50/pista_");

                        int pos = Cancion::longitudCadena(prefijo);
                        *(prefijo + pos) = static_cast<char>('0' + (numPista / 10));
                        *(prefijo + pos + 1) = static_cast<char>('0' + (numPista % 10));
                        *(prefijo + pos + 2) = '_';
                        *(prefijo + pos + 3) = '\0';

                        Cancion::copiarCadena(rutaActual, prefijo);
                        int posRuta = Cancion::longitudCadena(rutaActual);
                        Cancion::copiarCadena(rutaActual + posRuta, *(bases + (i % 10)));
                    }

                    ifstream verificar(rutaActual, ios::binary);
                    if (!verificar.is_open()) {
                        if (modo == 1) {
                            throw ExcepcionArchivoInvalido("No se pudo abrir el archivo en la ruta indicada.");
                        }
                        continue;
                    }
                    verificar.seekg(0, ios::end);
                    long tamArchivo = static_cast<long>(verificar.tellg());
                    verificar.close();

                    if (tamArchivo < 128) {
                        if (modo == 1) {
                            throw ExcepcionArchivoInvalido("Archivo corrupto o demasiado pequeno para ser audio valido.");
                        }
                        continue;
                    }

                    DatosAudio datos;
                    bool leido = lectorV2.leer(rutaActual, datos);
                    if (!leido) {
                        leido = lectorV1.leer(rutaActual, datos);
                    }

                    if (!leido || Cancion::longitudCadena(datos.titulo) == 0) {
                        const char* inicioNombre = rutaActual;
                        const char* p = rutaActual;
                        while (*p != '\0') {
                            if (*p == '/' || *p == '\\') inicioNombre = p + 1;
                            p++;
                        }
                        int k = 0;
                        while (*(inicioNombre + k) != '\0' && *(inicioNombre + k) != '.' && k < 127) {
                            *(datos.titulo + k) = *(inicioNombre + k);
                            k++;
                        }
                        *(datos.titulo + k) = '\0';
                    }

                    if (Cancion::longitudCadena(datos.artista) == 0) {
                        Cancion::copiarCadena(datos.artista, "Artista MP3");
                    }
                    if (datos.tamanoBytes <= 0) {
                        datos.tamanoBytes = tamArchivo;
                    }
                    if (datos.duracion <= 0.0) {
                        datos.duracion = (datos.tamanoBytes * 8.0) / 128000.0;
                    }
                    if (datos.anio <= 0) {
                        datos.anio = 2026 - (i % 15);
                    }

                    Cancion* nueva = nullptr;
                    if (i % 3 == 0) {
                        nueva = new PistaEstudio(datos.titulo, datos.artista, datos.duracion, datos.anio, datos.tamanoBytes, "Estudio Central");
                    } else if (i % 3 == 1) {
                        nueva = new PistaEnVivo(datos.titulo, datos.artista, datos.duracion, datos.anio, datos.tamanoBytes, "Arena Tour");
                    } else {
                        nueva = new PistaAcustica(datos.titulo, datos.artista, datos.duracion, datos.anio, datos.tamanoBytes, "Guitarra Acustica");
                    }

                    if (totalCanciones == capacidad) {
                        redimensionarCatalogo(biblioteca, capacidad, totalCanciones);
                    }
                    *(biblioteca + totalCanciones) = nueva;
                    totalCanciones++;

                    cola.agregar(nueva);
                    playlist.agregarCancion(nueva);
                    artistaDemo.agregarObra(nueva);
                    albumDemo.agregarPista(nueva->clonar());
                    cargadasEnLote++;
                }

                cout << "Todo okey. Se cargaron " << cargadasEnLote << " canciones en memoria." << endl;

            } else if (opcion == 2) {
                char tit[128], art[128], extra[128];
                double dur = 0;
                int anio = 2026, tipo = 1;
                long tam = 4000000;

                cout << "Titulo : ";
                cin.getline(tit, 128);
                if (Cancion::longitudCadena(tit) == 0) {
                    throw ExcepcionMemoriaVacia("El titulo no puede estar vacio.");
                }

                cout << "Artista : ";
                cin.getline(art, 128);
                if (Cancion::longitudCadena(art) == 0) {
                    Cancion::copiarCadena(art, "Desconocido");
                }

                cout << "Duracion en segundos: ";
                cin >> dur;
                cout << "Anio: ";
                cin >> anio;
                cout << "Tipo (1: Estudio, 2: En Vivo, 3: Acustica): ";
                cin >> tipo;
                limpiarBuffer();

                if (dur <= 0) {
                    throw ExcepcionArchivoInvalido("La duracion debe ser mayor a 0 segundos.");
                }

                Cancion* nueva = nullptr;
                if (tipo == 2) {
                    cout << "Lugar: ";
                    cin.getline(extra, 128);
                    nueva = new PistaEnVivo(tit, art, dur, anio, tam, extra);
                } else if (tipo == 3) {
                    cout << "Instrumento: ";
                    cin.getline(extra, 128);
                    nueva = new PistaAcustica(tit, art, dur, anio, tam, extra);
                } else {
                    cout << "Estudio: ";
                    cin.getline(extra, 128);
                    nueva = new PistaEstudio(tit, art, dur, anio, tam, extra);
                }

                if (totalCanciones == capacidad) {
                    redimensionarCatalogo(biblioteca, capacidad, totalCanciones);
                }
                *(biblioteca + totalCanciones) = nueva;
                totalCanciones++;

                cola.agregar(nueva);
                playlist.agregarCancion(nueva);
                artistaDemo.agregarObra(nueva);
                albumDemo.agregarPista(nueva->clonar());

                cout << "Cancion registrada correctamente." << endl;

            } else if (opcion == 3) {
                mostrarCatalogo(biblioteca, totalCanciones);
                if (totalCanciones > 0) {
                    cout << "Ingrese numero de pista para ver ficha tecnica y simular reproducir : ";
                    int idx = 0;
                    cin >> idx;
                    limpiarBuffer();
                    if (idx >= 1 && idx <= totalCanciones) {
                        Cancion* sel = *(biblioteca + idx - 1);
                        sel->mostrarFichaTecnica();
                        sel->reproducir();
                    }
                }

            } else if (opcion == 4) {
                cola.mostrarCola();
                if (!cola.estaVacia()) {
                    cout << "1. Reproducir actual | 2. Siguiente | 3. Anterior | 0. Volver: ";
                    int sub = 0;
                    cin >> sub;
                    limpiarBuffer();
                    if (sub == 1 && cola.obtenerActual() != nullptr) cola.obtenerActual()->reproducir();
                    else if (sub == 2) cola.siguiente();
                    else if (sub == 3) cola.anterior();
                }

            } else if (opcion == 5) {
                cout << endl;
                playlist.mostrarLista();
                cout << endl;
                albumDemo.mostrarAlbum();
                cout << endl;
                artistaDemo.mostrarDiscografia();

            } else if (opcion == 6) {
                if (totalCanciones < 2) {
                    cout << "Agregue al menos 2 canciones para ordenar y medir benchmark." << endl;
                } else {
                    cout << "\nCriterio de ordenamiento:" << endl;
                    cout << " 1. Alfabeticamente (Titulo)" << endl;
                    cout << " 2. Por Tiempo (Duracion en segundos)" << endl;
                    cout << " 3. Por Fecha (Anio de lanzamiento)" << endl;
                    cout << " 4. Por Orden de Agregacion (#ID)" << endl;
                    cout << "Seleccione criterio: ";
                    int critOp = 1;
                    cin >> critOp;

                    cout << "Direccion (1: Ascendente [A-Z / Menor a Mayor] | 2: Descendente [Z-A / Mayor a Menor]): ";
                    int dirOp = 1;
                    cin >> dirOp;

                    cout << "\nAlgoritmo de ordenamiento:" << endl;
                    cout << " 1. Bubble Sort" << endl;
                    cout << " 2. Selection Sort" << endl;
                    cout << " 3. Insertion Sort" << endl;
                    cout << " 4. Shell Sort" << endl;
                    cout << " 5. QuickSort" << endl;
                    cout << " 6. MergeSort" << endl;
                    cout << "Seleccione algoritmo: ";
                    int alg = 5;
                    cin >> alg;
                    limpiarBuffer();

                    CriterioOrden criterio = POR_TITULO;
                    if (critOp == 2) criterio = POR_DURACION;
                    else if (critOp == 3) criterio = POR_ANIO;
                    else if (critOp == 4) criterio = POR_AGREGACION;

                    bool ascendente = (dirOp != 2);

                    auto inicio = high_resolution_clock::now();
                    const char* nombreAlg = "QuickSort";

                    if (alg == 1) {
                        MotorOrdenamiento::ordenarBurbuja(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "BubbleSort";
                    } else if (alg == 2) {
                        MotorOrdenamiento::ordenarSeleccion(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "SelectionSort";
                    } else if (alg == 3) {
                        MotorOrdenamiento::ordenarInsercion(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "InsertionSort";
                    } else if (alg == 4) {
                        MotorOrdenamiento::ordenarShellSort(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "ShellSort";
                    } else if (alg == 6) {
                        MotorOrdenamiento::ordenarMergeSort(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "MergeSort";
                    } else {
                        MotorOrdenamiento::ordenarQuickSort(biblioteca, totalCanciones, criterio, ascendente);
                        nombreAlg = "QuickSort";
                    }

                    auto fin = high_resolution_clock::now();
                    double ms = duration<double, milli>(fin - inicio).count();

                    cout << "Ordenado con " << nombreAlg << " (" << (ascendente ? "Ascendente" : "Descendente") << ") en " << ms << " ms." << endl;
                    mostrarCatalogo(biblioteca, totalCanciones);
                    persistencia.registrarBenchmark(nombreAlg, totalCanciones, ms);
                }

            } else if (opcion == 7) {
                if (!persistencia.guardarBiblioteca(biblioteca, totalCanciones)) {
                    throw ExcepcionArchivoInvalido("No se pudo guardar data/biblioteca.txt. Verifique que exista la carpeta data/.");
                }
                cout << "Biblioteca guardada en: " << persistencia.getRutaBiblioteca() << endl;
                persistencia.mostrarLogBenchmark();
            }

        } catch (const ExcepcionReproductor& ex) {
            cerr << "\n[EXCEPCION CAPTURADA]: " << ex.obtenerMensaje() << endl;
        }
    }

    for (int i = 0; i < totalCanciones; i++) {
        delete *(biblioteca + i);
    }
    delete[] biblioteca;

    cout << "Memoria liberada correctamente. Programa finalizado." << endl;
    return 0;
}