#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/obj_import.h"



int VERTEX_COUNT = 0;
Vec3 *VERTICES = NULL;
Vec3 *NORMALS = NULL;
Vec2 *TEX_COORDS = NULL;
Vecs** vecs = NULL;



int load_obj(const char* path) {

	FILE* fp = fopen(path, "r");

	if(!fp)
		return 0;

	char buffer[512] = "";
	int vertex_count = 0;
	int normal_count = 0;
	int tex_coord_count = 0;
	Vec3* vertices = (Vec3*) malloc(MAX_VERTICES*sizeof(Vec3));
	Vec3* normals = (Vec3*) malloc(MAX_VERTICES*sizeof(Vec3));
	Vec2* tex_coords = (Vec2*) malloc(MAX_VERTICES*sizeof(Vec2));

	VERTEX_COUNT = 0;

	while(fgets(buffer, 512, fp)){
		if(buffer[0] == '#') // Comment
			continue;
		
		char* token = strtok(buffer, " ");
	
		if(strcmp(token, "v") == 0){
			// Parse vertex
			vertices[vertex_count].x = atof(strtok(NULL, " "));
			vertices[vertex_count].y = atof(strtok(NULL, " "));
			vertices[vertex_count].z = atof(strtok(NULL, " "));
			vertex_count++;
		}
		else if(strcmp(token, "vn") == 0) {
			// Parse normal vector
			normals[normal_count].x = atof(strtok(NULL, " "));
			normals[normal_count].y = atof(strtok(NULL, " "));
			normals[normal_count].z = atof(strtok(NULL, " "));
			normal_count++;
		}
		else if(strcmp(token, "vt") == 0) {
			// Parse texture coordinate
			tex_coords[tex_coord_count].x = atof(strtok(NULL, " "));
			tex_coords[tex_coord_count].y = -atof(strtok(NULL, " "));
			tex_coord_count++;
		}
		else if(strcmp(token, "f") == 0) {
			// Parse face
			int i;
			for(i = 0;i < 3;i++){
				VERTICES[VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
				TEX_COORDS[VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
				NORMALS[VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
				VERTEX_COUNT++;
			}
		}
	}
	free(vertices);
	free(tex_coords);
	free(normals);

	fclose(fp);

	return 1;
}

void init_vecs() {
	VERTICES = (Vec3*) malloc(MAX_VERTICES*sizeof(Vec3));
	NORMALS = (Vec3*) malloc(MAX_VERTICES*sizeof(Vec3));
	TEX_COORDS = (Vec2*) malloc(MAX_VERTICES*sizeof(Vec2));
}

void load_obj_display(const char* path, int index) {
    int i;

    if(0 <= index < MODEL_QUANT) {
        init_vecs();
        load_obj(path);
        vecs[index]->VERTICES = VERTICES;
        vecs[index]->NORMALS = NORMALS;
        vecs[index]->TEX_COORDS = TEX_COORDS;
        vecs[index]->VERTEX_COUNT = VERTEX_COUNT;
        
    }
    else {
        printf("Indice fora do range permitido: (0, %d)", MODEL_QUANT);
        exit(1);
    }

    
    
}

void init_obj_vecs() {
    int i;
    vecs = (Vecs**)malloc(MODEL_QUANT*sizeof(Vecs*));
    for(i = 0; i < MODEL_QUANT; i++) {
        vecs[i] = (Vecs*)malloc(sizeof(Vecs));
    }
}