#include "CompressorHuffman.h"

/*CompressorHuffman::CompressorHuffman(){

}*/

/*****************************************Protected function*********************************************/

void CompressorHuffman::vectorForHeap(){
	unsigned long * vector = dados.getArrayFrequency();
	for(int i = 0; i < 256; i++){
		if(vector[i] != 0){
			std::cout << "v[" << (char)i << "] = " << vector[i] << std::endl;
			minHeap.push(*(new FrequencyData(i, vector[i])));
/*			int size = minHeap.size();
			for(int j = 0; j < size; j++){
				std::cout << "(" << minHeap.top().getByte() << ", " << minHeap.top().getFrequency() << ")" << std::endl;
				minHeap.pop();
			}*/
		}
	}
	int size = minHeap.size();
	for(int j = 0; j < size; j++){
		std::cout << "(" << minHeap.top().getByte() << ", " << minHeap.top().getFrequency() << ")" << std::endl;
		minHeap.pop();
	}
}


FrequencyData * CompressorHuffman::BuildHuffmanTree()
{
    FrequencyData * menor1;
    FrequencyData * menor2;
    FrequencyData * temp = nullptr;
//    InsertionSort_L(lista);
    //inOrderList_L(lista);
	while (true) {
		//cout << minHeap.top() << " ";
		menor1 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency());
		std::cout << "(" << minHeap.top().getByte() << ", " << minHeap.top().getFrequency() << ")" << std::endl;
//		std::cout << "(" << menor1->getByte() << ", " << menor1->getFrequency() << ")" << std::endl;
		minHeap.pop();
		//std::cout << "(" << menor1->getByte() << ", " << menor1->getFrequency() << ")" << std::endl;
		getchar();
		if(!minHeap.empty()){
			break;
		}
		menor2 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency());
		minHeap.pop();
		temp = new FrequencyData(0, menor1->getFrequency()+menor2->getFrequency());
		menor1->setParent(temp);
		menor2->setParent(temp);
		temp->setLeft(menor1);
		temp->setRight(menor2);
		minHeap.push(*temp);
	}

	return menor1;
}

void CompressorHuffman::printHuffmanTree(FrequencyData * treeHuffman){
	if(treeHuffman != nullptr){
		printHuffmanTree(treeHuffman->getLeft());
		printHuffmanTree(treeHuffman->getRight());
		std::cout << "(" << treeHuffman->getByte() << ", " << treeHuffman->getFrequency() << ")" << std::endl;
	}
}

/***************************************End Protected function********************************************/

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
	cout << "Comprimindo " << endl;
	vectorForHeap();
	FrequencyData * treeHuffman = nullptr;
	treeHuffman = BuildHuffmanTree();
	printHuffmanTree(treeHuffman);
	cout << "Raiz da Arvore = " << treeHuffman << endl;
	return true;
}

bool CompressorHuffman::decompress(){
	cout << "Descomprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}
		
CompressorHuffman::~CompressorHuffman(){
	cout << "Destruindo Compressor" << endl;
}
