#ifndef INC_EMERGE2_H
#define INC_EMERGE2_H

struct Resultado
{
  char           *FormaCanonica;
  char           *Pronombre;
  char           *Prefijo;
  short int      Categoria;    // Categor�a gramatical.
  unsigned char  Antigua;      // Antigua 1=S�, 0=No.
  short int      Clasificacion;// Valor del c�digo de calsificaci�n sem�ntica de momento verbal.
  short int      Flexion;      // Valor del c�digo agrupado de la flexi�n reconocida.
  long           DirPalFich;   // Posici�n con colisiones resultas de un registro de infinitivo en PalFich.
  unsigned char  GenNum;       // Indica los posibles cambios de significado con el g�nero y el n�mero (0=no cambia,1=g�nero,2=n�mero,3=g�nero y n�mero).
};

extern "C" void _stdcall inicializaMorfo(const char *Ruta);
extern "C" void _stdcall reconoce(const char *Palabra, Resultado *Res, int &NumPalabras, unsigned char ConPrefijo );
extern "C" int  _stdcall genera( int formaCanonica, int flexion, const char *prefijo, const char *pronombre, char *VectorPalabras[]);
extern "C" int  _stdcall dameCategoriasElementales( int Categoria, int *VecCatElementales );
extern "C" int  _stdcall dameClasificacionesElementales( int Clasificacion, int *VecClasifElementales );
extern "C" void _stdcall eliminaVector( Resultado *Res, int NumPalabras );

#endif

