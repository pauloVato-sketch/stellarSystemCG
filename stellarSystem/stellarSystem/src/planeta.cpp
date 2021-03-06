#include "Planeta.hpp" 
#include <iostream>
/* Construtor vazio expl?cito
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
/* Fun??o que desenha os Planetas*/
int Planeta::desenhaPlaneta(int ano,int dia) {

	/*Movimento de transla??o baseando-se no ano, fizemos movimento circular, j? que era a forma mais simples, depois at?
	quisemos trocar para o movimento eliptico usando Kepler, por?m j? n?o havia tempo e decidimos deixar assim
	*/
	glRotatef(ano, 0, 1, 0);
	glTranslatef(x, y, z);
	glRotatef(-ano, 0.0, 1.0, 0.0);

	glPushMatrix();
	//Movimento de rota??o baseando-se no dia
		glRotatef(dia, 0.25, 1.0, 0.0);
		GLUquadric* quadObj = gluNewQuadric();
		// estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
		// ou GLU_POINT
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		// chama 01 glNormal para cada v?rtice.. poderia ser
		// GLU_FLAT (01 por face) ou GLU_NONE
		gluQuadricNormals(quadObj, GLU_SMOOTH);
		// chama 01 glTexCoord por v?rtice
		gluQuadricTexture(quadObj, GL_TRUE);
		// cria os v?rtices de uma esfera
		gluSphere(quadObj, radius, 200, 200);
		// limpa as vari?veis que a GLU usou para criar
		// a esfera
	gluDeleteQuadric(quadObj);

	/* Aqui seriam desenhadas as linhas de caminho dos planetas, por?m tive d?vida em como implementar, apenas pontos estavam
	aparecendo, da? deixei comentado como uma ideia (h? alguns coment?rios pelo c?digo com ideias que n?o foram pra frente,
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
