/*
* Esse arquivo serve SOMENTE como apoio pro main.c
*/

#ifndef CAM_MOV_H
#define CAM_MOV_H
#define PI 3.14
#define RAD_TO_GRAD(c) c*180/PI

extern void* cam;

/*Funções de callback da GLUT*/

/*Movimentar a camera no teclado e outras opções*/
void moveCam(unsigned char key, int x, int y);

/* Movimentar a camera com teclas especiais do teclado*/
void moveCamSpec(int key, int x, int y);

/*Função de motion do mouse*/
void mouse_func( int x, int y);

/*Função passiva do mouse*/
void pass_mouse_func(int x, int y);



#endif