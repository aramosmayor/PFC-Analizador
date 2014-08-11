#ifndef INC__MacrosH
#define INC__MacrosH

//definicion de macros compartidas por las clases del analisis

#define MAX_CAT_ELEM 1011 //codigo mas alto de la categoria elemental + 1
#define MAX_RES 1500 //maximo numero de resultados distintos al analizar lexicamente una palabra
#define MAXLONTRAD 500 //maxima longitud de las lineas del fichero traducciones.txt y mascarasFlexiones.txt
#define MAX_PAL 150 //maximo numero de palabras por oracion
#define MAX_LON_PAL 100 //maxima longitud de las palabras de la oracion a analizar
#define MAX_LON_ORA 10000 //maxima longitud de la oracion (maxima longitud de cada linea del fichero oraciones.txt)


#define NULO 0 //codigo del simbolo nulo
#define MAX_REG_GRAM 900 //maximas reglas que puede haber en la gramatica
#define MAX_TIPO_GRAM 200 //maximo nº de tipos que puede haaber en la gramatica
#define MAX_FLEX_GRAM 100 //idem con las flexiones
#define MAX_CATEG_GRAM 50 //idem con las categorias
#define MAX_APART_GRAM 50 //idem con los apartados
#define MAX_SIMB_GRAM 200 //maximo numero de simbolos de la gramatica
#define MAX_PREP 64  //maximo numero de preposiciones (que puede alamacenarse en un nodo)

#define MAXLIN 900 //maxima longitud de la linea del fichero de entrada (gramatica.txt, simbolos.txt, tipos.txt, ...)
#define MAX_LON 100 //maxima longitud de las ristras de simbolos, tipos, ...


#define ERROR_PAUSA 0  //0->continuar, 1->pausa despues de cada error
#define ERROR_FICHERO 1//0->salida errores por pantalla, 1->salida en el fichero de errores
#define FERROR "errores.txt"  //fichero en el que se guardaran los errores. Se hace uso de una macro para que sea el mismo en funciones.h y en Unit1.cpp



#define MODO_IMPRESION_COMPLETA

//#define FRASES

//descomentar para que al imprimir el un árbol, se muestre toda la información pormenorizada del nodo (para depuración)

//#define ANALIZA_FICHERO_FRASES

//descomentar para que se analicen las frases del fichero Oraciones_base.txt que debe estar en el mismo directorio que el .exe



//#define NO_BAJA_FRECUENCIA 1 //descomentar para que NO se apliquen los requisitos cuya frecuencia sea baja



#endif
