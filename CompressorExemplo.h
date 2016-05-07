#ifndef COMPRESSOR_EXEMPLO_H
#define COMPRESSOR_EXEMPLO_H

#include <iostream>
#include "CompressorIF.h"
#include "DadosCompressorIF.h"

using namespace std;

class CompressorExemplo : public CompressorIF{
	
	protected:
		DadosCompressorIF & dados;
	
	public:
		//CompressorHuffman();
		CompressorExemplo(DadosCompressorIF & d);
		
		void setDados(DadosCompressorIF & dados);
		DadosCompressorIF & getDados();
		bool compress();
		bool descompress();
		
		~CompressorExemplo();
};

#endif
