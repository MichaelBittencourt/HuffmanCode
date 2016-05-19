#ifndef COMPRESSOR_HUFFMAN_H
#define COMPRESSOR_HUFFMAN_H

#include <iostream>
#include "CompressorIF.h"
#include "DadosCompressorIF.h"

using namespace std;

class CompressorHuffman /*: public CompressorIF*/{
	
	protected:
		DadosCompressorIF & dados;
	
	public:
		//CompressorHuffman();
		CompressorHuffman(DadosCompressorIF &d);
		
		void setDados(DadosCompressorIF &dados);
		DadosCompressorIF& getDados();
		bool compress();
		bool decompress();
		
		~CompressorHuffman();
};

#endif
