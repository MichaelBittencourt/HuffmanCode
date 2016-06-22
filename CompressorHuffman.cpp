#include "CompressorHuffman.h"

/*CompressorHuffman::CompressorHuffman(){

}*/

/*****************************************Protected function*********************************************/

int CompressorHuffman::vectorForHeap(){
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
	return minHeap.size();
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

int CompressorHuffman::qtdNode(FrequencyData * arvore, int qtdNodeA)
{
    if(arvore != nullptr)
    {
        qtdNodeA = qtdNode(arvore->getLeft(), qtdNodeA);
        qtdNodeA = qtdNode(arvore->getRight(), qtdNodeA);
        qtdNodeA++;
    }
    return qtdNodeA;
}

int CompressorHuffman::qtdNodeTree(FrequencyData * arvore)
{
    int qtdNodeA = 0;
    return qtdNode(arvore, qtdNodeA);
}

int CompressorHuffman::achaFolha(unsigned char ** table, FrequencyData * arvore, int posFolha, int numNodeTree)
{
    //system("PAUSE");
    if(arvore != nullptr)
    {
        posFolha = achaFolha(table, arvore->getLeft(), posFolha, numNodeTree);
        posFolha = achaFolha(table, arvore->getRight(), posFolha, numNodeTree);
        //printf("\nvai verificar o if e posFolha = %d\n", posFolha);
        if(arvore->getLeft() == nullptr && arvore->getRight() == nullptr)
        {
            //printf("\npassou do if\narvore = %p arvore->parent = %p arvore->getLeft() = %p arvore->getRight() 4= %p\n", arvore, arvore->parent, arvore->getLeft(), arvore->getRight());
            int j;
            table[posFolha] = (unsigned char*)malloc(sizeof(unsigned char)*(numNodeTree+2));// esse + 2 é por causa do valor do byte e outro para o '\0' da string

            int k;
            for(k = 0; k< numNodeTree+2; k++)
            {
                table[posFolha][k] = '\0';
            }

            //printf("\nalocando table[%d] = %p\n", posFolha, table[posFolha]);
            for(j = 0; j < numNodeTree+2; j++)
            {
                if(arvore != nullptr)
                {
                    if(j == 0)
                    {
                        table[posFolha][j] = arvore->getByte();
                    }
                    else
                    {
                        if(j == numNodeTree+2 - 1)
                        {
                            table[posFolha][j] = '\0';
                        }
                        else
                        {
                            //printf("\nloop %d\narvore = %p e arvore->parent = %p\n", j, arvore, arvore->parent);
                            if(arvore->getParent()!=nullptr)  // se só tiver 1 nó será verificado antes de utilizar essa função
                            {
                                //printf("\narvore->parent->left = %p\n", arvore->parent->left);
                                if(arvore->getParent() != nullptr && arvore == arvore->getParent()->getLeft())
                                {
                                    //printf("\ndo pai foi pra esquerda\n");
                                    table[posFolha][j] = '0';
                                    arvore = arvore->getParent();
                                }
                                else
                                {
                                    //printf("\narvore->parent->right = %p\n", arvore->parent->right);
                                    if(arvore->getParent()->getRight() != nullptr && arvore == arvore->getParent()->getRight())
                                    {
                                        //printf("\ndo pai foi pra direita\n");
                                        table[posFolha][j] = '1';
                                        arvore = arvore->getParent();
                                    }
                                }
                            }
                            else
                            {
                                table[posFolha][j] = '\0';//ou é j ou j+1
                                break;
                            }
                        }
                    }
                }
            }
            posFolha++;//pois se eu entro no if quer dizer que encontrei outra folha e no fim o identificador da folha deve ser incrementado
        }
    }
    return posFolha;
}

void CompressorHuffman::invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree)
{
    unsigned char * temp = (unsigned char*)malloc(sizeof(unsigned char)*numNodeTree);
    int i, j = 1, cont = 0;
    for(i=0; i<typeNodeTree; i++)
    {
        while(table[i][j] != '\0')
        {
            temp[j-1] = table[i][j];
            j++;
            cont++;
        }
        for(j = cont-1; j>=0; j--)
        {
            table[i][cont-j] = temp[j];
        }
        j = 1;
        cont = 0;
    }
    free(temp);
}

