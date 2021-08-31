#include "../headers/camera.h"
#include <stdlib.h>
#include <math.h>

struct Camera {
    float p_x, p_y, p_z;//posicao da camera
    float n_x, n_y, n_z;//vetor fixo na direção do eixo Y
    float v_x, v_y, v_z;//Vetor que define a direção e sentido de visualização, vetor n
    float s_x, s_y, s_z;//vetor resultado do produto vetorial entre o normal e o view, vetor s
};

void updateSvec(Camera* c);

void cross_v_u(float v[], float u[], float output[]);



Camera* init_camera() {
    Camera* c = (Camera*)malloc(sizeof(Camera));
    c->p_x = 0;
    c->p_y = 20;
    c->p_z = 1;

    c->n_x = 0;
    c->n_y = 1;
    c->n_z = 0;

    c->v_x = 0;
    c->v_y = 0;
    c->v_z = 1;

    updateSvec(c);

    return c;
}

void descruct_camera(Camera* c) {
    free(c);
}

float* getCamCenter(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->p_x + (CAM_MV_SPEED * c->v_x);
    pos[1] = c->p_y + (CAM_MV_SPEED * c->v_y);
    pos[2] = c->p_z + (CAM_MV_SPEED * c->v_z);

    return pos;
}

float* getCamPos(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->p_x;
    pos[1] = c->p_y;
    pos[2] = c->p_z;

    return pos;
}

float* getCamNV(Camera* c) {
    float* pos = (float*)malloc(3*sizeof(float));
    pos[0] = c->n_x;
    pos[1] = c->n_y;
    pos[2] = c->n_z;

    return pos;
}


void moveCamFoward(Camera* c) {
    c->p_x += CAM_MV_SPEED * c->v_x;
    //c->p_y += CAM_MV_SPEED * c->v_y;
    c->p_z += CAM_MV_SPEED * c->v_z;
}

void moveCamBackwards(Camera* c) {
    c->p_x += - CAM_MV_SPEED * c->v_x;
    //c->p_y += - CAM_MV_SPEED * c->v_y;
    c->p_z += - CAM_MV_SPEED * c->v_z;
}

void moveCamRight(Camera* c) {
    c->p_x +=  CAM_MV_SPEED * c->s_x;
    //c->p_y +=  CAM_MV_SPEED * c->s_y;
    c->p_z +=  CAM_MV_SPEED * c->s_z;
}

void moveCamLeft(Camera* c) {
    c->p_x +=  - CAM_MV_SPEED * c->s_x;
    //c->p_y +=  - CAM_MV_SPEED * c->s_y;
    c->p_z +=  - CAM_MV_SPEED * c->s_z;
}

void moveCamUp(Camera* c) {
    //Se move no eixo Y
    c->p_x +=  CAM_MV_SPEED * 0;
    c->p_y +=  CAM_MV_SPEED * 1;
    c->p_z +=  CAM_MV_SPEED * 0;
}

void moveCamDown(Camera* c) {
    //Se move no eixo Y
    c->p_x +=  - CAM_MV_SPEED * 0;
    c->p_y +=  - CAM_MV_SPEED * 1;
    c->p_z +=  - CAM_MV_SPEED * 0;
}

void turnCamBack(Camera* c) {
    c->v_x = -  c->v_x;
    //c->v_y = -  c->v_y;
    c->v_z = -  c->v_z;

    c->s_x = - c->s_x;
    //c->s_y = -  c->s_y;
    c->s_z = -  c->s_z;

}


void rotateCamRight(Camera* c) {

    double cos_rot = cos(CAM_ROT_SPEED);
    double sin_rot = sin(CAM_ROT_SPEED);
    //Esse código rotaciona ao redor do eixo Y
    float const3 = (1 - cos_rot)*(c->v_y); 
    //como ta girando ao redor do eixo Y
    // o produto interno resulta somente em c-v_y
    float v_scaled[3] = {c->v_x*cos_rot, 
                            c->v_y*cos_rot, 
                            c->v_z*cos_rot}; 
    
    float yxv[3];
    float y[] = {0, 1, 0};
    float v[] = {c->v_x, c->v_y, c->v_z};

    cross_v_u(y, v, yxv);
    yxv[IX] *= sin_rot;
    yxv[IY] *= sin_rot;
    yxv[IZ] *= sin_rot;

    c->v_x = v_scaled[IX] + yxv[IX] + 0*const3;//o vetor Y é 0 na cord x
    c->v_y = v_scaled[IY] + yxv[IY] + 1*const3;//o vetor Y é 1 na cord y
    c->v_z = v_scaled[IZ] + yxv[IZ] + 0*const3;//o vetor Y é 0 na cord z

    /*
    c->v_x = cos_rot * c->v_x + sin_rot * c->s_x;
    c->v_y = cos_rot * c->v_y + sin_rot * c->s_y;
    c->v_z = cos_rot * c->v_z + sin_rot * c->s_z;
    */
    
    
    updateSvec(c);
} 

