#include "CompressorHuffman.h"

/*CompressorHuffman::CompressorHuffman(){

}*/

CompressorHuffman::CompressorHuffman(DadosCompressorIF & d) : dados(d){
	//this->dados = dados;
}

void CompressorHuffman::setDados(DadosCompressorIF & dados){
	this->dados = dados;
}
DadosCompressorIF & CompressorHuffman::getDados(){
	return dados;
}

bool CompressorHuffman::compress(){
	cout << "Comprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}

bool CompressorHuffman::descompress(){
	cout << "Descomprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}
		
CompressorHuffman::~CompressorHuffman(){
	cout << "Destruindo Compressor" << endl;
}
