/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "defesa.h"

#include <math.h>
#include <stdlib.h>

#include "objeto.h"

/* Cria aleatoriamente com prob. p e retorna uma variável do tipo Defesa. */
Defesa *geraDefesaAleatoria(double p) {
  double dado = randomDouble(0, 1);
  Defesa *newDef;
  if (dado > p)
    return NULL;
  else {
    newDef = mallocSafe(sizeof(Defesa));
    newDef->hp = 5;
    newDef->accuracy = 1;
    newDef->range = 150;
    newDef->firerate = 30;

    /* geração aleatória da posição (x,y) */
    newDef->posicao.x = ((int)(666 * sin(42 * dado))) % 20 - 10;
    newDef->posicao.y = ((int)(42 * cos(666 * dado))) % 10;
    newDef->posicao.z = -500;

    return newDef;
  }
}
