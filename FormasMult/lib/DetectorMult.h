/*
 * DetectorMult.h
 *
 *  Created on: 18/01/2015
 *      Author: pedro
 */

#ifndef DETECTORMULT_H_
#define DETECTORMULT_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <aruco/aruco.h>
#include <iostream>

using namespace cv;
using namespace aruco;

class DetectorMult{
private:
	float tamanhoMarcador;
	int idCamera;
	bool inicializado;
	string arquivoXML;
	MarkerDetector detector;
	vector<Marker> marcadores;
	VideoCapture capturador;
	CameraParameters* parametrosCamera;
	vector<int> idMarcadores;
	Mat imagemEntrada, imagemEntrada_copia, imagemRedimensionada;
	Size tamanhoJanela;

	vector<BoardDetector> detectorMult;
	vector<BoardConfiguration> configMult;
	vector<pair<Board,float> > detectados;
	float probDetec;
public:
	DetectorMult();
	DetectorMult(float,int,string,float,vector<BoardConfiguration>);
	void redimensionar();
	void setTamanhoJanela(Size);
	Mat getImagem_Copia();
	Mat getImagemRedimensionada();
	Mat getImagemEntrada();
	CameraParameters getParametrosCamera();
	VideoCapture getCapturador();
	Size getTamanhoJanela();
	vector<BoardConfiguration> getBoards();
	float getTamanhoMarcador();
	void inicializar(CameraParameters*);
	vector<Board> detectar();
	void recapturar();
};


#endif /* DETECTORMULT_H_ */
