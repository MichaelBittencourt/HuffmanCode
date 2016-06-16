#ifndef COMPRESSOR_HUFFMAN_ANTIGO_H
#define COMPRESSOR_HUFFMAN_ANTIGO_H

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#include "CompressorIF.h"
#define SIZE_VECTOR_BYTES 1000384

#define TAM_MAX_EXTENCAO 10

		typedef struct Node
		{
			char value;
			int frequencia;
			Node* parent;
			Node* left;
			Node* right;
		}Node;

		typedef struct ListaDENode
		{
			Node * no;
			struct ListaDENode * next;
			struct ListaDENode * prev;
		}ListaDENode;

class CompressorHuffmanAntigo : public CompressorIF{
	
	private:
		
		char * nomeArquivoEntrada;
		char * nomeArquivoSaida;
		
		int getByteFrequency(FILE* arq, struct Node **root);
		void inOrder(struct Node *root);
		int AddNode(Node **root, char value, int tiposDeCaracteres);

		void treeToList_L(Node* n, ListaDENode** head, ListaDENode** tail);
		void walkTree_L(struct Node *root, ListaDENode ** head, ListaDENode** tail);
		void InsertionSort_L(struct ListaDENode *node);
		void inOrderList_L(ListaDENode *root);
		Node * BuildHuffmanTree(ListaDENode* lista, Node* arvore);

		int qtdNode(Node * arvore, int qtdNodeA);
		int qtdNodeTree(Node *arvore);
		void invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree);
		int achaFolha(unsigned char ** table, Node * arvore, int posFolha, int numNodeTree);
		unsigned char ** tableTree(Node * arvore, int numNodeTree, int typeNodeTree);
		unsigned char * divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree);
		void tabelaToTree(unsigned char ** table, Node ** huffmanTree, int numNodeTree, int typeNodeTree);
		void convertCode(FILE * arquivoDescomprimido, unsigned char ** tabela, char *nomeArquivoComprimido, int qtdTiposCaracter, int numNodeTree, char * extencaoArquivoDescomprimido);
		void CompressFile(char * nomeArquivoDescomprimido, char nomeArquivoComprimido[]);
		void DecompressFile(char ArquivoDescomprimido[], char ArquivoComprimido[]);

		void FreeHuffmanTree(Node ** arvore);
		void FreeListValue(ListaDENode ** lista);
		void FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter);

		//funções para manipulação de Binarios e ASCII
		char bintoASCII(char binario[8]);
		void ascIItoBin(unsigned char let, char bin[8]);
		int imprimeBIN(char t[9]);
		char * toStringBin(char t[9]);

		char * getExtencaoArquivo(char * nomeArquivo);
		
	public:
		
		CompressorHuffmanAntigo();
		
		CompressorHuffmanAntigo(char nomeArquivoEntrada[], char nomeArquivoSaida[]);

		void setNomeArquivoEntrada(char * nomeArquivoEntrada);
		char * getNomeArquivoEntrada();
		void setNomeArquivoSaida(char * nomeArquivoSaida);
		char * getNomeArquivoSaida();
		bool compress();
		bool decompress();
		
		~CompressorHuffmanAntigo();
};

#endif
