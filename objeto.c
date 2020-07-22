/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "objeto.h"
#include <math.h>
#include <stdio.h>  /* fprintf() */
#include <stdlib.h> /* RAND_MAX, malloc(), exit() */
#include <time.h>   /* clock(), CLOCKS_PER_SEC */

/* Calcula a distancia entre as duas posições descritas pelas variáveis
      vet1 e vet2. */

double distancia(Vetor vet1, Vetor vet2)
{
   double d = 0;
   d += (vet2.x - vet1.x)*(vet2.x - vet1.x);
   d += (vet2.y - vet1.y)*(vet2.y - vet1.y);
   d += (vet2.z - vet1.z)*(vet2.z - vet1.z);
   return sqrt(d);
}

double randomDouble(double low, double high)
{
   double d;

   d = (double) rand() / ((double) RAND_MAX + 1);
   d *= (high - low + 1);

   return d;
}

/*O parâmetro de mallocSafe é do tipo size_t.  
      Em muitos computadores, size_t é equivalente a unsigned int.  
      A função protege o programa contra falta de memória ao fazer "malloc".

      Fonte: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html*/

void * mallocSafe(size_t nbytes)
{
   void *ptr;
   ptr = malloc(nbytes);

   if (ptr == NULL) {
      fprintf(stderr, "Erro! Acabou a memória!!!\n");
      exit(EXIT_FAILURE);
   }

   return ptr;
}

double modulo(double numero) {
   if (numero < 0)
      return - numero;
   return numero;
}
