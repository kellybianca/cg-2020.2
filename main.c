#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "headers/camera.h"
#include "headers/obj_import.h"
#include "headers/cam_movement.h"
#include "headers/draw_objects.h"
#include "headers/stb_image.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

//#define DEBUG
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

float *cam_pos;
float *cam_center;
float *cam_nv;

void *cam = NULL;

void display();

void setup_lighting();

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("CG - Kitchen");

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthRange(0.0f, 1.0f);

    setup_lighting();

    cam = (Camera *)init_camera();
    init_obj_vecs();
    init_textures_vec();


    load_obj_display("./models/geladeira.obj", 6);
    load_obj_display("./models/ventilador/helice.obj", 7);
    load_obj_display("./models/ventilador/base_sem_helice.obj", 8);
    load_obj_display("./models/lixinho.obj", 11);

    load_obj_display("./models/portaFechada.obj", 13);

    load_obj_display("./models/janelaFechada.obj", 14);

    load_obj_display("./models/mesa.obj", 15);

    load_obj_display("./models/casa/chao.obj", 17);
    load_obj_display("./models/casa/teto.obj", 18);
    load_obj_display("./models/casa/paredecomporta.obj", 19);
    load_obj_display("./models/casa/paredecomum.obj", 20);
    load_obj_display("./models/casa/paredecomjanela.obj", 21);

    load_obj_display("./models/janela/base.obj", 22);
    load_obj_display("./models/janela/janela.obj", 23);
    load_obj_display("./models/janela/janela2.obj", 24);

    load_obj_display("./models/pia.obj", 25);

    load_obj_display("./models/estante/estante.obj", 28);
    load_obj_display("./models/estante/taca.obj", 29);
    load_obj_display("./models/luminaria.obj", 30);
    load_obj_display("./models/luminaria2.obj", 31);

    load_texture("textures/cores.jpg", 0);
    load_texture("textures/container.jpg", 1);
    load_texture("textures/pisoceramica.jpg", 2);
    load_texture("textures/papeldeparede2.jpg", 3);
    load_texture("textures/geladeira.jpg", 5);
    load_texture("textures/textura_pia.jpg", 6);
    load_texture("textures/texturademadeira.jpg", 7);
    load_texture("textures/porta.jpg", 8);

    glutDisplayFunc(display);
    glutKeyboardFunc(moveCam);
    glutSpecialFunc(moveCamSpec);
    glutMotionFunc(mouse_func);
    glutPassiveMotionFunc(pass_mouse_func);
    glutMainLoop();
    return 0;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int i;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT,
                   0.001f, 1000.0f);

    cam_pos = getCamPos(cam);
    cam_center = getCamCenter(cam);
    cam_nv = getCamNV(cam);

    gluLookAt(cam_pos[IX], cam_pos[IY], cam_pos[IZ], cam_center[IX], cam_center[IY],
              cam_center[IZ], cam_nv[IX], cam_nv[IY], cam_nv[IZ]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //ventilador
    glPushMatrix();
    glTranslatef (-18, 71, -15);
    glScalef(4.0, 8.0, 4.0);
    glRotatef(-180, 90, 0, 90);
    draw_helix();
    glPopMatrix();
    
    //casa
    draw_house();

    //pia
    draw_sink();

    //estante
    glPushMatrix();
    draw_bookcase();
    glPopMatrix();

    //geladeira
    draw_fridge();

    //janela
    draw_window();

    //lixeira
    glPushMatrix();
    glTranslatef(40, 1.5, -66);
    glScalef(3.0, 3.0, 3.0);
    draw_objects(11, 0.5,  0.5, 0.5, 1);
    glPopMatrix();

    //porta
    glPushMatrix();
    draw_door();
    glPopMatrix();

    //mesa
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glScalef(3.5, 3.5, 3.5);
    glRotatef(-90, 0, 1, 0);
    draw_objects(15, 0.8, 0.8, 0.6, 1);
    glPopMatrix();

    //luminaria
    glPushMatrix();
    glTranslatef(0, 16, 0);
    glScalef(7.0, 7.0, 7.0);
    draw_objects(30, 1, 1, 1, 1);
    glPopMatrix();

    //quadro
    glPushMatrix();
    glTranslatef ( 0 ,30 , -73.7 ) ;
    glScalef(1.5, 1.5, 1.5);
    draw_objects(3, 0.1, 0.5, 0.8, 0);
    glPopMatrix();

    glPushMatrix();
    glEnable( GL_TEXTURE_2D ); 
    glTranslatef ( 1.75 ,30.5 , -71 ) ;
    //Desenha a imagem que vai no quadro
    aply_texture(0);
    glScalef(10.0, 10, 1.0);
    draw_cube();
    glDisable( GL_TEXTURE_2D ); 
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

void setup_lighting()
{
    float mat_specular[] = {1.0f, 1.0f, 1.0f}; //branco
    float light_position[] = {0.0f, 18.0f, 0.0f, 1.0f};
    float light_diffuse[] = {0.5f, 0.5f, 0.5f}; // lanterna clareando o ambiente

    //luminaria
    glMaterialfv(GL_LIGHT1, GL_SPECULAR, mat_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

    //spot  
    float spot_direction[] = {-0.7f, -0.5f, 0.0f};
    float spot_cutoff[] = {30.0f};
    float spot_position[] = {60, 15, 8, 1.0};
    float spot_difuse[] = {1.0, 1.0, 1.0}; // luz branca do spot

    glLightfv(GL_LIGHT0, GL_DIFFUSE, spot_difuse);
    glLightfv(GL_LIGHT0, GL_POSITION, spot_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glEnable(GL_COLOR_MATERIAL);
}