#ifndef COMPRESSOR_HUFFMAN_H
#define COMPRESSOR_HUFFMAN_H

#include <iostream>
#include <queue>
#include <string>
#include <string.h>
#include "CompressorIF.h"
#include "DadosCompressorIF.h"
#include "FrequencyData.h"
#define SIZE_VECTOR_BYTES 1000384

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
		int vectorForHeap();
		FrequencyData * BuildHuffmanTree();
		void printHuffmanTree(FrequencyData * treeHuffman, int qtdEspacos, bool simpleExibition);
		int qtdNode(FrequencyData * arvore, int qtdNodeA);
		int qtdNodeTree(FrequencyData * arvore);
		unsigned char ** tableTree(FrequencyData * arvore, int numNodeTree, int typeNodeTree);
		int achaFolha(unsigned char ** table, FrequencyData * arvore, int posFolha, int numNodeTree);
		void invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree);
		unsigned char * divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree);
/*		void convertCode(FILE * arquivoDescomprimido, unsigned char ** tabela, char *nomeArquivoComprimido, int qtdTiposCaracter, int numNodeTree, char * extencaoArquivoDescomprimido);

		void FreeHuffmanTree(Node ** arvore);
		void FreeListValue(ListaDENode ** lista);
		void FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter);

		//funções para manipulação de Binarios e ASCII
		char bintoASCII(char binario[8]);
		void ascIItoBin(unsigned char let, char bin[8]);
		int imprimeBIN(char t[9]);
		char * toStringBin(char t[9]);

		char * getExtencaoArquivo(char * nomeArquivo);

*/
		
	
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
