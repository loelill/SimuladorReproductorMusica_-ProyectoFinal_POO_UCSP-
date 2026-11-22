# Autores

-Llacho Zapana Loeli Eidhoven 
-Sucasaca Cohata Diego Fabrizio 
-Vilca Asqui Milton Pavel 

# Sistema de Gestión y Reproducción Musical en C++ (POO)

Proyecto final desarrollado en **C++** enfocado en la aplicación práctica de los pilares de la **Programación Orientada a Objetos (POO)**, gestión manual de memoria dinámica, aritmética de punteros, lectura binaria de metadatos ID3 (v1 y v2), persistencia en archivos y análisis empírico (*benchmark*) de algoritmos de ordenamiento.

---

## Características Principales y Restricciones Técnicas

* **Cero STL y Cero Librerías de Cadenas:** Implementación artesanal de manejo de cadenas (`char*`), arreglos dinámicos auto-redimensionables (`Cancion**`), listas doblemente enlazadas (`ColaReproduccion`) y ordenamiento sin utilizar `vector`, `string`, `<cstring>` ni `<algorithm>`.
* **Aritmética de Punteros Pura:** Acceso y recorrido de arreglos dinámicos mediante desplazamiento explícito de direcciones (`*(arreglo + i)`).
* **Jerarquía Polimórfica y Regla de los Tres:**
  * Clase base abstracta `Cancion` con métodos virtuales puros (`reproducir()`, `mostrarFichaTecnica()`, `clonar()`) y destructor virtual.
  * Clases derivadas: `PistaEstudio`, `PistaEnVivo` y `PistaAcustica`.
  * Implementación completa de constructor de copia, operador de asignación (`operator=`) y destructor para prevenir fugas de memoria (*memory leaks*).
* **Asociación vs. Composición:**
  * `ListaReproduccion`, `ColaReproduccion` y `Artista` mantienen referencias compartidas (asociación) a las pistas de la biblioteca.
  * `Album` almacena copias profundas independientes generadas mediante `clonar()` (composición).
* **Lectura Binaria de Archivos MP3:** Soporte para extracción de metadatos **ID3v2** e **ID3v1** mediante flujos binarios (`<fstream>`), con respaldo automático basado en el tamaño del archivo cuando no existen etiquetas embebidas.
* **Motor de Ordenamiento Multicriterio y Benchmark:**
  * **6 Algoritmos:** Bubble Sort, Selection Sort, Insertion Sort, Shell Sort, QuickSort y MergeSort.
  * **4 Criterios:** Alfabético (Título), Tiempo (Duración en segundos), Fecha (Año de lanzamiento) y Orden de Agregación (`#ID`), en dirección **Ascendente** o **Descendente**.
  * Medición de tiempo real en milisegundos con `<chrono>` sobre lotes de prueba (`pack_10`, `pack_20`, `pack_30`, `pack_50`) y registro en `data/benchmark.txt`.
* **Manejo de Excepciones Personalizadas:** Jerarquía `ExcepcionReproductor` (`ExcepcionArchivoInvalido`, `ExcepcionMemoriaVacia`) para capturar errores en tiempo de ejecución sin interrumpir el flujo del programa.

---

## Estructura del Proyecto

```text
├── bin/                    # Ejecutable compilado (reproductor_final.exe)
├── data/                   # Archivos de persistencia y lotes de prueba MP3
│   ├── musica/             # Pistas MP3 base
│   ├── pack_10/            # Lote de prueba con 10 pistas (no incluye pero si gustan colocan mas)
│   ├── pack_20/            # Lote de prueba con 20 pistas
│   ├── pack_30/            # Lote de prueba con 30 pistas
│   ├── pack_50/            # Lote de prueba con 50 pistas
│   
│   
├── include/                # Archivos de cabecera (.h)
│   ├── Album.h
│   ├── Artista.h
│   ├── Cancion.h
│   ├── ColaReproduccion.h
│   ├── Excepciones.h
│   ├── GestorPersistencia.h
│   ├── LectorID3.h
│   ├── LectorID3v1.h
│   ├── LectorID3v2.h
│   ├── ListaReproduccion.h
│   ├── MotorOrdenamiento.h
│   ├── PistaAcustica.h
│   ├── PistaEnVivo.h
│   └── PistaEstudio.h
└── src/                    # Implementaciones cpp y punto de entrada
    ├── Album.cpp
    ├── Artista.cpp
    ├── Cancion.cpp
    ├── ColaReproduccion.cpp
    ├── GestorPersistencia.cpp
    ├── LectorID3v1.cpp
    ├── LectorID3v2.cpp
    ├── ListaReproduccion.cpp
    ├── MotorOrdenamiento.cpp
    ├── PistaAcustica.cpp
    ├── PistaEnVivo.cpp
    ├── PistaEstudio.cpp
    └── main.cpp
