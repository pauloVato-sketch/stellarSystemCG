#pragma once
#include <GL/glut.h>
#include "Iluminacao.hpp"
#include <Iluminacao.hpp>

/* Defini��o da classe Sol*/
class Sol {
private:
	// Variaveis : raio, posi��o x , posi��o y , id da textura utilizada e objeto de ilumina��o
	GLdouble radius;
	GLint x;
	GLint y;
	GLint idTextura;
	Iluminacao iluminacao;
public:
	//Contrutores sem e com variaveis, respectivamente
	Sol();
	Sol(Iluminacao iluminacao, GLint x, GLint y,GLfloat radius);
	//Fun��o que desenha o Sol
	int desenhaSol(int anguloEsferaY);
	//Getters e Setters
	GLfloat getRadius();
	GLint getX();
	GLint getY();
	GLint getIdTextura();
	Iluminacao getIluminacao();

	void setRadius(float raio);
	void setX(int valueX);
	void setY(int valueY);
	void setIdTextura(int valueId);
	void setIluminacao(Iluminacao luz);
};