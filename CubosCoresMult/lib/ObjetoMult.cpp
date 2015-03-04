/*
 * ObjetoMult.cpp
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#include "ObjetoMult.h"


ObjetoMult::ObjetoMult(){}
ObjetoMult::ObjetoMult(float tamanhoMarcador, obj::FORMAS forma){
	this->tamanhoMarcador = tamanhoMarcador;
	this->carregaOBJ = NULL;
	this->renderizador = NULL;
	this->caminho = NULL;
	this->forma = forma;
}
ObjetoMult::ObjetoMult(float tamanhoMarcador,char caminho[]) {
	this->tamanhoMarcador = tamanhoMarcador;
	this->caminho = caminho;
	this->carregaOBJ = OBJParser().load(caminho);
	this->renderizador = new Renderer();
}
void ObjetoMult::desenharObjeto() {
	if(cores.size() != 0 )
		glColor3f(cores.at(0),cores.at(1),cores.at(2));
	double modelview_matrix[16];
	board.glGetModelViewMatrix(modelview_matrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixd(modelview_matrix);
	glTranslatef(0, 0, tamanhoMarcador/2);
	glPushMatrix();
	if(this->carregaOBJ == NULL)
		switch(this->forma){
		case obj::CUBO:
			glutSolidCube( tamanhoMarcador*7 );
			break;
		case obj::CONE:
			glutSolidCone(tamanhoMarcador/2,tamanhoMarcador,50,50);
			break;
		case obj::ESFERA:
			glutSolidSphere(tamanhoMarcador/2,50,50);
			break;
		}
	else
		this->renderizador->render(this->carregaOBJ);
}
void ObjetoMult::desenharPosicao(float x,float y, float z,bool modo_exemplo){
	glPushMatrix();
	glLoadIdentity();
	if(this->cores.size() == 3 )
			glColor3f(this->cores.at(0),this->cores.at(1),this->cores.at(2));
	glTranslatef(x,y,z);
	if(this->carregaOBJ == NULL)
		switch(this->forma){
		case obj::CUBO:
			if(modo_exemplo){
				glTranslatef(.4,0,0);
				glRotated(195,0,1,0);
				glRotated(10,1,0,0);
				glScaled(1.6,1.6,1.6);
			}
			glutSolidCube( tamanhoMarcador );
			break;
		case obj::CONE:
			if(modo_exemplo){
				glTranslatef(0,-.15,0);
				glRotated(270,1,0,0);
				glScaled(1.8,1.8,1.8);
			}
			glutSolidCone(tamanhoMarcador/2,tamanhoMarcador,20,20);
			break;
		case obj::ESFERA:
			if(modo_exemplo){
				glRotated(195,0,1,0);
				glScaled(1.8,1.8,1.8);
			}
			glutSolidSphere(tamanhoMarcador/2,20,20);
			break;
		}
	else
		this->renderizador->render(this->carregaOBJ);
	glPopMatrix();
}
void ObjetoMult::setCores(const vector<float>& cores) {
	this->cores = cores;
}
aruco::BoardConfiguration ObjetoMult::getConfig() const {
	return this->config;
}
void ObjetoMult::setBoard(const aruco::Board& board) {
	this->board = board;
}
void ObjetoMult::setConfig(aruco::BoardConfiguration&  config){
	this->config = config;
}
