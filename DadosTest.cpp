
#include "DadosTest.h"

DadosTest::DadosTest(){}

unsigned int DadosTest::DadosTest::getCountByte(char byte){
	cout << "Contando dados " << byte << endl;
	return byte;
}
void DadosTest::operator = (DadosCompressorIF & copia){//colocar const eu acho. Não sei se devo colocar aqui
	cout << "Realizando uma atribuicao" << endl;
}

DadosTest::~DadosTest(){
	cout << "Destruindo DadosTest" << endl;
}
