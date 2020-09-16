/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#ifndef H_NAVE_DEFINED
#define H_NAVE_DEFINED

#include "objeto.h"
#include <GL/glut.h>
#include <stdbool.h>

/* Atributos gerais */
#define NAVEHP 30
#define NAVESPD -0.5
#define NAVEFIRERATE 10
#define HITBOXNAVE 2

/* Posição inicial */
#define INIPOSX 0
#define INIPOSY 0
#define INIPOSZ 0

typedef struct nave Nave;
struct nave {
  int hp;
  Vetor posicao;
  Vetor vel;
};

void criaNave();

void atualizaNave();
void calculaDanoNave();
void naveAtira();
Vetor posicaoDaNave();
double naveSpeed();
bool naveEstaViva();
void naveColidiu();
void desenhaNave(void);
void freeNave();

Nave *devolveNave();

#endif
