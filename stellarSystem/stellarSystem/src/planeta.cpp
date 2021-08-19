#include "Planeta.hpp" 

int Planeta::desenhaPlaneta() {
	/*A fazer
	*/
	return 1;
}
GLint Planeta::getX() {
	return x;
}
GLint Planeta::getY() {
	return y;
}
GLint Planeta::getIdTextura() {
	return idTextura;
}

void Planeta::setX(int valueX) {
	this->x = valueX;
}
void Planeta::setY(int valueY) {
	this->y = valueY;
}
void Planeta::setIdTextura(int valueId) {
	this->idTextura = valueId;
}
