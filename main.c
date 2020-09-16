/*************************************************************************

   >>> MAC0211 (Laboratório de Programação I)
   Professor: Marco Dimas Gubitoso

   Grupo:
    > Caio Rulli Thomaz       - nº USP: 8536106

*************************************************************************/

#include "cenario.h"
#include "nave.h"
#include <GL/glut.h>
#include <stdbool.h>

bool *keyStates;
bool *keySpecialStates;
long cooldown;
extern Nave *nave;
extern unsigned int timestep;

void keyOperations(void) {
  if (keyStates['q'])
    fimDeJogo();
  if (keyStates[' '] && cooldown <= 0) {
    naveAtira();
    cooldown = NAVEFIRERATE;
  }
}

void keySpecialOperations(void) {
  if (keySpecialStates[GLUT_KEY_LEFT])
    nave->vel.x = -0.1;
  else if (keySpecialStates[GLUT_KEY_RIGHT])
    nave->vel.x = 0.1;
  else
    nave->vel.x = 0;
  if (keySpecialStates[GLUT_KEY_UP])
    nave->vel.y = 0.1;
  else if (keySpecialStates[GLUT_KEY_DOWN])
    nave->vel.y = -0.1;
  else
    nave->vel.y = 0;
}

void keyPressed(unsigned char key, int x, int y) { keyStates[key] = true; }

void keyUp(unsigned char key, int x, int y) { keyStates[key] = false; }

void keySpecial(int key, int x, int y) { keySpecialStates[key] = true; }

void keySpecialUp(int key, int x, int y) { keySpecialStates[key] = false; }

void reshape(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50, (GLfloat)width / (GLfloat)height, 1.0, 1025.0);
  glMatrixMode(GL_MODELVIEW);
}

void anda(int n) {
  timestep++;
  cooldown--;
  keyOperations();
  keySpecialOperations();
  atualizaCenario();
  glutTimerFunc(5, anda, 1);
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  int i;
  timestep = 0;
  cooldown = 0;
  keyStates = mallocSafe(256 * sizeof(bool));
  keySpecialStates = mallocSafe(256 * sizeof(bool));

  for (i = 0; i < 256; i++) {
    keyStates[i] = false;
    keySpecialStates[i] = false;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 400);
  carregaCenario();

  glutCreateWindow("O Ataque do Passaro Bionico! Parte Um");

  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyUp);
  glutSpecialFunc(keySpecial);
  glutSpecialUpFunc(keySpecialUp);
  glutDisplayFunc(desenhaCenario);
  glutReshapeFunc(reshape);
  glutTimerFunc(100, anda, 1);

  glutMainLoop();
  free(keyStates);
  free(keySpecialStates);
  return 0;
}
