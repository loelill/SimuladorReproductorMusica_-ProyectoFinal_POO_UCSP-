#include <ListaReproduccion.h>
ListaReproduccion::ListaReproduccion(const char* nom):cantidadCanciones(0),capacidad(4)
{
  int len=Cancion::longitudCadena(nom);
  nombre =new char[len +1];
  Cancion::copiarCadena(nombre,nom);
  canciones =new Cancion*[capacidad];
}
ListaReproduccion::ListaReproduccion(const ListaReproduccion& otra):cantidadCanciones(otra.cantidadCanciones),capacidad(otra.capacidad)
{
  int len=Cancion::longitudCadena(otra.nombre);
  nombre =new char[len +1];
  Cancion::copiarCadena(nombre,otra.nombre);
  canciones =new Cancion*[capacidad];
  for(int i=0;i<cantidadCanciones;i++)
  {
    *(canciones +i)=*(otra.canciones +i);
  }
}
  ListaReproduccion& ListaReproduccion::operator=(const ListaReproduccion& otra)
{
  if(this!=&otra)
  {
      delete []nombre ;
      delete []canciones ;
      cantidadCanciones=otra.cantidadCanciones;
      capacidad=otra.capacidad;
      int len=Cancion::longitudCadena(otra.nombre);
        nombre=new char[len +1];
      Cancion::copiarCadena(nombre,otra.nombre);
        canciones=new Cancion*[capacidad];
      for(int i=0;i<cantidadCanciones;i++)
      {
        *(canciones +i)=*(otra.canciones +i);
      }
  }
  return *this;
}

ListaReproduccion::~ListaReproduccion(){delete []nombre;delete []canciones;}

void ListaReproduccion::redimensionar()
{
    capacidad *=2;
    Cancion** nuevoArreglo =new Cancion*[capacidad];
    for(int i=0;i<cantidadCanciones;i++)
    {
      *(nuevoArreglo +i)=*(canciones +i);
    }
    delete []canciones;
    canciones=nuevoArreglo;
}

void ListaReproduccion::agregarCancion(Cancion* cancion)
{
    if(cancion==nullptr) return;
    if(cantidadCanciones==capacidad)
    {
      redimensionar();
    }
    *(canciones +cantidadCanciones)=cancion;
    cantidadCanciones++;
}

void ListaReproduccion::mostrarLista() const 
{
    cout << "LISTA: " << nombre << " | Canciones: " << cantidadCanciones << endl;
    for(int i=0;i<cantidadCanciones;i++)
    {
      cout << " [" << (i +1) << "] " << *(*(canciones +i)) << endl;
    }
}

const char* ListaReproduccion::getNombre() const 
{
      return nombre;
}

int ListaReproduccion::getCantidadCanciones() const 
{
      return cantidadCanciones;
}

Cancion* ListaReproduccion::getCancion(int indice) const 
{
      if(indice<0 || indice>=cantidadCanciones) return nullptr;
      return *(canciones +indice);
}
