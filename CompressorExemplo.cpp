#include "CompressorExemplo.h"

/*CompressorExemplo::CompressorExemplo(){

}*/

CompressorExemplo::CompressorExemplo(DadosCompressorIF &d) : dados(d) {
	//this->dados = dados;
}

void CompressorExemplo::setDados(DadosCompressorIF &dados){
	this->dados = dados;
}
DadosCompressorIF & CompressorExemplo::getDados(){
	return dados;
}

bool CompressorExemplo::compress(){
	cout << "Comprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}

bool CompressorExemplo::decompress(){
	cout << "Descomprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}
		
CompressorExemplo::~CompressorExemplo(){
	delete &dados;
	cout << "Destruindo Compressor" << endl;
}
