#pragma once
#include <GL/glut.h>
#include "Iluminacao.hpp"
#include <Iluminacao.hpp>

class Sol {
private:
	GLdouble radius;
	GLint x;
	GLint y;
	GLint idTextura;
	Iluminacao iluminacao;
public:
	Sol();
	Sol(Iluminacao iluminacao, GLint x, GLint y);

	int desenhaSol(int anguloEsferaY);
	GLint getX();
	GLint getY();
	GLint getIdTextura();
	Iluminacao getIluminacao();

	void setX(int valueX);
	void setY(int valueY);
	void setIdTextura(int valueId);
	void setIluminacao(Iluminacao luz);
};