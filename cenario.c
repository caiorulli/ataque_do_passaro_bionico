/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "cenario.h"
#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>

#include "objeto.h"
#include "nave.h"
#include "defesa.h"
#include "tiro.h"
#include "dinamico.h"

unsigned int timestep;
unsigned int pontuacao;
extern Nave *nave;

/* Inicialização */
void carregaCenario() {
   criaNave();
   criaListaDefesa();
   criaListaTiro();
   pontuacao = 0;
}

/* Laço de atualização dos elementos */
void atualizaCenario() {
  atualizaNave();
  atualizaListaTiro();
  atualizaListaDefesa();
  insereDefesa(geraDefesaAleatoria(0.005));
  defesasAtiram(timestep);
  calculaDanoNave();
  naveDefesaColidiram();
  calculaDanoDefesas();
  if (!naveEstaViva())
    fimDeJogo();
}

void desenhaCenario(void) {
  GLfloat i;
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 25,
             0, 0, 0,
             0, 1, 0);

  desenhaNave();
  desenhaDefesas();
  desenhaTiros();

  /* chão */
  glColor3f(1, .5, 0);
  glBegin(GL_QUADS);
  glVertex3f(-1000, -10, 25);
    glVertex3f(1000, -10, 25);
    glVertex3f(1000, -10, -1000);
    glVertex3f(-1000, -10, -1000);
  glEnd();
  glColor3f(0.4, 0.4, 0.4);
  glBegin(GL_QUADS); 
    glVertex3f(-10, -9.9, 25);
    glVertex3f(10, -9.9, 25);
    glVertex3f(10, -9.9, -1000);
    glVertex3f(-10, -9.9, -1000);
  glEnd();
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS);
  for (i = -1000; i < 25; i += 15) {
    glVertex3f(-1, -9.8, i + (timestep % 15));
    glVertex3f(1, -9.8, i + (timestep % 15));
    glVertex3f(1, -9.8, i + (timestep % 15) - 10);
    glVertex3f(-1, -9.8, i + (timestep % 15) - 10);
  }
  glEnd(); 

  /* céu */
  glColor3f(0.3, 0.3, 1);
  glBegin(GL_QUADS);
    glVertex3f(-1000, -1000, -999);
    glVertex3f(1000, -1000, -999);
    glVertex3f(1000, 1000, -1000);
    glVertex3f(-1000, 1000, -1000);
  glEnd();

  /* barra de vida */
  glBegin(GL_QUADS);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-14, 9, 1);
    glVertex3f(-14, 8, 1);
    glVertex3f(-9, 8, 1);
    glVertex3f(-9, 9, 1);

    glColor3f(0, 1, 1);
    glVertex3f(-14, 9, 1.0001);
    glVertex3f(-14, 8, 1.0001);
    glVertex3f(-14 + 5 * ((double) nave->hp / NAVEHP), 8, 1.0001);
    glVertex3f(-14 + 5 * ((double) nave->hp / NAVEHP), 9, 1.0001);
  glEnd();

  glutSwapBuffers();
  glFlush();
}

/* Protocolo de finalização do jogo */
void fimDeJogo() {
  freeNave();
  freeListaDefesa();
  freeListaTiro();
  printf("Pontuacao: %d\nDistancia percorrida: %d\n", pontuacao, timestep);
  exit(0);
}