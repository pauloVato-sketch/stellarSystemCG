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
double ano = 0, dia = 0, anoPausado = 0;
//Vector com as luzes sendo 0 para a luz do Sol
std::vector<Iluminacao> luzes;
//Objetos do Sol e dos planetas
Sol sun;
std::vector<Planeta> planetas;
//Angulo do eixo de giro do Sol e planetas em torno do eixo Y ou um pouco inclinado para mais realismo
float anguloEsferaY = 0;
//Vector de texturas
std::vector<int> idTexturas;
//Variaveis de controle da camera
enum CAMERAS { MODO_PAISAGEM = 0, MODO_SUPERIOR = 1,MODO_MUSEU = 2};
int modoCamera = MODO_PAISAGEM;
//Variavel que coordena o modo museu
//"  0 - SOL, 1 - MERCURIO, 2 - VENUS, 3 - TERRA, 4 - MARTE, 5 - JUPITER, 6 - SATURNO, 7 - URANO, 8 - NETUNO" 
int planetaAtual = 0;
//Variavel que liga/desliga a luz do Sol
bool luzLigada = true;

/* Função que carrega textura usando SOIL2*/
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
/* Função que carrega todas as texturas e salva no vector designado*/
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

/* Função que cria e instancia os planetas, além de colocá-los no seu respectivo vector*/
void criaPlanetas() {
	/*Criação e instanciação dos planetas*/
	Planeta mercurio,venus,terra,marte,jupiter,saturno,urano,netuno;
	//                  x     y   z  raio  correspondencia com o array de textura
	mercurio = Planeta(-125, -95, 0,  10); //0 - 1
	venus =    Planeta(-130,  80, 0,  20); //1 - 2
	terra =    Planeta(-135,  70, 0,  35); //2 - 3
	marte =    Planeta(-140,  85, 0,  25); //3 - 4
	jupiter =  Planeta(-150,-100, 0,  50); //4 - 5 
	saturno =  Planeta(-160, -90, 0,  45); //5 - 6
	urano =    Planeta(-165,  90, 0,  40); //6 - 7
	netuno =   Planeta(-170, 110, 0,  30); //7 - 8
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

/* Função que iniciliza o programa*/
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

	/* Chamo a função que constroi os planetas*/
	criaPlanetas();

	//inicializa variaveis de camera
	angle = 90;
	fAspect = WORLD_SIZE_W / WORLD_SIZE_H;
	zNear = 5;
	zFar = 2800;
	
}

void desenhaBG() {
	/*Aqui seria o background das estrelas, porém não tivemos tempo devido as outras materias estarem no pé, 
	e queriamos tentar a skybox porém reconhecemos que não teria como*/
}

/* Função que coordena qual câmera está ativa no momento
MODO_PAISAGEM é o padrão, e está levemente na diagonal para dar um efeito de longitude, 
MODO_SUPERIOR é o segundo modo, este modo está totalmente no eixo Y, acima do sistema solar e por fim 
MODO_MUSEU que é o modo que possibilita iterar pelos planetas de bem perto e vê-los rotacionar em torno de seu próprio eixo
*/
void posicionaObservador(int tipoObservador) { 
		/* Switch que coordena qual tipo de camera está sendo utilizada, utilizando  gluLookAt para focar nos planetas na função MUSEU*/
		switch (tipoObservador) {
			case MODO_PAISAGEM: {
				gluLookAt(-400, 400, 1200, 0, 0, 0, 1, 1, 0);
				break;
			}
			case MODO_SUPERIOR: {
				gluLookAt(0, 1200, 0, 0, 0, 0, 1, 0, 0);
				break;
			}
			case MODO_MUSEU: {
				switch (planetaAtual) {
					case 0: {
						gluLookAt(0, 0, 180, 0, 0, 0, 0, 1, 0);
						break;
					}
					case 1: {
						//Focalizando o xyz dos planetas e afastando o valor do raio para visualizar
						gluLookAt(planetas.at(0).getX() + 10, planetas.at(0).getY() + 10, planetas.at(0).getZ() + 10, 
							planetas.at(0).getX(), planetas.at(0).getY(),planetas.at(0).getZ(), 0, 1, 0);
						break;
					}
					case 2: {
						gluLookAt(planetas.at(1).getX() + 20, planetas.at(1).getY() + 20, planetas.at(1).getZ()+20,
							planetas.at(1).getX(), planetas.at(1).getY(), planetas.at(1).getZ(), 0, 1, 0);
						break;
					}
					case 3: {
						gluLookAt(planetas.at(2).getX() + 35, planetas.at(2).getY() + 35, planetas.at(2).getZ() + 35,
							planetas.at(2).getX(), planetas.at(2).getY(), planetas.at(2).getZ(), 0, 1, 0);
						break;
					}
					case 4: {
						gluLookAt(planetas.at(3).getX() + 25, planetas.at(3).getY() + 25, planetas.at(3).getZ() + 25,
							planetas.at(3).getX(), planetas.at(3).getY(), planetas.at(3).getZ(), 0, 1, 0);
						break;
					}
					case 5: {
						gluLookAt(planetas.at(4).getX() + 50, planetas.at(4).getY() + 50, planetas.at(4).getZ() + 50, 
							planetas.at(4).getX(), planetas.at(4).getY(), planetas.at(4).getZ(), 0, 1, 0);
						break;
					}
					case 6: {
						gluLookAt(planetas.at(5).getX() + 45, planetas.at(5).getY() + 45, planetas.at(5).getZ() + 45, 
							planetas.at(5).getX(), planetas.at(5).getY(), planetas.at(5).getZ(), 0, 1, 0);
						break;
					}
					case 7: {
						gluLookAt(planetas.at(6).getX() + 40, planetas.at(6).getY() + 40, planetas.at(6).getZ() + 40, 
							planetas.at(6).getX(), planetas.at(6).getY(), planetas.at(6).getZ(), 0, 1, 0);
						break;
					}
					case 8: {
						gluLookAt(planetas.at(7).getX() + 30, planetas.at(7).getY() + 30, planetas.at(7).getZ() + 30,
							planetas.at(7).getX(), planetas.at(7).getY(), planetas.at(7).getZ(), 0, 1, 0);
						break;
					}

				}
			}
	}

}
/* Função que prepara a chamada para a câmera do LookAt, utilizando o gluPerspective*/
void especificaParametrosVisualizacao() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, fAspect, zNear, zFar);
	//zNear representa o corte frontal e o zFar representa o corte final, em outras palavras, representam, juntos, o espaço em Z que nossa camera consegue ver os objetos.

	posicionaObservador(modoCamera);
}