unsigned char ** CompressorHuffman::tableTree(FrequencyData * arvore, int numNodeTree, int typeNodeTree)
{
    //int test=0;
    //printf("\nentrou na tableTree\n");
    unsigned char ** table = (unsigned char**)malloc(sizeof(unsigned char*)*typeNodeTree);/**(numNodeTree+2));isso esse pedaço eu vou alocar na outra função a cada loop*/
    /*test = */achaFolha(table, arvore, 0, numNodeTree);
    //printf("\npassou da acha folha\n");
    invertTable(table, numNodeTree, typeNodeTree);
    return table;
}


unsigned char * CompressorHuffman::divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree)
{
    unsigned char * Vector = (unsigned char*)malloc(sizeof(char) * typeNodeTree);
    unsigned char * temp = (unsigned char*)malloc(sizeof(char)*numNodeTree+3);
    int i, j;
    for(i = 0; i < typeNodeTree; i++)
    {
        Vector[i] = table[i][0];
        j = 1;
        while((table[i][j-1] != '\0') || (j-1 == 0))
        {
            temp[j-1] = table[i][j];//vai passar o de indice 1 ou seja inicio da sequencia até o fim para o temp[0] até o fim copiando também o '\0'
            j++;
        }
        j = 0;
        do
        {
            table[i][j] = temp[j];
            j++;
        }
        while(temp[j-1] != '\0');
    }
    free(temp);
    return Vector;
}

