#ifndef DADOS_TEST_H
#define DADOS_TEST_H

#include <iostream>
#include "DadosCompressorIF.h"

using namespace std;

class DadosTest : public DadosCompressorIF {
	public:
		DadosTest();
		DadosTest(bool actionCompress);
		unsigned int getCountByte(char byte);
		unsigned char * getArrayFrequency();
		unsigned char getPadding(); //é um valor entre 0 e 7
		unsigned int read(unsigned char * buffer, const unsigned int size); //Retorna a quatidade real de dados lidos em caso de chegar ao fim dos dados
		void write(const unsigned char * ArrayDados, const unsigned int size);
		void setTypeAction(const bool typeAction);
		void operator = (DadosCompressorIF & copia);//colocar const eu acho. Não sei se devo colocar aqui
		~DadosTest();

		private:
			bool actionCompress;

};

#endif