/* Função que desenha o mundo*/
void desenhaMundo() {
	//Cria o sol e sua Iluminação
	Iluminacao i;
	luzes.push_back(i);
	//Define os valores para as variáveis da iluminação
	luzes[0].setLuzAmbiente({1,1,1,1.0 });
	luzes[0].setLuzDifusa({ 0.7,0.7,0.7,1.0 });
	luzes[0].setLuzEspecular({ 1, 1, 1, 1.0 });
	luzes[0].setPosicaoLuz({ 0 , 0, 0, 1.0 });

	luzes[0].setEspecMaterial(60);
	luzes[0].setEspecularidade({ 1.0, 1.0, 1.0, 1.0 });

	sun = Sol(luzes[0], 0, 0, 100);

	//Habilita o tipo de sombreamento
	glShadeModel(GL_FLAT);

	//Define a reflectividade do material
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun.getIluminacao().getEspecularidade().data());

	//Define a quantidade de brilho refletido do material
	glMateriali(GL_FRONT, GL_SHININESS, sun.getIluminacao().getEspecMaterial());

	//Ativa o uso da luz ambiente -- COMENTADO POIS QUERIAMOS APENAS A LUZ PONTUAL, QUE SERIA A LUZ DO SOL NO NOSSO SISTEMA
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sun.getIluminacao().getLuzAmbiente().data());

	//Define os parametros de luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun.getIluminacao().getLuzAmbiente().data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun.getIluminacao().getLuzDifusa().data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun.getIluminacao().getLuzEspecular().data());
	glLightfv(GL_LIGHT0, GL_POSITION, sun.getIluminacao().getPosicaoLuz().data());

	//Limpa o buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*Tentamos colocar instruções de controle na tela além do console
	informacoesTela();
	*/

	/* Chama função da câmera*/
	especificaParametrosVisualizacao();
	
	/* Volta com o matrixMode para MODELVIEW, já que na câmera é utilizado o PROJECTION*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* Apaga a luz baseado no input
	*/
	if (luzLigada) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		//Se for o MODO_MUSEU, desenha apenas o Sol/planeta selecionado e sua rotação, para ficar melhor na câmera
		if (modoCamera == MODO_MUSEU) {
			switch (planetaAtual) {
				case 0: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						sun.desenhaSol(anguloEsferaY);
					glPopMatrix();
					break;
				}
				case 1: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 2: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 3: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 4: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 5: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 6: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 7: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
				case 8: {
					glPushMatrix();
						glBindTexture(GL_TEXTURE_2D, idTexturas[planetaAtual]);
						planetas.at(planetaAtual - 1).desenhaPlaneta(ano, dia);
					glPopMatrix();
					break;
				}
			}
		}else if (modoCamera != MODO_MUSEU) {
			//Se for qualquer uma das outras câmeras, desenha o Sol e todos os planetas normalmente
			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, idTexturas[0]);
				sun.desenhaSol(anguloEsferaY);
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			for (int i = 0; i < planetas.size(); i++) {
				glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, idTexturas[i + 1]);
					planetas.at(i).desenhaPlaneta(ano, dia);
				glDisable(GL_TEXTURE_2D);
			}	
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	especificaParametrosVisualizacao();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Imprime a ajuda no console
void imprimirAjudaConsole(void)
{
	std::cout << "Ajuda:" << std::endl;
	std::cout << "  Aperte 'p' para alternar o layout da camera, que gira na seguinte ordem:" << std::endl
		<< "  CAMERA INICIAL : MODO PAISAGEM -> MODO SUPERIOR -> MODO MUSEU" << std::endl
		<< "  Ao chegar no MODO MUSEU, clique nos numeros 0-8 para iterar pelos astros na sequencia:" << std::endl
		<< "  0 - SOL, 1 - MERCURIO, 2 - VENUS, 3 - TERRA, 4 - MARTE, 5 - JUPITER, 6 - SATURNO, 7 - URANO, 8 - NETUNO" << std::endl;
}

