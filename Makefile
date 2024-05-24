all:
	cc -o donut src/main.c -lGL -lGLU -lglut -lm

vbo:
	cc -o donutvbo src/mainvbo.c -lGL -lGLU -lglut -lm
