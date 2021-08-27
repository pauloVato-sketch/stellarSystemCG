#pragma once
#include <GL/glut.h>

class Planeta{
private:
	GLfloat radius;
	GLint x;
	GLint y;
	GLint z;
	GLint idTextura;
public:
	Planeta();
	Planeta(GLint x, GLint y,GLint z,GLfloat radius);
	int desenhaPlaneta(int ano,int dia);
	GLdouble getRadius();
	GLint getX();
	GLint getY();
	GLint getZ();
	GLint getIdTextura();

	void setRadius(float raio);
	void setX(int valueX);
	void setY(int valueY);
	void setZ(int valueZ);
	void setIdTextura(int valueId);
};