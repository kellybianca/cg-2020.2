all:	main clean
main:	obj_import.o	camera.o	cam_movement.o	draw_objects.o stb_image.o
	gcc obj_import.o camera.o cam_movement.o draw_objects.o stb_image.o main.c -o main.out -IGL -IGLU -IGLUT -lglut -lGL -lGLU -lm
obj_import.o:
	gcc sources/obj_import.c -c
camera.o:
	gcc sources/camera.c -c
cam_movement.o:
	gcc sources/cam_movement.c -c
draw_objects.o:
	gcc sources/draw_objects.c -c
stb_image.o:
	gcc sources/stb_image.c -c
clean:
	rm -rf *.o