void CompressorHuffman::convertCode(unsigned char ** tabela, int qtdTiposCaracter, int numNodeTree)
{
    int i = 0, j = 0;
	//int contCaracterNome = 0;
	unsigned int sizeVectorBytes = dados.getBufferSize();
	unsigned char * vetorDeBytes = new unsigned char[sizeVectorBytes];
	unsigned char * bufferLido = new unsigned char[sizeVectorBytes];
	int posVetorDeBytes = 0;

	char stringQtdTiposCaracter[16];
	char stringNumNodeTree[16];
	
	char * extensao = dados.getExt();
	for(i = 0; extensao[i] != '\0'; i++){
		vetorDeBytes[posVetorDeBytes++] = extensao[i];
	}
	vetorDeBytes[posVetorDeBytes++] = '\0';
	
	sprintf(stringQtdTiposCaracter, "%d", qtdTiposCaracter);
	for(i = 0; stringQtdTiposCaracter[i] != '\0'; i++){
		vetorDeBytes[posVetorDeBytes++] = stringQtdTiposCaracter[i];
	}
	vetorDeBytes[posVetorDeBytes++] = '\0';

	sprintf(stringNumNodeTree, "%d", numNodeTree);
	for(i = 0; stringNumNodeTree[i] != '\0'; i++){
		vetorDeBytes[posVetorDeBytes++] = stringNumNodeTree[i];
	}
	vetorDeBytes[posVetorDeBytes++] = '\0';
	
	dadosSaida.setOpenFile(false, false);
	
	//Até esse ponto eu concidero que não vou estourar nunca o tamanho do buffer, daki em diante tem que conciderar esse caso.

	/********************************Parte para remover ******************************
	for(i = 0; nomeArquivoComprimido[i] != '\0'; i++){
		contCaracterNome++;
	}
	char * novoNome = (char*)malloc(sizeof(char)*(contCaracterNome+TAM_MAX_EXTENCAO));
	strcpy(novoNome, nomeArquivoComprimido);
    strcat(novoNome, ".hx2");
	
	FILE * arquivoComprimido = NULL;
	
    if((arquivoComprimido = fopen(novoNome, "w+b")) == NULL)
    {
        printf("\nNao foi possivel criar o arquivo %s", novoNome);
    }
	free(novoNome);
    
	fseek(arquivoComprimido, 0, SEEK_SET);
	fprintf(arquivoComprimido, "%s", extencaoArquivoDescomprimido);
	fprintf(arquivoComprimido,"%c",'\0');
    fprintf(arquivoComprimido, "%d", qtdTiposCaracter);
    fprintf(arquivoComprimido,"%c",'\0');
    fprintf(arquivoComprimido, "%d", numNodeTree);
    fprintf(arquivoComprimido,"%c",'\0');
*/

	cout << "Resultado de abertura para escrita = " << dadosSaida.getFileIsOpen() << std::endl;

	std::cout << "Tamanho do buffer = " << dados.getBufferSize() << std::endl;
//	getchar();
    for(i = 0; i < qtdTiposCaracter; i++)
    {
        for(j = 0; j==0 || tabela[i][j] != '\0'; j++)
        {
//            fprintf(arquivoComprimido, "%c", tabela[i][j]);
        }

  //      fprintf(arquivoComprimido, "%c", tabela[i][j]);
    }
/*
    for(i = 0; i < qtdTiposCaracter; i++)
    {
		cout << "Entrou no for1" << endl;

        for(j = 0; j==0 || tabela[i][j] != '\0'; j++)
        {

			getchar();
			cout << "entrou do for2" << endl;
			//vetorDeBytes[posVetorDeBytes] = tabela[i][j];
			cout  << "Posicao Atual = " << posVetorDeBytes << " i = " << i << "j = " << j << endl;
			posVetorDeBytes = (posVetorDeBytes+1)%sizeVectorBytes;//quando estourar ele retorna 0 para posVectorDeBytes, então posso gravar
			if(posVetorDeBytes == 0){
				dadosSaida.write(vetorDeBytes, sizeVectorBytes);//fwrite(vetorDeBytes, sizeof(unsigned char), sizeVectorBytes, arquivoComprimido);
			}
            fprintf(arquivoComprimido, "%c", tabela[i][j]);
        }
		vetorDeBytes[posVetorDeBytes] = tabela[i][j];
		posVetorDeBytes = (posVetorDeBytes+1)%sizeVectorBytes;//quando estourar ele retorna 0 para posVectorDeBytes, então posso gravar
		if(posVetorDeBytes == 0){
			dadosSaida.write(vetorDeBytes, sizeVectorBytes);//fwrite(vetorDeBytes, sizeof(unsigned char), sizeVectorBytes, arquivoComprimido);
		}
        fprintf(arquivoComprimido, "%c", tabela[i][j]);
    }
*/
	/*******************Fim da parte que tem que remover*************************************/
    unsigned char c;// recebe o byte lido do arquivo descomprimido
    char binario[8];// vai conter o código bit a bit
    int contBin = 0;// conta em qual bit está o código
    unsigned char gravaArquivo; //variável que vai receber o valor em ASCII equivalente do código de binário[8]
	unsigned int qtdLido = 0;
  //  fseek(arquivoDescomprimido, 0, SEEK_SET);
    //while(!feof(arquivoDescomprimido))
	//dadosSaida.setOpenFile(false, true);
	while((qtdLido = dados.read(bufferLido, sizeVectorBytes)) > 0)
    {
		for(unsigned int iBuffer = 0; iBuffer < qtdLido; iBuffer++){
		    //fscanf(arquivoDescomprimido, "%c", &c);
			c = bufferLido[iBuffer];
		    //if((qtdLido == sizeVectorBytes) || (qtdLido < sizeVectorBytes && iBuffer < (qtdLido-1)) // isso é pq se chegar no EOF significa que não é pra gravar o c por assim estaria gravando o EOF e na hora que for descomprimir e criar um novo arquivo ele terá dois EOF, o que não pode
			if((qtdLido == sizeVectorBytes) || (iBuffer < (qtdLido-1))) // isso é pq se chegar no EOF significa que não é pra gravar o c por assim estaria gravando o EOF e na hora que for descomprimir e criar um novo arquivo ele terá dois EOF, o que não pode
		    {
		        for(i = 0; i < qtdTiposCaracter; i++)
		        {
		            if(tabela[i][0] == c)
		            {
		                j = 1;
		                while(tabela[i][j] != '\0') //para gravar está aqui dentro por que ele só gravara o conteudo que ler na tabela
		                {
		                    if(contBin < 8) // quando contBin atinngir 8 implica que completou o byte e tem de converter e salvar no arquivo
		                    {
		                        binario[contBin] = tabela[i][j];//pego a sequencia contida na tabela até atingir o fim da string ou atingir o limite do byte
		                        contBin++;
		                        j++; //cada vez q salvo o codigo correspondente do caminho no binário, eu devo verificar o que tem na próxima posição da tabela
		                    }
		                    else
		                    {
		                        gravaArquivo = bintoASCII(binario);//aqui converto os '1' e '0' em sequencia no código binario correspondente
								// Trecho adicionei para enviar com rajada
								vetorDeBytes[posVetorDeBytes] = gravaArquivo;
								posVetorDeBytes = (posVetorDeBytes+1)%sizeVectorBytes;//quando estourar ele retorna 0 para posVectorDeBytes, então posso gravar
								if(posVetorDeBytes == 0){
									dadosSaida.write(vetorDeBytes, sizeVectorBytes);//fwrite(vetorDeBytes, sizeof(unsigned char), sizeVectorBytes, arquivoComprimido);
								}
		          				// Fim trecho para enviar com rajada 
								//fprintf(arquivoComprimido, "%c", gravaArquivo);// aqui estou gravando o dado convertido para byte
		                        contBin = 0;//está sendo zerado para iniciar outro byte, ele é posto igual a zero apenas quando grava no arquivo
		                    }
		                }
		                break;//ele faz o for até achar o 'c' equivalente na tabela, quando ele encontra pode encerrar o for para ler novamente outro caracter
		            }
		        }
		    }
		}
    }
    //se contBin = 4 então faltam 4 espaços para completar 1byte, pois foi inserido o 3 e em seguida foi incrementado o 4, ou seja o 4 não foi inserido,
    //se for igual a 2 então faltam 6 ou seja serão completado 8-contBin espaços
    if(contBin != 0)
    {
        for(i = contBin; i < 8; i++)
        {
            binario[i] = 0;
        }
        gravaArquivo = bintoASCII(binario);// converto o ultimo Byte junto com o padding
		vetorDeBytes[posVetorDeBytes] = gravaArquivo; 
		dadosSaida.write(vetorDeBytes, posVetorDeBytes + 1);//fwrite(vetorDeBytes, sizeof(unsigned char), posVetorDeBytes+1, arquivoComprimido);
//        fprintf(arquivoComprimido, "%c", gravaArquivo);//salvando esse byte
    }
    //agora preciso salvar quantos digitos de padding foi inserido no arquivo ou seja 8-contBin
	posVetorDeBytes = 0;
	char padding;
    sprintf(&padding, "%d", 8-contBin);//estou fazendo com %c pra ver se fica mais otimizado com menos espaço, mais pode dar mais certo com %d
	vetorDeBytes[posVetorDeBytes] = padding; 
	dadosSaida.write(vetorDeBytes, 1);
    //fclose(arquivoComprimido);
	dadosSaida.setCloseFile();
}

