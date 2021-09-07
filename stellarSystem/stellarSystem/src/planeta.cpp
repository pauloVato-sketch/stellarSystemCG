#include "Planeta.hpp" 
#include <iostream>
/* Construtor vazio explícito
*/
Planeta::Planeta() {
}
/*
  Construtor que recebe variaveis de classe
*/
Planeta::Planeta(GLint x, GLint y, GLint z,GLfloat radius) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->radius = radius;
}
/* Função que desenha os Planetas*/
int Planeta::desenhaPlaneta(int ano,int dia) {

	/*Movimento de translação baseando-se no ano, fizemos movimento circular, já que era a forma mais simples, depois até
	quisemos trocar para o movimento eliptico usando Kepler, porém já não havia tempo e decidimos deixar assim
	*/
	glRotatef(ano, 0, 1, 0);
	glTranslatef(x, y, z);
	glRotatef(-ano, 0.0, 1.0, 0.0);

	glPushMatrix();
	//Movimento de rotação baseando-se no dia
		glRotatef(dia, 0.25, 1.0, 0.0);
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
		gluSphere(quadObj, radius, 200, 200);
		// limpa as variáveis que a GLU usou para criar
		// a esfera
	gluDeleteQuadric(quadObj);

	/* Aqui seriam desenhadas as linhas de caminho dos planetas, porém tive dúvida em como implementar, apenas pontos estavam
	aparecendo, daí deixei comentado como uma ideia (há alguns comentários pelo código com ideias que não foram pra frente,
	mas que nas ferias eu, Paulo, irei terminar)
	
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
		glVertex3f(x, y, z);
		glVertex3f(x + 1, y + 1, z + 1);
	glEnd();*/

	glPopMatrix();
	
	glutPostRedisplay();

	return 1;
}

/* Getters e Setters*/
GLdouble Planeta::getRadius() {
	return radius;
}
GLint Planeta::getX() {
	return x;
}
GLint Planeta::getY() {
	return y;
}
GLint Planeta::getZ() {
	return z;
}
GLint Planeta::getIdTextura() {
	return idTextura;
}


void Planeta::setRadius(float raio) {
	this->radius = raio;
}
void Planeta::setX(int valueX) {
	this->x = valueX;
}
void Planeta::setY(int valueY) {
	this->y = valueY;
}
void Planeta::setZ(int valueZ) {
	this->z = valueZ;
}
void Planeta::setIdTextura(int valueId) {
	this->idTextura = valueId;
}
