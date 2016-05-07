#include "CompressorExemplo.h"

/*CompressorExemplo::CompressorExemplo(){

}*/

CompressorExemplo::CompressorExemplo(DadosCompressorIF & d) : dados(d){
	//this->dados = dados;
}

void CompressorExemplo::setDados(DadosCompressorIF & dados){
	this->dados = dados;
}
DadosCompressorIF & CompressorExemplo::getDados(){
	return dados;
}

bool CompressorExemplo::compress(){
	cout << "Comprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}

bool CompressorExemplo::descompress(){
	cout << "Descomprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}
		
CompressorExemplo::~CompressorExemplo(){
	cout << "Destruindo Compressor" << endl;
}
