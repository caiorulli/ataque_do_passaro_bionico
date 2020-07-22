/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "nave.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tiro.h"
#include "objeto.h"
#include "cenario.h"
    
Nave *nave;
extern bool *keySpecialStates;
extern unsigned int timestep;

void criaNave() {
   nave = mallocSafe(sizeof(Nave));

   nave->hp = NAVEHP;
   nave->posicao.x = 0;
   nave->posicao.y = 0;
   nave->posicao.z = 0;
   nave->vel.x = nave->vel.y = 0;
   nave->vel.z = NAVESPD;
}

/*Recebe vetor.
      Atualiza a orientação e posição da nave.*/
void atualizaNave() {
   nave->posicao.x += nave->vel.x;
   nave->posicao.y += nave->vel.y;
   
   /* Verifica se a nave saiu do corredor */
   if (nave->posicao.x < LIMITEESQ) nave->posicao.x = LIMITEESQ;
   if (nave->posicao.x > LIMITEDIR) nave->posicao.x = LIMITEDIR;
   if (nave->posicao.y < LIMITEINF + 1.7) nave->posicao.y = LIMITEINF + 1.7;
   if (nave->posicao.y > LIMITESUP) nave->posicao.y = LIMITESUP;
}

/*Altera a vida da nave, analisando se ela foi atingida por algum tiro.*/
void calculaDanoNave() {
   int dano = levouTiroNave();
   nave->hp -= dano;
}

/*Cria um tiro disparado pela nave e insere na lista de Tiro.*/
void naveAtira() {
   Vetor shotspeed, posicao;
   posicao.x = nave->posicao.x;
   posicao.y = nave->posicao.y + 1.5;
   posicao.z = nave->posicao.z - 3.25;
   shotspeed.x = 2 * nave->vel.x;
   shotspeed.y = 2 * nave->vel.y;
   shotspeed.z = nave->vel.z * 2;
   insereTiro(AMIGO, posicao, shotspeed);
}

Vetor posicaoDaNave() {
   return nave->posicao;
}

bool naveEstaViva() {
   return nave->hp > 0;
}

/*Faz a nave perder vida por ter colidido com algo.*/
void naveColidiu() {
   nave->hp -= 1;
}

