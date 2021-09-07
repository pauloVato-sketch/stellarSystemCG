#pragma once
#include <GL/glut.h>

/* Definição da classe Planeta*/
class Planeta{
private:
	// Variaveis : raio, posição x , posição y , posição x e id da textura 
	GLfloat radius;
	GLint x;
	GLint y;
	GLint z;
	GLint idTextura;
public:
	//Contrutores sem e com variaveis, respectivamente
	Planeta();
	Planeta(GLint x, GLint y,GLint z,GLfloat radius);
	//Função que desenha o Sol
	int desenhaPlaneta(int ano,int dia);
	//Getters e Setters
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