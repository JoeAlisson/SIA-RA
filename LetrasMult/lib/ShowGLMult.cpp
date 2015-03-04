/*
 * ShowGLMult.cpp
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#include "ShowGLMult.h"

DetectorMult ShowGLMult::detector = DetectorMult();
Util ShowGLMult::util = Util();
int ShowGLMult::MODOS = 0;
vector<ObjetoMult> ShowGLMult::objetos = vector<ObjetoMult>();
vector<ObjetoMult> ShowGLMult::ultimasPosicoes = ShowGLMult::objetos;
Kalman ShowGLMult::kalman = Kalman();
ObjetoMult ShowGLMult::endGame = ObjetoMult();
bool ShowGLMult::gameOver = false;

ShowGLMult::ShowGLMult(DetectorMult& detector,vector<ObjetoMult> objetos, ObjetoMult& endGame){
	if(objetos.size() == detector.getBoards().size()){
		ShowGLMult::detector = detector;
		ShowGLMult::objetos = objetos;
		ShowGLMult::endGame = endGame;
		for(unsigned int i=0;i<objetos.size();i++)
			ShowGLMult::objetos.at(i).setConfig(ShowGLMult::detector.getBoards().at(i));
		ShowGLMult::ultimasPosicoes = ShowGLMult::objetos ;
	}
}
void ShowGLMult::ativarIluminacao(){
	float luzAmbiente[]={0.2,0.2,0.2,1.0};
	float luzDifusa[]={0.9,0.7,0.7,1.0};
	float luzEspecular[] = {1.0, 1.0, 1.0, 1.0};
	float posicaoLuz[]={50, 25.0, 50.0, 1.0};

	float especularidade[] = {1.0,1.0,1.0,1.0};
	int especMaterial = 60;

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
void ShowGLMult::desativarIluminacao(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
bool ShowGLMult::isOrdenado(){
	vector<Board>marcadores = ShowGLMult::detector.detectar();
	vector<double*> vetores;
	Util* util = new Util();
	if(marcadores.size() == ShowGLMult::objetos.size()){
		for(unsigned int i=0;i<marcadores.size();i++){
			double temp[16];
			marcadores.at(i).glGetModelViewMatrix(temp);
			vetores.push_back(util->getCenter(temp));;
		}
		delete(util);
		for(unsigned int i=0;i<vetores.size()-1;i++){
			if(vetores[i][0] < vetores[i+1][0]){
				if(i == marcadores.size()-1)
					return true;
			}else{
				return false;
			}
		}
	}
	else
		return false;
}
void ShowGLMult::desenharExemplo(){
	float posicao = ShowGLMult::detector.getTamanhoMarcador();
	for(int i=ShowGLMult::objetos.size()-1;i>=0;i--){
		ativarIluminacao();
		ShowGLMult::objetos[i].desenharPosicao(-posicao,0.8,.5,false);
		desativarIluminacao();
		posicao += ShowGLMult::detector.getTamanhoMarcador()*.7;

	}
}
void ShowGLMult::desenharObjetos(){
	vector<Board>boards = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<boards.size();x++){
		for(unsigned int y=0;y<ShowGLMult::objetos.size();y++){
			if(util.isBoardEqual(boards[x].conf,ShowGLMult::objetos[y].getConfig())){
				ShowGLMult::objetos[y].setBoard(boards[x]);
				ativarIluminacao();
				ShowGLMult::objetos[y].desenharObjeto();
				desativarIluminacao();
			}
		}
	}
}
void ShowGLMult::desenharUltimaPosicao(){
	for(unsigned int x=0;x<ShowGLMult::ultimasPosicoes.size();x++){
		ativarIluminacao();
		ShowGLMult::ultimasPosicoes[x].desenharObjeto();
		desativarIluminacao();
	}
	vector<Board> detectados = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<detectados.size();x++){
		for(unsigned int y=0;y<ShowGLMult::ultimasPosicoes.size();y++){
			if(detectados[x].conf == ShowGLMult::ultimasPosicoes[y].getConfig())
				ShowGLMult::ultimasPosicoes[y].setBoard(detectados[x]);
		}
	}
}
void ShowGLMult::desenharKalman(){
	vector<Board>marcadores = ShowGLMult::detector.detectar();
	vector<ObjetoMult>objetos = ShowGLMult::objetos;
	for(unsigned int x=0;x<marcadores.size();x++){
		for(unsigned int y=0;y<objetos.size();y++){
//			if(marcadores[x].conf == objetos[y].getConfig()()){
//				objetos[y].setBoard(ShowGLMult::kalman.prever(marcadores[x]));
//				ativarIluminacao();
//				objetos[y].desenharObjeto();
//				desativarIluminacao();
//			}
		}
	}
}
void ShowGLMult::desenharMultTecnicas(){
	for(unsigned int x=0;x<ShowGLMult::ultimasPosicoes.size();x++){
		ativarIluminacao();
		ShowGLMult::ultimasPosicoes[x].desenharObjeto();
		desativarIluminacao();
	}
	vector<Board> detectados = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<detectados.size();x++){
		for(unsigned int y=0;y<ShowGLMult::ultimasPosicoes.size();y++){
//			if(detectados[x].conf == ShowGLMult::ultimasPosicoes[y].getConfig())
//				ShowGLMult::ultimasPosicoes[y].setBoard(
//						ShowGLMult::kalman.prever(detectados[x])
//				);
		}
	}
}
void ShowGLMult::desenharTela(){
	if (detector.getImagemRedimensionada().rows==0)
	    return;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, detector.getTamanhoJanela().width, 0, detector.getTamanhoJanela().height, -1.0, 1.0);
    glViewport(0, 0, detector.getTamanhoJanela().width , detector.getTamanhoJanela().height);
    glPixelZoom( 1, -1);
    glRasterPos3f( 0, detector.getTamanhoJanela().height  - 0.5, -1.0 );
    glDrawPixels ( detector.getTamanhoJanela().width , detector.getTamanhoJanela().height , GL_RGB ,
    		GL_UNSIGNED_BYTE , detector.getImagemRedimensionada().ptr(0) );
    if(isOrdenado())
    	ShowGLMult::gameOver = true;
    if(gameOver){
    	ativarIluminacao();
    	ShowGLMult::endGame.desenharPosicao(0,0,.8,true);
    	desativarIluminacao();
    }
    glLoadIdentity();

    desenharExemplo();

    glMatrixMode(GL_PROJECTION);
    double proj_matrix[16];
    detector.getParametrosCamera().glGetProjectionMatrix(
    		detector.getImagemEntrada().size(),detector.getTamanhoJanela(),proj_matrix,0.05,10
	);
    glLoadIdentity();
    glLoadMatrixd(proj_matrix);

    if(ShowGLMult::MODOS ==  0)
    	desenharObjetos();
    else if(ShowGLMult::MODOS == 1)
    	desenharUltimaPosicao();
    else if(ShowGLMult::MODOS == 2)
    	desenharKalman();
    else if(ShowGLMult::MODOS == 3)
    	desenharMultTecnicas();

    glutSwapBuffers();
}
void ShowGLMult::teclasEspeciais(int key, int x, int y){
	switch(key) {
		case GLUT_KEY_F1 :
			ShowGLMult::MODOS = 0; break;
		case GLUT_KEY_F2 :
			ShowGLMult::MODOS = 1; break;
		case GLUT_KEY_F3 :
			ShowGLMult::MODOS = 2; break;
		case GLUT_KEY_F4 :
			ShowGLMult::MODOS = 3; break;
		}
}
void ShowGLMult::emEspera(){
	detector.recapturar();
	glutPostRedisplay();
}
void ShowGLMult::redimensionar(GLsizei largura, GLsizei altura){
		detector.setTamanhoJanela(Size(largura,altura));
	    if (largura*3%4!=0) {
	        largura+=largura*3%4;
	        redimensionar(largura,detector.getTamanhoJanela().height);
	    }
	    else {
	        if (detector.getImagem_Copia().rows!=0)
	        detector.redimensionar();
	    }
}
void ShowGLMult::executar(int & argc, char** argv){
	 glutInit(&argc, argv);
	 glutInitWindowPosition( 0, 0);
	 Mat imagemEntrada = detector.getImagemEntrada();
	 glutInitWindowSize(imagemEntrada.size().width,imagemEntrada.size().height);
	 glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	 glutCreateWindow( "Jogo Formas (cores diferentes)" );
	 glutDisplayFunc( desenharTela );
	 glutIdleFunc( emEspera );
	 glutReshapeFunc( redimensionar );
	 glutSpecialFunc( teclasEspeciais );
	 glClearColor( 0.0, 0.0, 0.0, 1.0 );
	 glClearDepth( 1.0 );
	 detector.setTamanhoJanela(imagemEntrada.size());
	 Size tamanhoJanela = detector.getTamanhoJanela();
	 redimensionar(tamanhoJanela.width,tamanhoJanela.height);
	 glutMainLoop();
}


