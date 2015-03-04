/*
 * DetectorMultMult.cpp
 *
 *  Created on: 18/01/2015
 *      Author: pedro
 */
#include "DetectorMult.h"
DetectorMult::DetectorMult(){}
DetectorMult::DetectorMult(float tamanhoMarcador,int idCamera,string arquivoXML,float probDetec,
vector<BoardConfiguration> configMult){
	this->tamanhoMarcador = tamanhoMarcador;
	this->idMarcadores = idMarcadores;
	this->idCamera = idCamera;
	this->arquivoXML = arquivoXML;
	this->inicializado = false;
	this->configMult = configMult;
	this->probDetec = probDetec;
	for(unsigned int i=0;i<configMult.size();i++){
		this->detectorMult.push_back(BoardDetector());
		pair<Board,float> temp(Board(),0.0);
		this->detectados.push_back(temp);
	}
}
void DetectorMult::inicializar(CameraParameters* parametrosCamera){
	try{
		this->parametrosCamera = parametrosCamera;
	}catch(Exception& e) {
		cout << "Erro ao ler o arquivo XML." << endl;
	}
	try{
		this->capturador.open(idCamera);
	}catch(Exception& e) {
		cout << "Erro ao iniciar a captura de video." << endl;
	}
	this->detector.setCornerRefinementMethod(MarkerDetector::SUBPIX);
	for(unsigned int i=0;i < detectorMult.size();i++){
		detectorMult.at(i).setParams(configMult[i],*parametrosCamera,tamanhoMarcador);
		detectorMult.at(i).getMarkerDetector().setCornerRefinementMethod(MarkerDetector::HARRIS);
		detectorMult.at(i).set_repj_err_thres(1.5);
	}
	this->capturador >> this->imagemEntrada;
	this->parametrosCamera->resize(this->imagemEntrada.size());
	this->tamanhoJanela = this->imagemEntrada.size();
	inicializado = true;
}
void DetectorMult::recapturar(){
	capturador.grab();
	capturador.retrieve(this->imagemEntrada);
	this->imagemEntrada_copia.create(this->imagemEntrada.size(),CV_8UC3);
    cv::cvtColor(this->imagemEntrada,this->imagemEntrada,CV_BGR2RGB);
    cv::undistort(this->imagemEntrada,this->imagemEntrada_copia,this->parametrosCamera->CameraMatrix,
    		this->parametrosCamera->Distorsion);
    this->detector.detect(this->imagemEntrada_copia,this->marcadores);
    for(unsigned int i=0;i<this->detectorMult.size();i++){

    	this->detectados.at(i).second = this->detectorMult[i].detect(marcadores,configMult[i],detectados.at(i).first,
    			*parametrosCamera,tamanhoMarcador);
    }
    this->redimensionar();
}
vector<Board> DetectorMult::detectar(){
	vector<Board> detectados;
	for(unsigned int i=0;i<this->detectados.size();i++){
		if(this->detectados[i].second >= this->probDetec)
			detectados.push_back(this->detectados[i].first);
	}
	return detectados;
}
void DetectorMult::redimensionar(){
	cv::resize(this->imagemEntrada_copia,this->imagemRedimensionada,this->tamanhoJanela);
}

Mat DetectorMult::getImagemEntrada(){
	return this->imagemEntrada;
}

Mat DetectorMult::getImagem_Copia(){
	return this->imagemEntrada_copia;
}
CameraParameters DetectorMult::getParametrosCamera(){
	if(inicializado)
		return *this->parametrosCamera;
	else
		throw new Exception();
}
VideoCapture DetectorMult::getCapturador(){
	return this->capturador;
}
Size DetectorMult::getTamanhoJanela(){
	return this->tamanhoJanela;
}
Mat DetectorMult::getImagemRedimensionada(){
	return this->imagemRedimensionada;
}
void DetectorMult::setTamanhoJanela(Size tamanhoJanela){
	this->tamanhoJanela = tamanhoJanela;
}
float DetectorMult::getTamanhoMarcador(){
	return this->tamanhoMarcador;
}
vector<aruco::BoardConfiguration> DetectorMult::getBoards(){
	return this->configMult;
}