void CompressorHuffman::FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter){
	int i = 0;// j = 0; 
	unsigned char ** test = (*tabela);
	for(i = 0; i < qtdTiposCaracter; i++){
		free(test[i]);
	}
	free(test);
}


//funções para maniputação com binários e em ASCII

char CompressorHuffman::bintoASCII(char binario[8])
{
    int i;
    unsigned char value = 0;
    for(i = 0; i < 8; i++)
    {
        if(binario[i] == '1')
            value += pow(2, 7-i);
    }
    return value;
}

void CompressorHuffman::ascIItoBin(unsigned char let, char bin[8])
{
    int i;
    //int j;
    for(i = 0; i<8; i++)
    {

        bin[7-i] = let%2;
        let = let / 2;
    }
}

int CompressorHuffman::imprimeBIN(char t[9])
{
    int i = 0;
    int imprime = 0;
    for(i = 0; i < 8; i++)
    {
        imprime += t[7-i]*pow(10, i);
    }
    return imprime;
}

char * CompressorHuffman::toStringBin(char t[9])
{
    int i = 0;
    char * imprime = (char*)malloc(9*sizeof(char));
    for(i = 0; i < 8; i++)
    {
        if(t[i] == 1)
            t[i] = '1';
        else
            t[i] = '0';
    }
    t[8] ='\0';
    return imprime;
}

