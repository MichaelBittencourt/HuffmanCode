#include "CompressorHuffman.h"

/*CompressorHuffman::CompressorHuffman(){

}*/

/*****************************************Protected function*********************************************/

void CompressorHuffman::vectorForHeap(){
	unsigned long * vector = dados.getArrayFrequency();
	for(int i = 0; i < 256; i++){
		if(vector[i] != 0){
			std::cout << "v[" << (char)i << "] = " << vector[i] << std::endl;
			minHeap.push(new FrequencyData(i, vector[i]));
/*			int size = minHeap.size();
			for(int j = 0; j < size; j++){
				std::cout << "(" << minHeap.top().getByte() << ", " << minHeap.top().getFrequency() << ")" << std::endl;
				minHeap.pop();
			}*/
		}
	}
	/*int size = minHeap.size();
	for(int j = 0; j < size; j++){
		std::cout << "(" << minHeap.top()->getByte() << ", " << minHeap.top()->getFrequency() << ")" << std::endl;
		minHeap.pop();
	}*/
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
		//menor1.set( = minHeap.top();
		menor1 = minHeap.top();
		//temp = new FrequencyData(0);
		//menor1 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency(), temp, minHeap.top().getLeft(),minHeap.top().getRight());
		//menor1 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency());
		//std::cout << "(" << minHeap.top().getByte() << ", " << minHeap.top().getFrequency() << ")" << std::endl;
		//std::cout << "(" << menor1->getByte() << ", " << menor1->getFrequency() << ")" << std::endl;
		//getchar();
		minHeap.pop();
		//std::cout << "(" << menor1->getByte() << ", " << menor1->getFrequency() << ")" << std::endl;
		if(minHeap.empty()){
			break;
		}
		//menor2 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency());
//		menor2 = new FrequencyData(minHeap.top().getByte(), minHeap.top().getFrequency(), temp, minHeap.top().getLeft(),minHeap.top().getRight());
		menor2 = (FrequencyData *)minHeap.top();
//		std::cout << "(" << menor2->getByte() << ", " << menor2->getFrequency() << ")" << std::endl;
		//getchar();
		minHeap.pop();
	//	std::cout << "(" << menor2->getByte() << ", " << menor2->getFrequency() << ")" << std::endl;
		temp = new FrequencyData(0, menor1->getFrequency()+menor2->getFrequency());
		//temp->setFrequency(menor1->getFrequency()+menor2->getFrequency());
		menor1->setParent(temp);
		menor2->setParent(temp);
		temp->setLeft(menor1);
		temp->setRight(menor2);
		minHeap.push(temp);
	}

	return menor1;
}

void CompressorHuffman::printHuffmanTree(FrequencyData * treeHuffman, int qtdEspacos, bool simpleExibition){
	if(treeHuffman != nullptr){
		string deslocamento = "";
		if(qtdEspacos != 0)
			deslocamento += "   ";			
		for(int i = 0; i < qtdEspacos; i++){
			if(i == qtdEspacos-1){
				deslocamento += "|__";
			}
			else
				deslocamento += "      ";
		}
		string byte = "";
		byte += (char)treeHuffman->getByte();
		if(byte == "\n"){
			byte = "\\n";
		}
		if(simpleExibition)
			std::cout << deslocamento << "(" << byte << ", " << treeHuffman->getFrequency() << ")" << std::endl;
		else
			std::cout  << deslocamento << "Nivel = " << qtdEspacos << "\n" << deslocamento << "parent = " << treeHuffman->getParent() <<"\n" << deslocamento << "(" << byte << ", " << treeHuffman->getFrequency() << ") = "<< treeHuffman << "\n"  << deslocamento << "left = " << treeHuffman->getLeft() << "right = " << treeHuffman->getRight() << std::endl;
		printHuffmanTree(treeHuffman->getLeft(), qtdEspacos+1, simpleExibition);
		//getchar();
		printHuffmanTree(treeHuffman->getRight(),qtdEspacos+1, simpleExibition);
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
	printHuffmanTree(treeHuffman, 0, true);
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
