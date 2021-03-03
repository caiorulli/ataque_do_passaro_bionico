/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "tiro.h"

#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>

#include "nave.h"
#include "objeto.h"

static Tiro *lst = NULL;
extern Nave *nave;

void criaListaTiro() {
  lst = mallocSafe(sizeof(Tiro));
  lst->prox = NULL;
}

/* Percorre cada Tiro da lista, atualizando sua posição ou removendo-o, se necessário. */
void atualizaListaTiro() {
  Tiro *p, *q;
  p = lst;
  q = p->prox;

  while (q != NULL) {
    q->posicao.x += q->vel.x;
    q->posicao.y += q->vel.y;
    q->posicao.z += q->vel.z - nave->vel.z;
    if (q->posicao.z > HITBOXNAVE || q->posicao.z < LIMITEPROF ||
        q->posicao.y < LIMITEINF + 0.1) {
      p->prox = q->prox;
      free(q);
      q = p->prox;
      continue;
    }
    q = q->prox;
    p = p->prox;
  }
}

void insereTiro(bool origem, Vetor posicao, Vetor veloc) {
  Tiro *p;

  p = mallocSafe(sizeof(*p));

  p->posicao.x = posicao.x;
  p->posicao.y = posicao.y;
  p->posicao.z = posicao.z;
  p->vel.x = veloc.x;
  p->vel.y = veloc.y;
  p->vel.z = veloc.z;
  p->origem = origem;

  p->prox = lst->prox;
  lst->prox = p;
}

/* Recebe a posicao da nave e devolve quantos tiros acertaram-na. */
int levouTiroNave() {
  Tiro *p, *q;
  int n = 0;
  p = lst;
  q = lst->prox;
  while (q != NULL) {
    if (q->origem != AMIGO &&
        distancia(q->posicao, nave->posicao) <= HITBOXNAVE) {
      n++;
      p->prox = q->prox;
      free(q);
      q = p->prox;
    } else {
      p = p->prox;
      q = q->prox;
    }
  }
  return n;
}

/* Recebe um ponteiro para um inimigo e retorna quantos tiros acertaram-no. */
int levouTiroDefesa(Defesa *def) {
  Tiro *p, *q;
  int n = 0;
  p = lst;
  q = lst->prox;
  while (q != NULL) {
    if (q->origem == AMIGO &&
        distancia(q->posicao, def->posicao) <= HITBOXDEF) {
      n++;
      p->prox = q->prox;
      free(q);
      q = p->prox;
    } else {
      p = p->prox;
      q = q->prox;
    }
  }
  return n;
}

void desenhaTiros(void) {
  Tiro *p;
  for (p = lst->prox; p != NULL; p = p->prox) {
    if (p->origem == AMIGO)
      glColor3f(0, 0, 1);
    else
      glColor3f(1, 0, 0);
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3f(p->posicao.x, p->posicao.y, p->posicao.z);
    glEnd();
  }
}

void freeListaTiro() {
  Tiro *q;
  for (q = lst->prox; q != NULL; q = lst->prox) {
    lst->prox = q->prox;
    free(q);
  }
  free(lst);
  q = lst = NULL;
}

/* testes. */
Tiro *devolveListaTiro() { return lst; }
