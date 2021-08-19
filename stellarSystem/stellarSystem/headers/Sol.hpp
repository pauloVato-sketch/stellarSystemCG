#pragma once
#include <GL/glut.h>

class Sol {
private:
	GLdouble radius;
	GLint x;
	GLint y;
	GLint idTextura;
public:
	int desenhaSol();
	GLint getX();
	GLint getY();
	GLint getIdTextura();

	void setX(int valueX);
	void setY(int valueY);
	void setIdTextura(int valueId);
};