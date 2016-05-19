
#include "DadosTest.h"

DadosTest::DadosTest(){
	this->actionCompress = true;
}

DadosTest::DadosTest(bool actionCompress){
	this->actionCompress = actionCompress;
}

unsigned int DadosTest::DadosTest::getCountByte(char byte){
	cout << "Contando quantidade de '" << byte << "'" <<  endl;
	return byte;
}

unsigned char * DadosTest::getArrayFrequency(){
	unsigned char * arrayFrequency = new unsigned char[256];
	for(int i = 0; i < 256; i++){
		arrayFrequency[i] = i;
	}
	if(actionCompress)
		cout << "Pegando Array com frequencias para os Dados Descomprimidos." << endl;
	else
		cout << "Pegando Array com frequencias para os Dados Comprimidos." << endl;
	return arrayFrequency;
}

unsigned char DadosTest::getPadding(){ //é um valor entre 0 e 7
	if(actionCompress){
		cout << "Retorna 0 está sendo feita a compressao, logo não tem padding" << endl;
		return 0;
	}
	cout << "pegando padding = 5" << endl;
	return 5;
}
unsigned int DadosTest::read(unsigned char * buffer, const unsigned int size){ //Retorna a quatidade real de dados lidos em caso de chegar ao fim dos dados
	if(actionCompress){	
		cout << "Lendo "<<  size << " bytes dos dados Descomprimidos" <<  endl;
	}
	else{
		cout << "Lendo "<<  size << " bytes dos dados Comprimidos" <<  endl;
	}
	return size;
}
void DadosTest::write(const unsigned char * ArrayDados, const unsigned int size){
	cout << "Escrevendo Dados" << endl;
}
void DadosTest::setTypeAction(const bool typeAction){
	actionCompress = typeAction;
}

void DadosTest::operator = (DadosCompressorIF & copia){//colocar const eu acho. Não sei se devo colocar aqui
	cout << "Realizando uma atribuicao" << endl;
}

DadosTest::~DadosTest(){
	cout << "Destruindo DadosTest" << endl;
}
