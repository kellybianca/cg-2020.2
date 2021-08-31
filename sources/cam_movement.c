#include "../headers/cam_movement.h"
#include "../headers/draw_objects.h"
#include "../headers/camera.h"
#include <GL/gl.h>
#include <GL/glut.h>

int old_x = 0;
int old_y = 0;



void moveCam(unsigned char key, int x, int y) {

    switch(key) {
        case 'w':
            moveCamFoward((Camera*)cam);
            break;
        case 's':
            moveCamBackwards((Camera*)cam);
            break;
        case 'a':
            moveCamLeft((Camera*)cam);
            break;     
        case 'd':
            moveCamRight((Camera*)cam);
            break;
        case 'z':
            turnCamBack((Camera*)cam);
            break;
        case 'f':
            moveCamDown((Camera*)cam);
            break;
        case 'r':
            moveCamUp((Camera*)cam);
            break;      
        case '/':
            resetOrgDir((Camera*)cam);
            break;  
        case 'o':
            change_door_state();
            break;
        case 'p':
            change_window_state();
            break;
    }
    glutPostRedisplay();
    

}

void moveCamSpec(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:
           rotateCamUp((Camera*)cam);
           break;
        case GLUT_KEY_DOWN:
            rotateCamDown((Camera*)cam);
            break;

        case GLUT_KEY_LEFT:
            rotateCamLeft((Camera*)cam);
            break;
        case GLUT_KEY_RIGHT:
            rotateCamRight((Camera*)cam);
            break;
    }
    glutPostRedisplay();
    
    
}

void mouse_func( int x, int y) {
    int diff_x = old_x - x;
    int diff_y = old_y - y;
    old_x = x;
    old_y = y;
    int i;

    if(diff_x > 0) {
        rotateCamRight((Camera*)cam);
    }
    if(diff_x < 0) {
        rotateCamLeft((Camera*)cam);
    }

    if(diff_y > 0) {
        rotateCamUp((Camera*)cam);
    }
    if(diff_y < 0) {
        rotateCamDown((Camera*)cam);
    }
    glutPostRedisplay();
}

void pass_mouse_func(int x, int y) {
    old_x = x;
    old_y = y;
}
