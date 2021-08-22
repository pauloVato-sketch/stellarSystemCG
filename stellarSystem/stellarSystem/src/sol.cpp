#include "Sol.hpp"
#include <iostream>

Sol::Sol() {
}

Sol::Sol(Iluminacao iluminacao, GLint x, GLint y) {
	this->iluminacao = iluminacao;
	this->x = x;
	this->y = y;
}
int Sol::desenhaSol(int anguloEsferaY) {

	glRotatef(anguloEsferaY, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glutWireSphere(50.0f, 50, 50);

	return 1;
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