/*
 * ShowGLMult.h
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#ifndef SHOWGLMULT_H_
#define SHOWGLMULT_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include "DetectorMult.h"
#include "ObjetoMult.h"
#include "Kalman.h"
#include "Util.hpp"
#include <glm/glm.hpp>

using namespace cv;

class ShowGLMult{
private:
	static void ativarIluminacao();
	static void desativarIluminacao();
	static void emEspera();
	static void desenharExemplo();
	static void desenharTela();
	static void desenharObjetos();
	static void desenharUltimaPosicao();
	static void desenharKalman();
	static void desenharMultTecnicas();
	static bool isOrdenado();
	static void teclasEspeciais(int,int,int);
	static void redimensionar(GLsizei, GLsizei);
public:
	static Util util;
	static int MODOS;
	static bool gameOver;
	static DetectorMult detector;
	static vector<ObjetoMult> objetos;
	static vector<ObjetoMult> ultimasPosicoes;
	static Kalman kalman;
	static ObjetoMult endGame;
	ShowGLMult(DetectorMult&,vector<ObjetoMult>,ObjetoMult&);
	void executar(int&,char**);
};

#endif /* SHOWGLMULT_H_ */
