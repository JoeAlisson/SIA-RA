/*
 * Util.h
 *
 *  Created on: 06/02/2015
 *      Author: pedro
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_
#include <glm/glm.hpp>

using namespace glm;

class Util {
public:

	Util(){};
	vec3 ExtractCameraPos(const double modelview[16]){
		mat3 matrix(1);
		for(unsigned int i=0; i<3;i++){
			unsigned int j=i;
			unsigned int x = 0;
			for(; j<11; j += 4){
				matrix[i][x] = modelview[j];
				x++;
			}
		}
		vec3 vetor(modelview[12],modelview[13],modelview[14]);
		return -matrix*vetor;
	}
	double* getCenter(const double modelview[16]){
		double* cXYZ = new double[3];
		double** matrix = new double*[3];
		for(unsigned int i=0; i<3;i++){
			matrix[i] = new double[3];
			unsigned int j=i;
			unsigned int x = 0;
			for(; j<11; j += 4){
				matrix[i][x] = modelview[j];
				x++;
			}
		}
		double* vetor = new double(3);
		vetor[0] = modelview[12]; vetor[1] =modelview[13]; vetor[2] =modelview[14];
		for(unsigned int x=0; x<3;x++){
			double resultado = 0;
			for(unsigned int y=0; y<3;y++){
				resultado += matrix[x][y] + vetor[y];
			}
			cXYZ[x] = resultado;
		}
		return cXYZ;
	}
	bool isBoardEqual(aruco::BoardConfiguration b1, aruco::BoardConfiguration b2){
		vector<int> lista_b1;b1.getIdList(lista_b1);
		vector<int> lista_b2;b2.getIdList(lista_b2);
		if(lista_b1.size() == lista_b2.size()){
			for(unsigned int x=0;x<lista_b1.size();x++){
					if(lista_b1.at(x) != lista_b2.at(x))
						return false;
			}
			return true;
		}else{
			return false;
		}
	}
};


#endif /* UTIL_H_ */
