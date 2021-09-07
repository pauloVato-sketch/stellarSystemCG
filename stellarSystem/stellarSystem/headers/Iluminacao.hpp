#pragma once
#include <GL/glut.h>
#include <vector>
/* Definição da classe de Iluminação*/
class Iluminacao {
	/* Definição das variaveis de instancia usadas para definir uma luz, luz ambiente, difusa, especular,
	posicao, material e especularidade do material*/
private:
	std::vector<GLfloat> luzAmbiente;
	std::vector<GLfloat> luzDifusa;
	std::vector<GLfloat> luzEspecular;
	std::vector<GLfloat> posicaoLuz;
	std::vector<GLfloat> especularidade;
	GLint especMaterial;
	
public:
	/* Getters e Setters*/
	std::vector<GLfloat> getLuzAmbiente();
	std::vector<GLfloat> getLuzDifusa();
	std::vector<GLfloat> getLuzEspecular();
	std::vector<GLfloat> getEspecularidade();
	std::vector<GLfloat> getPosicaoLuz();
	GLint getEspecMaterial();


	void setLuzAmbiente(std::vector<GLfloat> valueAmbient);
	void setLuzDifusa(std::vector<GLfloat> valueDifuse);
	void setLuzEspecular(std::vector<GLfloat> valueSpecular);
	void setEspecularidade(std::vector<GLfloat> valueSpecularity);
	void setPosicaoLuz(std::vector<GLfloat> valuePosLight);
	void setEspecMaterial(GLint valueMaterialSpec);

};