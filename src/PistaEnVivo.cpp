#include <PistaEnVivo.h>
PistaEnVivo::PistaEnVivo(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* lug):Cancion(tit,art,dur,anioLanzamiento ,tamano)
{
  int len=longitudCadena(lug);
  lugar =new char[len +1];
  copiarCadena(lugar,lug);
}
PistaEnVivo::PistaEnVivo(const PistaEnVivo& otra):Cancion(otra)
{
    int len=longitudCadena(otra.lugar);
  lugar =new char[len +1];
  copiarCadena(lugar,otra.lugar);
}
  PistaEnVivo& PistaEnVivo::operator=(const PistaEnVivo& otra)
{
  if(this!=&otra)
  {
    Cancion::operator=(otra);
      delete []lugar ;
      int len=longitudCadena(otra.lugar);
        lugar=new char[len +1];
      copiarCadena(lugar,otra.lugar);
      
  }
  return *this;
}

PistaEnVivo::~PistaEnVivo(){delete []lugar;}

void PistaEnVivo::reproducir() {
    cout << "[EN VIVO] Reproduciendo: " << *this << endl;
}

void PistaEnVivo::mostrarFichaTecnica() const 
{
    cout << "------ EN VIVO ------" << endl;
    cout << "Titulo   : " << titulo << endl;
    cout << "Artista  : " << artista << endl;
    cout << "Anio     : " << anio << endl;
    cout << "Duracion : " << duracion << " s" << endl;
    cout << "Tamano   : " << tamanoBytes << " bytes" << endl;
    cout << "Lugar    : " << lugar << endl;
}

Cancion* PistaEnVivo::clonar() const 
{
    return new PistaEnVivo(*this);
}

const char* PistaEnVivo::getLugar() const 
{
      return lugar;
}