void rotateCamLeft(Camera* c) {
    double cos_rot = cos(-CAM_ROT_SPEED);
    double sin_rot = sin(-CAM_ROT_SPEED);
    //Esse código rotaciona ao redor do eixo Y
    float const3 = (1 - cos_rot)*(c->v_y); 
    //como ta girando ao redor do eixo Y
    // o produto interno resulta somente em c-v_y
    float v_scaled[3] = {c->v_x*cos_rot, 
                            c->v_y*cos_rot, 
                            c->v_z*cos_rot}; 
    
    float yxv[3];
    float y[] = {0, 1, 0};
    float v[] = {c->v_x, c->v_y, c->v_z};

    cross_v_u(y, v, yxv);
    yxv[IX] *= sin_rot;
    yxv[IY] *= sin_rot;
    yxv[IZ] *= sin_rot;

    c->v_x = v_scaled[IX] + yxv[IX] + 0*const3;//o vetor Y é 0 na cord x
    c->v_y = v_scaled[IY] + yxv[IY] + 1*const3;//o vetor Y é 1 na cord y
    c->v_z = v_scaled[IZ] + yxv[IZ] + 0*const3;//o vetor Y é 0 na cord z

    /*
    c->v_x = cos_rot*c->v_x + sin_rot* c->s_x;
    c->v_y = cos_rot*c->v_y + sin_rot* c->s_y;
    c->v_z = cos_rot*c->v_z + sin_rot* c->s_z;
    */
    
    
    updateSvec(c);
} 

void rotateCamUp(Camera* c) {

    float cos_nv = c->n_x*c->v_x+ c->n_y*c->v_y + c->n_z*c->v_z;
    float ang = acos(cos_nv);
    float norma = sqrt(c->v_x*c->v_x+ c->v_y*c->v_y + c->v_z*c->v_z);
    

    if(ang >= MAX_GRAD) {
        double cos_rot = cos(CAM_ROT_SPEED);
        double sin_rot = sin(CAM_ROT_SPEED);

        float cons = (1 - cos_rot) * (c->s_x*c->v_x+ c->s_y*c->v_y + c->s_z*c->v_z);
        float v_scaled[3] = {c->v_x*cos_rot, c->v_y*cos_rot, c->v_z*cos_rot};
        float sxv[3];
        float s[] = {c->s_x, c->s_y, c->s_z};
        float v[] = {c->v_x, c->v_y, c->v_z};
        cross_v_u(s, v, sxv);
        sxv[IX] *= sin_rot; 
        sxv[IY] *= sin_rot; 
        sxv[IZ] *= sin_rot; 

        c->v_x = v_scaled[IX] + sxv[IX] + cons*c->s_x;
        c->v_y = v_scaled[IY] + sxv[IY] + cons*c->s_y;
        c->v_z = v_scaled[IZ] + sxv[IZ] + cons*c->s_z;
    }

    
    
}

void rotateCamDown(Camera* c) {
    float cos_nv = c->n_x*c->v_x+ c->n_y*c->v_y + c->n_z*c->v_z;
    float ang = acos(cos_nv);
    

    if (ang <= MIN_GRAD)
    {
        double cos_rot, sin_rot;
        cos_rot = cos(-CAM_ROT_SPEED);
        sin_rot = sin(-CAM_ROT_SPEED);

        float cons = (1 - cos_rot) * (c->s_x*c->v_x+ c->s_y*c->v_y + c->s_z*c->v_z);
        float v_scaled[3] = {c->v_x*cos_rot, c->v_y*cos_rot, c->v_z*cos_rot};
        float sxv[3];
        float s[] = {c->s_x, c->s_y, c->s_z};
        float v[] = {c->v_x, c->v_y, c->v_z};
        cross_v_u(s, v, sxv);
        sxv[IX] *= sin_rot; 
        sxv[IY] *= sin_rot; 
        sxv[IZ] *= sin_rot; 

        c->v_x = v_scaled[IX] + sxv[IX] + cons*c->s_x;
        c->v_y = v_scaled[IY] + sxv[IY] + cons*c->s_y;
        c->v_z = v_scaled[IZ] + sxv[IZ] + cons*c->s_z;
    }
    
   

}

void updateSvec(Camera* c) {
    //atualiza o vetor s da camera
    float* cords = (float*)malloc(3*sizeof(float));

    //calculo do produto vetorial
    c->s_x = (c->v_y*c->n_z) - (c->n_y*c->v_z);
    c->s_y = (c->n_x*c->v_z) - (c->v_x*c->n_z);
    c->s_z = (c->v_x*c->n_y) - (c->n_x*c->v_y);

}

void cross_v_u(float v[], float u[], float output[]) {
    //Faz o produto vetorial VxU e escreve o resultado no vetor output
    output[IX] = (v[IY]*u[IZ]) - (u[IY]*v[IZ]);
    output[IY] = (u[IX]*v[IZ]) - (v[IX]*u[IZ]);
    output[IZ] = (v[IX]*u[IY]) - (u[IX]*v[IY]);

}

void resetOrgDir(Camera* c) {
    //Volta os vetores ao estado inicial
    c->n_x = 0;
    c->n_y = 1;
    c->n_z = 0;

    c->v_x = 0;
    c->v_y = 0;
    c->v_z = 1;

    updateSvec(c);
}