char * CompressorHuffman::getExtencaoArquivo(char * nomeArquivo){
	int i;
	int posPonto = 0;
	int contTamanhoExtencao = 0;
	for(i = strlen(nomeArquivo); i >= 0 ; i--){
		contTamanhoExtencao++;
		if(nomeArquivo[i] == '.'){
			posPonto = i;
			break;
		}
	}
	char * extencao;
	if(posPonto <= 0){
		extencao = new char[1];
		extencao[0] = '\0';
		return extencao;
	}
	extencao = new char[contTamanhoExtencao+1];
	for(i = 0; i < contTamanhoExtencao+1; i++){
		extencao[i] = nomeArquivo[posPonto+i];
	}
	return extencao;	
}


/***************************************End Protected function********************************************/

CompressorHuffman::CompressorHuffman(DadosCompressorIF & d, DadosCompressorIF & ds) : dados(d), dadosSaida(ds){
	//this->dados = dados;
}

void CompressorHuffman::setDados(DadosCompressorIF & dados){
	this->dados = dados;
}
DadosCompressorIF & CompressorHuffman::getDados(){
	return dados;
}

bool CompressorHuffman::compress(){
	//cout << "Comprimindo " << endl;
	system("echo 0 | dialog --title 'Comprimindo' --gauge '\nLendo dados' 8 40 6");
	unsigned char ** tabela = nullptr;
	FrequencyData * treeHuffman = nullptr;
	int numNodeTree = 0;
	int tiposCaracter = 0;

	tiposCaracter = vectorForHeap();
	system("(echo 10; sleep 1) | dialog --title 'Comprimindo' --gauge '\nGerando Arvore de Huffman' 8 40 6");

	treeHuffman = BuildHuffmanTree();

	system("(echo 20; sleep 1) | dialog --title 'Comprimindo' --gauge '\nIniciando Compressao' 8 40 6");
	//printHuffmanTree(treeHuffman, 0, true);
	//cout << "Raiz da Arvore = " << treeHuffman << endl;
	numNodeTree = qtdNodeTree(treeHuffman);
	//cout << "Numero de nos na arvore de Huffman = " << numNodeTree << endl; 
	//cout << "Quantidade de tipos de caracter = " << tiposCaracter << endl;
	system("(echo 25; sleep 1) | dialog --title 'Comprimindo' --gauge '\nGerando Tabela de caracteres' 8 40 6");
	tabela = tableTree(treeHuffman, numNodeTree, tiposCaracter);
	//cout << "tabela de converssao" << endl;
	//for(int i = 0; i < tiposCaracter; i++)
		//cout << tabela[i] << endl;
	//cout << "quantidade node tree =  " << numNodeTree << endl;
	system("(echo 30; sleep 1) | dialog --title 'Comprimindo' --gauge '\nConvertendo o codigo' 8 40 6");
	convertCode(tabela, tiposCaracter, numNodeTree);
	
	delete treeHuffman;
	FreeTableBytes(&tabela, tiposCaracter);
	return true;
}

bool CompressorHuffman::decompress(){
	cout << "Descomprimindo = " << dados.getCountByte('a') << " fim" << endl;
	return true;
}
		
CompressorHuffman::~CompressorHuffman(){
	cout << "Destruindo Compressor" << endl;
}
