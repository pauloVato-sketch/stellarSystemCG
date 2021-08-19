#include "Iluminacao.hpp"
#include <vector>

std::vector<GLfloat> Iluminacao::getLuzAmbiente() {
	return this->luzAmbiente;
}
std::vector<GLfloat> Iluminacao::getLuzDifusa() {
	return this->luzDifusa;
}
std::vector<GLfloat> Iluminacao::getLuzEspecular() {
	return this->luzEspecular;
}
std::vector<GLfloat> Iluminacao::getEspecularidade() {
	return this->especularidade;
}
std::vector<GLfloat> Iluminacao::getPosicaoLuz() {
	return this->posicaoLuz;
}
GLint Iluminacao::getEspecMaterial() {
	return this->especMaterial;
}

void Iluminacao::setLuzAmbiente(std::vector<GLfloat> valueAmbient) {
	this->luzAmbiente = valueAmbient;
}
void Iluminacao::setLuzDifusa(std::vector<GLfloat> valueDifuse) {
	this->luzDifusa = valueDifuse;
}
void Iluminacao::setLuzEspecular(std::vector<GLfloat> valueSpecular) {
	this->luzEspecular = valueSpecular;
}
void Iluminacao::setEspecularidade(std::vector<GLfloat> valueSpecularity) {
	this->especularidade = valueSpecularity;
}
void Iluminacao::setPosicaoLuz(std::vector<GLfloat> valuePosLight) {
	this->posicaoLuz = valuePosLight;
}
void Iluminacao::setEspecMaterial(GLint valueMaterialSpec) {
	this->especMaterial = valueMaterialSpec;
}