void desenhaNave(void) {
   glPushMatrix();
   glTranslatef(nave->posicao.x, nave->posicao.y, nave->posicao.z);
   if (keySpecialStates[GLUT_KEY_RIGHT])
      glRotatef(-10, 0,  1,  0);
   else if (keySpecialStates[GLUT_KEY_LEFT])
      glRotatef(10, 0,  1,  0);
   if (keySpecialStates[GLUT_KEY_UP])
      glRotatef(10, 1,  0,  0);
   else if (keySpecialStates[GLUT_KEY_DOWN])
      glRotatef(-10, 1,  0,  0);

   glBegin(GL_QUADS);
      /* corpo */
      glColor3f(0.8, 0.8, 0);
      glVertex3f(- 1, - 1, + 1);
      glVertex3f(+ 1, - 1, + 1);
      glVertex3f(+ 1, - 1, - 1);
      glVertex3f(- 1, - 1, - 1);

      glColor3f(0, 0.5, 0);
      glVertex3f(- 1, + 1, + 1);
      glVertex3f(+ 1, + 1, + 1);
      glVertex3f(+ 1, + 1, - 1);
      glVertex3f(- 1, + 1, - 1);

      glVertex3f(- 1, - 1, + 1);
      glVertex3f(+ 1, - 1, + 1);
      glVertex3f(+ 1, + 1, + 1);
      glVertex3f(- 1, + 1, + 1);

      glVertex3f(- 1, - 1, + 1);
      glVertex3f(- 1, - 1, - 1);
      glVertex3f(- 1, + 1, - 1);
      glVertex3f(- 1, + 1, + 1);

      glVertex3f(+ 1, - 1, + 1);
      glVertex3f(+ 1, - 1, - 1);
      glVertex3f(+ 1, + 1, - 1);
      glVertex3f(+ 1, + 1, + 1);

      /* pescoço */
      glVertex3f(+ 0.5, + 1, - 1);
      glVertex3f(- 0.5, + 1, - 1);
      glVertex3f(- 0.5, + 1.5, - 2);
      glVertex3f(+ 0.5, + 1.5, - 2);

      glVertex3f(+ 0.5, + 0, - 1);
      glVertex3f(- 0.5, + 0, - 1);
      glVertex3f(- 0.5, + 0.5, - 2);
      glVertex3f(+ 0.5, + 0.5, - 2);

      glVertex3f(- 0.5, + 0, - 1);
      glVertex3f(- 0.5, + 1, - 1);
      glVertex3f(- 0.5, + 1.5, - 2);
      glVertex3f(- 0.5, + 0.5, - 2);

      glVertex3f(+ 0.5, + 0, - 1);
      glVertex3f(+ 0.5, + 1, - 1);
      glVertex3f(+ 0.5, + 1.5, - 2);
      glVertex3f(+ 0.5, + 0.5, - 2);

      /* primeira perna */
      glColor3f(0.8, 0.8, 0);
      glVertex3f(+ 0.5, + 0, + 1);
      glVertex3f(+ 0.3, + 0, + 1);
      glVertex3f(+ 0.3, + 0, + 1.5);
      glVertex3f(+ 0.5, + 0, + 1.5);

      glVertex3f(+ 0.5, - 0.2, + 1);
      glVertex3f(+ 0.3, - 0.2, + 1);
      glVertex3f(+ 0.3, - 0.2, + 1.5);
      glVertex3f(+ 0.5, - 0.2, + 1.5);

      glVertex3f(+ 0.5, + 0, + 1);
      glVertex3f(+ 0.5, - 0.2, + 1);
      glVertex3f(+ 0.5, - 0.2, + 1.5);
      glVertex3f(+ 0.5, + 0, + 1.5);

      glVertex3f(+ 0.3, + 0, - 1);
      glVertex3f(+ 0.3, - 0.2, - 1);
      glVertex3f(+ 0.3, - 0.2, + 1.5);
      glVertex3f(+ 0.3, + 0, + 1.5);

      glVertex3f(+ 0.5, + 0, + 1.5);
      glVertex3f(+ 0.3, + 0, + 1.5);
      glVertex3f(+ 0.3, - 0.2, + 1.5);
      glVertex3f(+ 0.5, - 0.2, + 1.5);

      /* segunda perna */
      glColor3f(0.8, 0.8, 0);
      glVertex3f(- 0.5, + 0, + 1);
      glVertex3f(- 0.3, + 0, + 1);
      glVertex3f(- 0.3, + 0, + 1.5);
      glVertex3f(- 0.5, + 0, + 1.5);

      glVertex3f(- 0.5, - 0.2, + 1);
      glVertex3f(- 0.3, - 0.2, + 1);
      glVertex3f(- 0.3, - 0.2, + 1.5);
      glVertex3f(- 0.5, - 0.2, + 1.5);

      glVertex3f(- 0.5, + 0, + 1);
      glVertex3f(- 0.5, - 0.2, + 1);
      glVertex3f(- 0.5, - 0.2, + 1.5);
      glVertex3f(- 0.5, + 0, + 1.5);

      glVertex3f(- 0.3, + 0, - 1);
      glVertex3f(- 0.3, - 0.2, - 1);
      glVertex3f(- 0.3, - 0.2, + 1.5);
      glVertex3f(- 0.3, + 0, + 1.5);

      glVertex3f(- 0.5, + 0, + 1.5);
      glVertex3f(- 0.3, + 0, + 1.5);
      glVertex3f(- 0.3, - 0.2, + 1.5);
      glVertex3f(- 0.5, - 0.2, + 1.5);

   glEnd();

   /* cabeça */
   glPushMatrix();
   glTranslatef(0, 1, - 2.75);
   glBegin(GL_QUADS);
      glColor3f(0, 0.5, 0);
      glVertex3f(- 0.75, - 0.75, + 0.75);
      glVertex3f(- 0.75, + 0.75, + 0.75);
      glVertex3f(+ 0.75, + 0.75, + 0.75);
      glVertex3f(+ 0.75, - 0.75, + 0.75);

      glVertex3f(- 0.75, - 0.75, + 0.75);
      glVertex3f(- 0.75, + 0.75, + 0.75);
      glVertex3f(- 0.75, + 0.75, - 0.75);
      glVertex3f(- 0.75, - 0.75, - 0.75);

      glVertex3f(+ 0.75, - 0.75, + 0.75);
      glVertex3f(+ 0.75, + 0.75, + 0.75);
      glVertex3f(+ 0.75, + 0.75, - 0.75);
      glVertex3f(+ 0.75, - 0.75, - 0.75);

      glVertex3f(- 0.75, + 0.75, + 0.75);
      glVertex3f(+ 0.75, + 0.75, + 0.75);
      glVertex3f(+ 0.75, + 0.75, - 0.75);
      glVertex3f(- 0.75, + 0.75, - 0.75);

      glVertex3f(- 0.75, - 0.75, + 0.75);
      glVertex3f(+ 0.75, - 0.75, + 0.75);
      glVertex3f(+ 0.75, - 0.75, - 0.75);
      glVertex3f(- 0.75, - 0.75, - 0.75);

      /* bico */
      glColor3f(0.8, 0.8, 0);
      glVertex3f(- 0.75, - 0.75, - 0.75);
      glVertex3f(+ 0.75, - 0.75, - 0.75);
      glVertex3f(+ 0.75, - 0.75, - 1.5);
      glVertex3f(- 0.75, - 0.75, - 1.5);

      glVertex3f(- 0.75, - 0.25, - 0.75);
      glVertex3f(+ 0.75, - 0.25, - 0.75);
      glVertex3f(+ 0.75, - 0.25, - 1.5);
      glVertex3f(- 0.75, - 0.25, - 1.5);

      glVertex3f(- 0.75, - 0.75, - 1.5);
      glVertex3f(- 0.75, - 0.25, - 1.5);
      glVertex3f(- 0.75, - 0.25, - 0.75);
      glVertex3f(- 0.75, - 0.75, - 0.75);

      glVertex3f(+ 0.75, - 0.75, - 1.5);
      glVertex3f(+ 0.75, - 0.25, - 1.5);
      glVertex3f(+ 0.75, - 0.25, - 0.75);
      glVertex3f(+ 0.75, - 0.75, - 0.75);
   glEnd();

   glBegin(GL_TRIANGLES);
      glColor3f(0, 0.5, 0);

      /* penas em cima da cabeça */
      glVertex3f(- 0.25, + 0.75, + 0.75);
      glVertex3f(+ 0.25, + 0.75, + 0.75);
      glVertex3f(+ 0.30, + 0.90, + 0.75);

      glVertex3f(- 0.25, + 0.75, + 0.75);
      glVertex3f(+ 0.25, + 0.75, + 0.75);
      glVertex3f(- 0.30, + 0.90, + 0.75);

      glVertex3f(- 0.25, + 0.75, + 0.75);
      glVertex3f(+ 0.25, + 0.75, + 0.75);
      glVertex3f(0, + 1, + 0.75);
   glEnd();
   glPopMatrix();

   glBegin(GL_TRIANGLES);
      /* rabo */
      glVertex3f(- 0.5, + 1, + 1);
      glVertex3f(+ 0.5, + 1, + 1);
      glVertex3f(+ 0.60, + 1.2, + 1);

      glVertex3f(- 0.5, + 1, + 1);
      glVertex3f(+ 0.5, + 1, + 1);
      glVertex3f(- 0.60, + 1.2, + 1);

      glVertex3f(- 0.5, + 1, + 1);
      glVertex3f(+ 0.5, + 1, + 1);
      glVertex3f(0, + 1.4, + 1);

      /* primeira pata */
      glColor3f(0.8, 0.8, 0);
      glVertex3f(+ 0.5, + 0, + 1.5);
      glVertex3f(+ 0.3, + 0, + 1.5);
      glVertex3f(+ 0.8, - 0.8, + 1.5);

      glVertex3f(+ 0.5, + 0, + 1.5);
      glVertex3f(+ 0.3, + 0, + 1.5);
      glVertex3f(+ 0.1, - 0.8, + 1.5);

      glVertex3f(+ 0.5, + 0, + 1.5);
      glVertex3f(+ 0.3, + 0, + 1.5);
      glVertex3f(+ 0.4, - 1, + 1.5);

      /* segunda pata */
      glVertex3f(- 0.5, + 0, + 1.5);
      glVertex3f(- 0.3, + 0, + 1.5);
      glVertex3f(- 0.8, - 0.8, + 1.5);

      glVertex3f(- 0.5, + 0, + 1.5);
      glVertex3f(- 0.3, + 0, + 1.5);
      glVertex3f(- 0.1, - 0.8, + 1.5);

      glVertex3f(- 0.5, + 0, + 1.5);
      glVertex3f(- 0.3, + 0, + 1.5);
      glVertex3f(- 0.4, - 1, + 1.5);

      /* primeira asa */
      glVertex3f(- 1, + 0.5, - 1);
      glVertex3f(- 1, + 0.5, + 1);
      glVertex3f(- modulo(cos((double) timestep / 25)) * 2 - 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);

      glVertex3f(- 1, + 0, - 1);
      glVertex3f(- 1, + 0, + 1);
      glVertex3f(- modulo(cos((double) timestep / 25)) * 2 - 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);

      glVertex3f(- 1, + 0.5, + 1);
      glVertex3f(- 1, + 0, + 1);
      glVertex3f(- modulo(cos((double) timestep / 25)) * 2 - 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);

      /* segunda asa */
      glVertex3f(+ 1, + 0.5, - 1);
      glVertex3f(+ 1, + 0.5, + 1);
      glVertex3f(+ modulo(cos((double) timestep / 25)) * 2 + 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);

      glVertex3f(+ 1, + 0, - 1);
      glVertex3f(+ 1, + 0, + 1);
      glVertex3f(+ modulo(cos((double) timestep / 25)) * 2 + 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);

      glVertex3f(+ 1, + 0.5, + 1);
      glVertex3f(+ 1, + 0, + 1);
      glVertex3f(+ modulo(cos((double) timestep / 25)) * 2 + 1, sin((double) timestep / 25) * 2 + 0.5, + 0.5);
   glEnd();

   glPopMatrix();
}

void freeNave() {
   free(nave);
   nave = NULL;
}

/*testes*/
Nave * devolveNave() {
   return nave;
}
