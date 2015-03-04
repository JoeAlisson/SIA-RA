/*
 * BoardObjetoException.hpp
 *
 *  Created on: 05/02/2015
 *      Author: pedro
 */
#ifndef BOARDOBJETOEXCEPTION_HPP_
#define BOARDOBJETOEXCEPTION_HPP_
#include <exception>
using namespace std;

class BoardObejtoException : public exception{
public:
	virtual const char* what() const throw(){
		return "Número de ObjetosMult diferente do de BoardConfiguration";
	}
};

#endif /* BOARDOBJETOEXCEPTION_HPP_ */


