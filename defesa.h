/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#ifndef H_DEFESA_DEFINED
#define H_DEFESA_DEFINED

#include <stdbool.h>
#include <GL/glut.h>
#include "objeto.h"

#define NMAXDEF 10 /* Número máximo de inimigos simultaneamente na tela */
#define HITBOXDEF 5

typedef struct defesa Defesa;
struct defesa {
   int hp;
   Vetor posicao;
   int accuracy;
   double range;
   int firerate;
   Defesa *prox;
};

void criaListaDefesa();
void atualizaListaDefesa();
void insereDefesa(Defesa *defesa);
void defesasAtiram(unsigned int timestep);
bool naveDefesaColidiram();
void calculaDanoDefesas();
void desenhaDefesas(void);
void freeListaDefesa();

Defesa * devolveListaDefesa();

#endif
