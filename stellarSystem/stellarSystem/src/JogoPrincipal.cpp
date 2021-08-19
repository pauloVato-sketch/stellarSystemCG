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

GLint WORLD_SIZE_W=800, WORLD_SIZE_H=600;
Sol sun;

void inicializa(){
	//Inicializa a semente para numero aleatorio
	srand(time(NULL));

	//Função que define a cor de fundo
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// desenho preenchido 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Permite mesclagem de cores e suporte ha texturas com tranparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void desenhaMundo() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sun.desenhaSol();
}
//Função responsável por alterar a visão ao redimensionar a janela
void redimensionada(int width, int height) {
	// left, bottom, right, top
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Defino as coordenadas do mundo utilizando as constantes definidas
	glOrtho(0.0, WORLD_SIZE_W, 0.0, WORLD_SIZE_H, -1.0, 3.0);

	//Nova proporção da janela depois de ser redimensionada
	float windowRatioAspect = ((float)width) / height;
	//Proporção base do mundo
	float worldAspectRatio = ((float)WORLD_SIZE_W) / WORLD_SIZE_H;
	std::cout << "raj: " << windowRatioAspect << " ram " << worldAspectRatio << std::endl;
	//Se a proporção do mundo for maior, significa que a tela ficou menor que o mundo, e tratamos como necessário
	if (windowRatioAspect < worldAspectRatio) {

		float hViewport = width / worldAspectRatio;
		float yViewport = (height - hViewport) / 2;
		glViewport(0, yViewport, width, hViewport);

	}
	else if (windowRatioAspect > worldAspectRatio) {
		//Se a proporção da janela for maior, significa que a tela ficou maior que o mundo, e tratamos como necessário		
		float wViewport = ((float)height) * worldAspectRatio;
		float xViewport = (width - wViewport);
		glViewport(0, 0, xViewport + wViewport, height);
	}
	else {
		//Se não houve alteração, apenas defina o viewport com os novos tamanhos
		glViewport(0, 0, width, height);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Função que opera as entradas do teclado
void teclaPressionada(unsigned char key, int x, int y){

	switch (key){
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
/*
	Função que lida com teclas especiais
*/
void teclaEspecialPressionada(int key, int x, int y){
		/*switch (key){
			
			default:
				break;
			}
		}*/
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

	inicializa();
	glutMainLoop();

	return 0;

}