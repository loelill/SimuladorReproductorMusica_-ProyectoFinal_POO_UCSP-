#include <PistaAcustica.h>
PistaAcustica::PistaAcustica(const char* tit, const char* art, double dur, int anioLanzamiento, long tamano, const char* inst):Cancion(tit,art,dur,anioLanzamiento ,tamano)
{
  int len=longitudCadena(inst);
  instrumento =new char[len +1];
  copiarCadena(instrumento,inst);
}
PistaAcustica::PistaAcustica(const PistaAcustica& otra):Cancion(otra)
{
    int len=longitudCadena(otra.instrumento);
  instrumento =new char[len +1];
  copiarCadena(instrumento,otra.instrumento);
}
  PistaAcustica& PistaAcustica::operator=(const PistaAcustica& otra)
{
  if(this!=&otra)
  {
    Cancion::operator=(otra);
      delete []instrumento ;
      int len=longitudCadena(otra.instrumento);
        instrumento=new char[len +1];
      copiarCadena(instrumento,otra.instrumento);
      
  }
  return *this;
}

PistaAcustica::~PistaAcustica(){delete []instrumento;}

void PistaAcustica::reproducir() {
    cout << "[ACUSTICA] Reproduciendo: " << *this << endl;
}

void PistaAcustica::mostrarFichaTecnica() const 
{
    cout << "------ ACUSTICA ------" << endl;
    cout << "Titulo   : " << titulo << endl;
    cout << "Artista  : " << artista << endl;
    cout << "Anio     : " << anio << endl;
    cout << "Duracion : " << duracion << " s" << endl;
    cout << "Tamano   : " << tamanoBytes << " bytes" << endl;
    cout << "Instrum. : " << instrumento << endl;
}

Cancion* PistaAcustica::clonar() const 
{
    return new PistaAcustica(*this);
}

const char* PistaAcustica::getInstrumento() const 
{
      return instrumento;
}
