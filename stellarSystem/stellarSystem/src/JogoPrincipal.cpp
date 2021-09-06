/*
	Autores: Pablo Vasconcelos e Paulo Lopes d. Nascimento
	Data entrega: 26/08
	Motivação: Projeto stellar system

*/
//Incluindo bibliotecas gráficas
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL2/SOIL2.h>
//Incluindo bibliotecas do C/C++ que serão úteis
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
//Incluindo bibliotecas minhas no projeto
#include "Iluminacao.hpp"
#include "Planeta.hpp"
#include "Sol.hpp"


//Definições de tamanho da janela
GLint WORLD_SIZE_W=800, WORLD_SIZE_H=600;
int larguraJanela=800, alturaJanela=600;
//Definições de angulo da camera, aspecto e valores de perto/longe para o perspective
GLfloat angle, fAspect, zNear, zFar;
//Ferramentas de rotação
double ano=0;
double dia=0;
//Vector com as luzes sendo 0 para a luz do Sol
std::vector<Iluminacao> luzes;
//Objetos do Sol e dos planetas
Sol sun;
std::vector<Planeta> planetas;
//Angulo do eixo de giro do Sol e planetas em torno do eixo Y ou um pouco inclinado para mais realismo
float anguloEsferaY = 0;
//Array de texturas
std::vector<int> idTexturas;
//Variaveis de controle da camera
enum CAMERAS { MODO_PAISAGEM = 0, MODO_SUPERIOR = 1,MODO_MUSEU = 2};
int modoCamera = MODO_PAISAGEM;

GLuint carregaTextura(const char* arquivo) {
	GLuint idTextura = SOIL_load_OGL_texture(
		arquivo,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	if (idTextura == 0) {
		printf("Erro do SOIL: '%s'\n", SOIL_last_result());
	}

	return idTextura;
}

void loadTextures() {
	idTexturas.push_back(carregaTextura("res/sun.jfif"));
	idTexturas.push_back(carregaTextura("res/mercurio.jpg"));
	idTexturas.push_back(carregaTextura("res/venus.jfif"));
	idTexturas.push_back(carregaTextura("res/earth.jfif"));
	idTexturas.push_back(carregaTextura("res/mars.jfif"));
	idTexturas.push_back(carregaTextura("res/jupiter.jfif"));
	idTexturas.push_back(carregaTextura("res/saturn.jfif"));
	idTexturas.push_back(carregaTextura("res/uranus.jfif"));
	idTexturas.push_back(carregaTextura("res/neptune.jfif"));

}
void criaPlanetas() {
	/*Criação e instanciação dos planetas
	*/
	Planeta mercurio,venus,terra,marte,jupiter,saturno,urano,netuno;
	mercurio = Planeta(-125, -95, 0, 10);
	venus =    Planeta(-130,  80, 0, 20);
	terra =    Planeta(-135,  70, 0, 35);
	marte =    Planeta(-140,  85, 0, 25);
	jupiter =  Planeta(-150,-100, 0, 50);
	saturno =  Planeta(-160, -90, 0, 45);
	urano =    Planeta(-165,  90, 0, 40);
	netuno =   Planeta(-170, 110, 0, 30);
	//Inserindo no array Planetas
	planetas.push_back(mercurio);
	planetas.push_back(venus);
	planetas.push_back(terra);
	planetas.push_back(marte);
	planetas.push_back(jupiter);
	planetas.push_back(saturno);
	planetas.push_back(urano); 
	planetas.push_back(netuno);
}
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

	loadTextures();
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

	luzes[0].setLuzAmbiente({ 1,1,1,1.0 });
	luzes[0].setLuzDifusa({ 0.7,0.7,0.7,1.0 });
	luzes[0].setLuzEspecular({ 1, 1, 1, 1.0 });
	luzes[0].setPosicaoLuz({ 0 , 0, 0, 1.0 });

	luzes[0].setEspecMaterial(60);
	luzes[0].setEspecularidade({ 1.0, 1.0, 1.0, 1.0 });

	sun = Sol(luzes[0], 0, 0, 100);
	
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

	criaPlanetas();

	//inicializa variaveis de camera
	angle = 90;
	fAspect = WORLD_SIZE_W / WORLD_SIZE_H;
	zNear = 5;
	zFar = 2800;
	
}

void desenhaBG() {
	//glClearColor(1,1,1,1);
	//glutSwapBuffers();
}
void posicionaObservador(int tipoObservador) { //0 - Observador Astronauta (pode andar livremente rumo ao desconhecido no espaço) | 1 - Observador astrologo (observa o espaço a uma longa distancia por meio de uma luneta)

		switch (tipoObservador) {
		case MODO_PAISAGEM: {
			gluLookAt(-400, 400, 1200, 0, 0, 0, 1, 1, 0);
			break;
		}
		case MODO_SUPERIOR: {
			gluLookAt(0, 1200, 0, 0, 0, 0, 1, 0, 0);
			break;
		}
	}

}



void especificaParametrosVisualizacao() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, zNear, zFar);
	//zNear representa o corte frontal e o zFar representa o corte final, em outras palavras, representam, juntos, o espaço em Z que nossa camera consegue ver os objetos.

	posicionaObservador(modoCamera);
}
void desenhaMundo() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	especificaParametrosVisualizacao();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTexturas[0]);
	sun.desenhaSol(anguloEsferaY);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < planetas.size();i++) {
		glBindTexture(GL_TEXTURE_2D, idTexturas[i+1]);
		planetas.at(i).desenhaPlaneta(ano, dia);
		
	}
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glutSwapBuffers();

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
	std::cout << fAspect << std::endl;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	especificaParametrosVisualizacao();

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
		modoCamera = (modoCamera == MODO_PAISAGEM) ? MODO_SUPERIOR : MODO_PAISAGEM;
		break;
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
	
	glutPostRedisplay();
}
void atualizaEsfera(int time) {
	
	anguloEsferaY += 0.1f;
	dia = fmod(dia, 360);
	if (modoCamera != MODO_MUSEU) {
		ano = fmod(ano + 0.5, 360);
	}
	
	
	glutPostRedisplay();
	glutTimerFunc(time, atualizaEsfera, time);
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
	glutTimerFunc(16, atualizaEsfera, 16);

	inicializa();
	glutMainLoop();

	return 0;

}