#ifndef INC_EMERGE2_H
#define INC_EMERGE2_H

struct Resultado
{
  char           *FormaCanonica;
  char           *Pronombre;
  char           *Prefijo;
  short int      Categoria;    // Categoría gramatical.
  unsigned char  Antigua;      // Antigua 1=Sí, 0=No.
  short int      Clasificacion;// Valor del código de calsificación semántica de momento verbal.
  short int      Flexion;      // Valor del código agrupado de la flexión reconocida.
  long           DirPalFich;   // Posición con colisiones resultas de un registro de infinitivo en PalFich.
  unsigned char  GenNum;       // Indica los posibles cambios de significado con el género y el número (0=no cambia,1=género,2=número,3=género y número).
};

extern "C" void _stdcall inicializaMorfo(const char *Ruta);
extern "C" void _stdcall reconoce(const char *Palabra, Resultado *Res, int &NumPalabras, unsigned char ConPrefijo );
extern "C" int  _stdcall genera( int formaCanonica, int flexion, const char *prefijo, const char *pronombre, char *VectorPalabras[]);
extern "C" int  _stdcall dameCategoriasElementales( int Categoria, int *VecCatElementales );
extern "C" int  _stdcall dameClasificacionesElementales( int Clasificacion, int *VecClasifElementales );
extern "C" void _stdcall eliminaVector( Resultado *Res, int NumPalabras );

#endif

