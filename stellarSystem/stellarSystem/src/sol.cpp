#include "Sol.hpp"
#include <iostream>

/* Construtor vazio explícito
*/
Sol::Sol() {
}
/*
  Construtor que recebe variaveis de classe
*/
Sol::Sol(Iluminacao iluminacao, GLint x, GLint y,GLfloat radius) {
	this->iluminacao = iluminacao;
	this->x = x;
	this->y = y;
	this->radius = radius;
}
/* Função que desenha o Sol*/
int Sol::desenhaSol(int anguloEsferaY) {

	//Define rotação em torno do eixo Y
	glRotatef(anguloEsferaY, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	// cria uma quádrica
	GLUquadric* quadObj = gluNewQuadric();
	// estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
	// ou GLU_POINT
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	// chama 01 glNormal para cada vértice.. poderia ser
	// GLU_FLAT (01 por face) ou GLU_NONE
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	// chama 01 glTexCoord por vértice
	gluQuadricTexture(quadObj, GL_TRUE);
	// cria os vértices de uma esfera
	gluSphere(quadObj,radius, 200, 200);
	// limpa as variáveis que a GLU usou para criar
	// a esfera
	gluDeleteQuadric(quadObj);
	return 1;
}

/* Getters e Setters */
GLfloat Sol::getRadius() {
	return radius;
}
GLint Sol::getX() {
	return x;
}
GLint Sol::getY() {
	return y;
}
GLint Sol::getIdTextura() {
	return idTextura;
}
Iluminacao Sol::getIluminacao() {
	return iluminacao;
}


void Sol::setRadius(float raio) {
	this->radius = raio;
}
void Sol::setX(int valueX) {
	this->x = valueX;
}
void Sol::setY(int valueY) {
	this->y = valueY;
}
void Sol::setIdTextura(int valueId) {
	this->idTextura = valueId;
}
void Sol::setIluminacao(Iluminacao luz) {
	this->iluminacao = luz;
}