//Função que opera as entradas do teclado
void teclaPressionada(unsigned char key, int x, int y) {

	switch (key) {
	case 27:      // Tecla "ESC"
		exit(0);  // Sai da aplicação
		break;
	case 32: {	  // Tecla SPACE
		if (luzLigada) luzLigada = false;
		else luzLigada = true;//Apaga a luz do Sol

		break;
	}
	case 48: // Números para iterar pelos planetas no MODO MUSEU - 0 - SOL
		planetaAtual = 0;
		break;
	case 49: // Números para iterar pelos planetas no MODO MUSEU - 1 - MERCURIO
		planetaAtual = 1;
		break;
	case 50: // Números para iterar pelos planetas no MODO MUSEU - 2 - VENUS
		planetaAtual = 2;
		break;
	case 51: // Números para iterar pelos planetas no MODO MUSEU - 3 - TERRA
		planetaAtual = 3;
		break;
	case 52: // Números para iterar pelos planetas no MODO MUSEU - 4 - MARTE
		planetaAtual = 4;
		break;
	case 53: // Números para iterar pelos planetas no MODO MUSEU - 5 - JUPITER
		planetaAtual = 5;
		break;
	case 54: // Números para iterar pelos planetas no MODO MUSEU - 6 - SATURNO
		planetaAtual = 6;
		break;
	case 55: // Números para iterar pelos planetas no MODO MUSEU - 7 - URANO
		planetaAtual = 7;
		break;
	case 56: // Números para iterar pelos planetas no MODO MUSEU - 8 - NETUNO
		planetaAtual = 8;
		break;
	

	case 72:  //H 
	case 104: //h
		imprimirAjudaConsole(); // Exibe ajuda no console
		break;

	case 80: // 'P;
	case 112: //'p'
		/* Itera pelas câmeras ao apertar 'p', na ordem MODO_PAISAGEM -> MODO_SUPERIOR -> MODO_MUSEU -> MODO_PAISAGEM */
		if (modoCamera == MODO_PAISAGEM) {
			modoCamera = MODO_SUPERIOR;
		}
		else if (modoCamera == MODO_SUPERIOR) {
			modoCamera = MODO_MUSEU;
		}
		else if (modoCamera == MODO_MUSEU) {
			modoCamera = MODO_PAISAGEM;
		}
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

//Função que mantem atualizando a esfera
void atualizaEsfera(int time) {
	//Variando o angulo da esfera em torno do eixo Y
	anguloEsferaY += 0.1f;
	//Rotação em torno do proprio corpo celeste.
	dia = fmod(dia+1, 360);

	/*Se a camera ativa, não for do MUSEU e o MUSEU não tiver sido ativado ainda, apenas translada normalmente,
	se ja foi ativado, e não for MUSEU, recebo o valor anterior do ano antes da pausa,
	se for a camera do MUSEU, pausa a translação e coloca os planetas na posição inicial/seleciona o planeta
	para desenhá-lo sem muitos problemas
	*/
	if (modoCamera != MODO_MUSEU && anoPausado == 0) {
		ano = fmod(ano + 0.5, 360);
	}
	else if (modoCamera != MODO_MUSEU && anoPausado != 0) {
		ano = anoPausado;
		ano = fmod(ano + 0.5, 360);
	}else{
		anoPausado = ano;
		ano = 0;
	}
	
	glutPostRedisplay();
	glutTimerFunc(time, atualizaEsfera, time);
}

/* Função main*/
int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//Definindo um objeto de janela para fixar o tamanho da janela inicial
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//Definindo o tamanho da janela e sua posição no monitor
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(275, 50);
	/* Cria a janela com o titulo*/
	glutCreateWindow("stellarSystem - phoursky");
	/* Define callbacks */
	glutDisplayFunc(desenhaMundo);
	glutReshapeFunc(redimensionada);
	glutKeyboardFunc(teclaPressionada); //Usado para capturar os eventos de teclas especiais (aquelas que nao geram um valor ASCII)
	glutSpecialFunc(teclaEspecialPressionada);
	glutTimerFunc(16, atualizaEsfera, 16);

	inicializa();
	glutMainLoop();

	return 0;

}