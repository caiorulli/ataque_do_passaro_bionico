/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "defesa.h"

#include <stdbool.h>

#include "cenario.h"
#include "nave.h"
#include "objeto.h"
#include "tiro.h"
#define DEFESAHP 5

static Defesa *listaDefesa = NULL;
extern Nave *nave;
extern unsigned int pontuacao;
extern unsigned int timestep;

void criaListaDefesa() {
  listaDefesa = mallocSafe(sizeof(Defesa));
  listaDefesa->prox = NULL;
}

/*Percorre cada Defesa da lista, atualizando sua posição. Se for necessário,
      remove o inimigo da lista.*/
void atualizaListaDefesa() {
  Defesa *p, *q;

  p = listaDefesa;
  q = p->prox;
  while (q != NULL) {
    q->posicao.z -= nave->vel.z;
    if (q->hp <= 0 || q->posicao.z > 0) {
      /* pontuação:  +timestep sempre que matar algum inimigo */
      if (q->hp <= 0)
        pontuacao += timestep;
      p->prox = q->prox;
      free(q);
    } else
      p = p->prox;
    q = p->prox;
  }
}

void insereDefesa(Defesa *defesa) {
  Defesa *q;
  if (defesa == NULL)
    return;
  for (q = listaDefesa; q->prox != NULL; q = q->prox)
    ;
  q->prox = defesa;
  defesa->prox = NULL;
}

/*
      Determina se os inimigos da lista de Defesa atiram, e, se isso ocorrer,
      cria um Tiro e insere na lista de mesmo tipo.*/

void defesasAtiram(unsigned int timestep) {
  Defesa *q;
  Vetor shotspeed;
  for (q = listaDefesa->prox; q != NULL; q = q->prox) {
    if (!(timestep % q->firerate) &&
        distancia(q->posicao, nave->posicao) <= q->range) {
      shotspeed.x = ((nave->posicao.x + nave->vel.x * 2) - q->posicao.x) / 2;
      shotspeed.x *= randomDouble(1 / q->accuracy, q->accuracy);
      shotspeed.y = ((nave->posicao.y + nave->vel.y * 2) - q->posicao.y) / 2;
      shotspeed.y *= randomDouble(1 / q->accuracy, q->accuracy);
      shotspeed.z = ((nave->posicao.z + nave->vel.z * 2) - q->posicao.z) / 2;
      shotspeed.z *= randomDouble(1 / q->accuracy, q->accuracy);
      insereTiro(!AMIGO, q->posicao, shotspeed);
    } /* Evita que a defesa atire toda hora */
  }
}

/*Recebe a posicao da nave e verifica se ela colidiu com algum inimigo.*/
bool naveDefesaColidiram() {
  Defesa *q;

  for (q = listaDefesa->prox; q != NULL; q = q->prox)
    if (distancia(q->posicao, nave->posicao) < (HITBOXNAVE + HITBOXDEF))
      return true;

  return false;
}

/*Percorre a lista, analisando se alguma defesa levou dano.*/
void calculaDanoDefesas() {
  Defesa *q;
  int dano;

  for (q = listaDefesa->prox; q != NULL; q = q->prox) {
    dano = levouTiroDefesa(q);
    q->hp -= dano;
  }
}

void desenhaDefesas(void) {
  Defesa *p;
  for (p = listaDefesa->prox; p != NULL; p = p->prox) {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    /* suporte da torre */
    glVertex3f(p->posicao.x - 0.1, -10, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x + 0.1, -10, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x + 0.1, p->posicao.y, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x - 0.1, p->posicao.y, p->posicao.z - 0.1);

    glVertex3f(p->posicao.x - 0.1, -10, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x - 0.1, p->posicao.y, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x - 0.1, p->posicao.y, p->posicao.z + 0.1);
    glVertex3f(p->posicao.x - 0.1, -10, p->posicao.z + 0.1);

    glVertex3f(p->posicao.x + 0.1, -10, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x + 0.1, p->posicao.y, p->posicao.z - 0.1);
    glVertex3f(p->posicao.x + 0.1, p->posicao.y, p->posicao.z + 0.1);
    glVertex3f(p->posicao.x + 0.1, -10, p->posicao.z + 0.1);

    glVertex3f(p->posicao.x - 0.1, -10, p->posicao.z + 0.1);
    glVertex3f(p->posicao.x + 0.1, -10, p->posicao.z + 0.1);
    glVertex3f(p->posicao.x + 0.1, p->posicao.y, p->posicao.z + 0.1);
    glVertex3f(p->posicao.x - 0.1, p->posicao.y, p->posicao.z + 0.1);

    /* elemento principal da torre */
    glVertex3f(p->posicao.x - 2, p->posicao.y - 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y - 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y + 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 2, p->posicao.z - 2);

    glVertex3f(p->posicao.x - 2, p->posicao.y - 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 2, p->posicao.z + 2);
    glVertex3f(p->posicao.x - 2, p->posicao.y - 2, p->posicao.z + 2);

    glVertex3f(p->posicao.x + 2, p->posicao.y - 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y + 2, p->posicao.z - 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y + 2, p->posicao.z + 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y - 2, p->posicao.z + 2);

    glVertex3f(p->posicao.x - 2, p->posicao.y - 2, p->posicao.z + 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y - 2, p->posicao.z + 2);
    glVertex3f(p->posicao.x + 2, p->posicao.y + 2, p->posicao.z + 2);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 2, p->posicao.z + 2);
    glEnd();

    /* barra de vida */
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 4, p->posicao.z);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 3, p->posicao.z);
    glVertex3f(p->posicao.x + 3, p->posicao.y + 3, p->posicao.z);
    glVertex3f(p->posicao.x + 3, p->posicao.y + 4, p->posicao.z);

    glColor3f(0, 1, 1);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 4, p->posicao.z + 0.01);
    glVertex3f(p->posicao.x - 2, p->posicao.y + 3, p->posicao.z + 0.01);
    glVertex3f(p->posicao.x - 2 + 5 * ((double)p->hp / DEFESAHP),
               p->posicao.y + 3, p->posicao.z + 0.01);
    glVertex3f(p->posicao.x - 2 + 5 * ((double)p->hp / DEFESAHP),
               p->posicao.y + 4, p->posicao.z + 0.01);
    glEnd();
  }
}

void freeListaDefesa() {
  Defesa *q;
  for (q = listaDefesa->prox; q != NULL; q = listaDefesa->prox) {
    listaDefesa->prox = q->prox;
    free(q);
  }
  free(listaDefesa);
  listaDefesa = q = NULL;
}

/*testes.*/
Defesa *devolveListaDefesa() { return listaDefesa; }
