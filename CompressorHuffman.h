#ifndef COMPRESSOR_HUFFMAN_H
#define COMPRESSOR_HUFFMAN_H

#include <iostream>
#include <queue>
#include <string>
#include "CompressorIF.h"
#include "DadosCompressorIF.h"
#include "FrequencyData.h"

using namespace std;

struct comparatorLong{
	bool operator ()(FrequencyData * i, FrequencyData * j){
		return i->getFrequency() > j->getFrequency();
	}
};

/*
unsigned char * compress(unsigned char * vetorDados, int sizeVetor, int & sizeDataCompress){
    ListaDENode * listaDeBytes = NULL;
    ListaDENode * tail = NULL;
    Node * root = NULL;
    Node * treeHuffman = NULL;
	list<unsigned char> listaComprimida;
    int TiposCaracter = 0;
    unsigned char ** tabela = NULL;
    int numNodeTree = 0;
	unsigned char * vetorComprimido = NULL;

	TiposCaracter = getByteFrequency(vetorDados, sizeVetor, &root);//Substituir arquivo por Vetor
	
	walkTree_L(root, &listaDeBytes, &tail);

	treeHuffman = BuildHuffmanTree(listaDeBytes, treeHuffman);
    treeHuffman->parent = NULL;

    numNodeTree = qtdNodeTree(treeHuffman);

	tabela = tableTree(treeHuffman, numNodeTree, TiposCaracter);

    listaComprimida = convertCode(vetorDados, sizeVetor, tabela, TiposCaracter, numNodeTree);

	sizeDataCompress = (listaComprimida.size()+1)*sizeof(unsigned char);
	vetorComprimido = (unsigned char*)malloc(sizeDataCompress);

	int i = 0;
	for(list<unsigned char>::iterator it = listaComprimida.begin(); it != listaComprimida.end(); it++, i++){
		vetorComprimido[i] = *it;
		//printf("VetorComprimido[%d] = %x, *it = %x", i, vetorComprimido[i], *it);
		//getchar();
		wait();
	}
	vetorComprimido[listaComprimida.size()] = '\0';
	#ifdef EXIBE_INFORMACOES
		printf("\nsize da lista comprimida = %d\n", (int)listaComprimida.size());
	#endif

	FreeHuffmanTree(&root);

	FreeListValue(&listaDeBytes);

	FreeTableBytes(&tabela, TiposCaracter);

	return vetorComprimido;
}

*/

class CompressorHuffman : public CompressorIF{
	
	protected:

		DadosCompressorIF & dados;
		priority_queue<FrequencyData *, std::vector<FrequencyData *>, comparatorLong> minHeap;
		void vectorForHeap();
		FrequencyData * BuildHuffmanTree();
		void printHuffmanTree(FrequencyData * treeHuffman, int qtdEspacos, bool simpleExibition);
	
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
