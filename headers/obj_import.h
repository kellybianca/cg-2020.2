#define MAX_VERTICES 200000
#define MODEL_QUANT 50

typedef struct Vec2 Vec2;

typedef struct Vec3 Vec3;

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

typedef struct Vecs Vecs;

struct Vecs {
    Vec3 *VERTICES;
    Vec3 *NORMALS;
    Vec2 *TEX_COORDS;
    int VERTEX_COUNT;
};

/*Inicializados em obj_import.c*/
extern int VERTEX_COUNT;
extern Vec3 *VERTICES;
extern Vec3 *NORMALS;
extern Vec2 *TEX_COORDS;
extern Vecs** vecs;


int load_obj(const char* path);

void init_vecs();


void load_obj_display(const char* path, int index);
void init_obj_vecs();

