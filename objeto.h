/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#ifndef H_OBJETO_DEFINED
#define H_OBJETO_DEFINED
#include <stdlib.h> /* size_t */

#define PI  3.14159265358979323846
#define FREEZE 2 /* Tempo padrão que o programa fica parado em congela() */

typedef struct vetor Vetor;
struct vetor {
   double x;
   double y;
   double z;
};

/* Eixos estão definidos como x = horizontal, y = vertical,
 z = profundidade */

double randomDouble(double low, double high);
void * mallocSafe(size_t nbytes);
double distancia(Vetor vet1, Vetor vet2);
double modulo(double numero);

#endif
