/*
 * ObjetoMult.h
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#ifndef OBJETOMULT_H_
#define OBJETOMULT_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <aruco/aruco.h>
#include "../lib/objparser.h"
#include "../lib/renderer.h"

namespace obj{
	enum FORMAS{CUBO,CONE,ESFERA};
}

class ObjetoMult{
private:
	aruco::BoardConfiguration config;
	obj::FORMAS forma;
	aruco::Board board;
	float tamanhoMarcador;
	vector<float> cores;
	char* caminho;
	OBJMesh* carregaOBJ;
	Renderer* renderizador;
public:
	ObjetoMult();
	ObjetoMult(float,obj::FORMAS);
	ObjetoMult(float,char*);
	void desenharObjeto();
	void desenharPosicao(float,float,float,bool);
	void setCores(const vector<float>& cores);
	void setConfig(aruco::BoardConfiguration&);
	aruco::BoardConfiguration getConfig() const;
	void setBoard(const aruco::Board& marcador);
};



#endif /* OBJETOMULT_H_ */
