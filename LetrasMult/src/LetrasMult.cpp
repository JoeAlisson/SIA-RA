//============================================================================
// Name        : CubosCoresMult.cpp
// Author      : Pedro
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <aruco/aruco.h>
#include "../lib/DetectorMult.h"
#include "../lib/ObjetoMult.h"
#include "../lib/ShowGLMult.h"
using namespace std;
using namespace aruco;

int main(int argc,char **argv) {
	string caminho = "intrinsics.yml";
	CameraParameters* parametros = new CameraParameters();
	parametros->readFromXMLFile(caminho);

	vector<BoardConfiguration> vectorConfig;
	BoardConfiguration config_1("board_2x3_1.yml");
	BoardConfiguration config_2("board_2x3_2.yml");
	BoardConfiguration config_3("board_2x3_3.yml");

	vectorConfig.push_back(config_1); vectorConfig.push_back(config_2);
	vectorConfig.push_back(config_3);

	DetectorMult detectorMult(0.5,1,caminho,0.2,vectorConfig);
	detectorMult.inicializar(parametros);

	ObjetoMult cuboVerde(.2,"obj/_A.obj");
	float tempCores1[] = {1,1,1};
	cuboVerde.setCores(vector<float>(tempCores1,tempCores1+3));

	ObjetoMult cuboVermelho(.2,"obj/_B.obj");
	float tempCores2[] = {1,1,1};
	cuboVermelho.setCores(vector<float>(tempCores2,tempCores2+3));

	ObjetoMult cuboAzul(.2,"obj/_C.obj");
	float tempCores3[] = {1,1,1};
	cuboAzul.setCores(vector<float>(tempCores3,tempCores3+3));

	vector<ObjetoMult> objetos;
	objetos.push_back(cuboVerde); objetos.push_back(cuboVermelho);
	objetos.push_back(cuboAzul);

	ObjetoMult endGame(0.10,"parabens.obj");

	ShowGLMult showGL(detectorMult,objetos,endGame);
	showGL.executar(argc,argv);
}
