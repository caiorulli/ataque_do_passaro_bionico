/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#ifndef H_TIRO_DEFINED
#define H_TIRO_DEFINED
   
#include <stdbool.h>
#include <GL/glut.h>
#include "objeto.h"
#include "nave.h"
#include "defesa.h"
#include "tiro.h"

#define AMIGO true   /* Analisa se o tiro foi feito por algum inimigo ou pela nave */

/* Limites do cenário */
#define LIMITEESQ -10
#define LIMITEDIR 10
#define LIMITESUP 10
#define LIMITEINF -10
#define LIMITEPROF -500

typedef struct tiro Tiro;
struct tiro {
   bool origem;
   Vetor posicao;
   Vetor vel;
   Tiro *prox;
};

void criaListaTiro();

void atualizaListaTiro();
void atualizaTiro(Tiro *tiro);
void insereTiro(bool origem, Vetor posicao, Vetor veloc);
int  levouTiroNave();
int  levouTiroDefesa(Defesa *def);
void desenhaTiros(void);
void freeListaTiro();

Tiro * devolveListaTiro();

#endif