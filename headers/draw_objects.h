/*
* Esse arquivo serve SOMENTE como apoio pro main.c
*/
#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

typedef struct TextureInfo TextureInfo;

/* Guarda todos os ids das texturas carregadas*/
extern TextureInfo** textures;

/*Desenha marcações nos eixos*/
void draw_axis_ticks();

/*Desenha a janela dependendo do estado dela*/
void draw_window();

/*Desenha um objeto qualquer*/
void draw_objects(int index,  float r, float g, float b, int ap_texture);

/*Desenha uma linha*/
void draw_line(float x0, float y0, float z0, float x1, float y1, float z1);

/*Desenha os eixos x, y, z*/
void draw_axis();

/*Desenha um cubo*/
void draw_cube();

/*Desenha o ventilador girando*/
void draw_helix();

/*Desenha a porta dependendo do estado dela*/
void draw_door();

void draw_house();

void draw_bed();

void draw_bookcase();

/*Muda o estado da porta entre aberta/fechada*/
void change_door_state();

/*Muda o estado da janela entre aberta/fechada*/
void change_window_state();

/*
Carrega uma imagem localizada em path para uma textura e associa seu id na posição index
Se o arquivo não puder ser carregado o programa é encerrado
*/
void load_texture(const char* path, int index);

/*
Inicializa o vetor de ID's de texturas
*/
void init_textures_vec();

/*
Aplica uma textura com seu id na posição index do vetor textures
*/
void aply_texture(int index);
#endif