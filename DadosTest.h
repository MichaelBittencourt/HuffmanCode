#ifndef DADOS_TEST_H
#define DADOS_TEST_H

#include <iostream>
#include "DadosCompressorIF.h"

using namespace std;

class DadosTest : public DadosCompressorIF {
	public:
		DadosTest();
		unsigned int getCountByte(char byte);//Metodos Referente a leitura e escrita dos dados.
		/*Os metodos e estruturas aqui listadas devem tratar leitura e escritas dos dados, fornecendo
		o conjunto de bytes necessarios para implementação do compressor.*/
		void operator = (DadosCompressorIF & copia);//colocar const eu acho. Não sei se devo colocar aqui
		~DadosTest();
};

#endif
