#pragma once
#include <GL/glut.h>
#include "Iluminacao.hpp"
#include <Iluminacao.hpp>

/* Definição da classe Sol*/
class Sol {
private:
	// Variaveis : raio, posição x , posição y , id da textura utilizada e objeto de iluminação
	GLdouble radius;
	GLint x;
	GLint y;
	GLint idTextura;
	Iluminacao iluminacao;
public:
	//Contrutores sem e com variaveis, respectivamente
	Sol();
	Sol(Iluminacao iluminacao, GLint x, GLint y,GLfloat radius);
	//Função que desenha o Sol
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