/*
	Autores: Pablo Vasconcelos e Paulo Lopes d. Nascimento
	Data entrega: 26/08
	Motivação: Projeto stellar system

*/
//Incluindo bibliotecas gráficas
#include <GL/glew.h>
#include <GL/freeglut.h>
//Incluindo bibliotecas do C/C++ que serão úteis
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
//Incluindo bibliotecas minhas no projeto
#include "Sol.hpp"
#include "Iluminacao.hpp"

GLint WORLD_SIZE_W=800, WORLD_SIZE_H=600;
GLfloat angle, fAspect, zNear, zFar;
float xMouse = 250, yMouse = 250;
std::vector<Iluminacao> luzes;
Sol sun;
int larguraJanela, alturaJanela;
float anguloEsferaY = 0;

void inicializa() {
	//Inicializa a semente para numero aleatorio
	srand(time(NULL));

	//Função que define a cor de fundo
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// desenho preenchido 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Permite mesclagem de cores e suporte ha texturas com tranparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);


	//Cria o sol
	Iluminacao i;
	luzes.push_back(i);

	luzes[0].setLuzAmbiente({ 0.2,0.2,0.2,1.0 });
	luzes[0].setLuzDifusa({ 0.7,0.7,0.7,1.0 });
	luzes[0].setLuzEspecular({ 1, 1, 1, 1.0 });
	luzes[0].setPosicaoLuz({ 0 , 50.0, 50.0, 1.0 });

	luzes[0].setEspecMaterial(10);
	luzes[0].setEspecularidade({ 1.0, 1.0, 1.0, 1.0 });

	sun = Sol(luzes[0], 0, 0);

	//Habilita o tipo de sombreamento
	glShadeModel(GL_FLAT);

	//Define a refletancia do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun.getIluminacao().getEspecularidade().data());

	//Define a quantidade de brilho refletido do material
	glMateriali(GL_FRONT, GL_SHININESS, sun.getIluminacao().getEspecMaterial());

	//Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sun.getIluminacao().getLuzAmbiente().data());

	//Define os parametros de luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun.getIluminacao().getLuzAmbiente().data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun.getIluminacao().getLuzDifusa().data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun.getIluminacao().getLuzEspecular().data());
	glLightfv(GL_LIGHT0, GL_POSITION, sun.getIluminacao().getPosicaoLuz().data());



	//inicializa variaveis de camera
	angle = 50;
	fAspect = 0;
	zNear = 0.5;
	zFar = 500;
	glutSetCursor(GLUT_CURSOR_NONE);
}

void desenhaBackground() {
	//glClearColor(1,1,1,1);
	//glutSwapBuffers();

}

void desenhaMundo() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Posiciona a câmera de acordo com posição x,y do mouse na janela
	//gluLookAt(1 * (xMouse - larguraJanela / 2) / (larguraJanela / 16), -1 * (yMouse - alturaJanela / 2) / (alturaJanela / 16) + 3, 5,
	//	0, 0, 0,
	//	0, 1, 0);
	glPushMatrix();
	sun.desenhaSol(anguloEsferaY);
	glPopMatrix();
	//glBegin(GL_POLYGON);	// Face posterior
	//glNormal3f(0, 0, 1);  // Normal da face
	//glVertex3f(0, 0, 0);
	//glVertex3f(-50.0, 0,0);
	//glVertex3f(-50.0, -50.0, 0);
	//glVertex3f(0, -50.0, 0);
	//glEnd();


	glutSwapBuffers();

}

void posicionaObservador(int tipoObservador) { //0 - Observador Atrounalta (pode andar livrimente rumo ao desconhecido no espaço) | 1 - Observador astrologo (observa o espaço a uma longa distancia por meio de uma luneta)

	gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);


}

void especificaParametrosVisualizacao() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, zNear, zFar); //zNear representa o corte frontal e o zFar representa o corte final, em outras palavras, representam, juntos, o espaço em Z que nossa camera consegue ver os objetos.

	posicionaObservador(0);
}

//Função responsável por alterar a visão ao redimensionar a janela
void redimensionada(GLsizei width, GLsizei height) {

	larguraJanela = width;
	alturaJanela = height;
	if (height == 0) { //Teste para previnir um divisao por 0 na proporção de aspecto da tela.
		height == 1;
	}

	// left, bottom, right, top
	glViewport(0, 0, width, height);

	fAspect = (GLfloat)width / (GLfloat)height;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	especificaParametrosVisualizacao();

	////Defino as coordenadas do mundo utilizando as constantes definidas
	//glOrtho(0.0, WORLD_SIZE_W, 0.0, WORLD_SIZE_H, -1.0, 3.0);

	////Nova proporção da janela depois de ser redimensionada
	//float windowRatioAspect = ((float)width) / height;

	////Proporção base do mundo
	//float worldAspectRatio = ((float)WORLD_SIZE_W) / WORLD_SIZE_H;
	//std::cout << "raj: " << windowRatioAspect << " ram " << worldAspectRatio << std::endl;

	////Se a proporção do mundo for maior, significa que a tela ficou menor que o mundo, e tratamos como necessário
	//if (windowRatioAspect < worldAspectRatio) {

	//	float hViewport = width / worldAspectRatio;
	//	float yViewport = (height - hViewport) / 2;
	//	glViewport(0, yViewport, width, hViewport);

	//}
	//else if (windowRatioAspect > worldAspectRatio) {
	//	//Se a proporção da janela for maior, significa que a tela ficou maior que o mundo, e tratamos como necessário		
	//	float wViewport = ((float)height) * worldAspectRatio;
	//	float xViewport = (width - wViewport);
	//	glViewport(0, 0, xViewport + wViewport, height);
	//}
	//else {
	//	//Se não houve alteração, apenas defina o viewport com os novos tamanhos
	//	glViewport(0, 0, width, height);
	//}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//Função que opera as entradas do teclado
void teclaPressionada(unsigned char key, int x, int y) {

	switch (key) {
	case 27:      // Tecla "ESC"
		exit(0);  // Sai da aplicação
		break;

	case 32: // Tecla "SPACE"

		break;

	case 83:
	case 115: //S
		//menuSelecao = menuAtivado ? true : false;
		break;

	case 66:
	case 98:
		//menuSelecao = menuSelecao ? false : true;
		break;

	case 80: // 'P;
	case 112: //'p'


	default:
		break;

	}
}



//Função que lida com teclas especiais
void teclaEspecialPressionada(int key, int x, int y) {
	/*switch (key){

		default:
			break;
		}
	}*/
}

void posicionaCamera(int x, int y) {
	xMouse = x;
	yMouse = y;;
	glutPostRedisplay();
}

void rotacionaEsfera() {
	anguloEsferaY += 0.01f;
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//Definindo um objeto de janela para fixar o tamanho da janela inicial
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(275, 50);

	glutCreateWindow("stellarSystem - phoursky");

	glutDisplayFunc(desenhaMundo);
	glutReshapeFunc(redimensionada);
	glutKeyboardFunc(teclaPressionada); //Usado para capturar os eventos de teclas especiais (aquelas que nao geram um valor ASCII)
	glutSpecialFunc(teclaEspecialPressionada);
	glutPassiveMotionFunc(posicionaCamera);
	glutIdleFunc(rotacionaEsfera);
	inicializa();
	glutMainLoop();

	return 0;

}