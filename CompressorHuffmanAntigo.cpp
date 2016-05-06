#include "CompressorHuffmanAntigo.h"

CompressorHuffmanAntigo::CompressorHuffmanAntigo(){
	nomeArquivoEntrada = NULL;
	nomeArquivoSaida = NULL;
}
		
CompressorHuffmanAntigo::CompressorHuffmanAntigo(char nomeArquivoEntrada[], char nomeArquivoSaida[]){
	this->nomeArquivoEntrada = nomeArquivoEntrada;
	this->nomeArquivoSaida = nomeArquivoSaida;
}


void CompressorHuffmanAntigo::inOrder(struct Node *root)
{
    if(root != NULL)
    {
        inOrder(root->left);
        //printf("\nlista->no-valor = %c\nlista->no->frequencia = %d\nlista->no = %p\nlista->no->parent = %p \nlista->no->left = %p\nlista->no->right = %p\n",root->value, root->frequencia, root, root->parent,root->left,root->right);//para debug
        printf("Valor: %c :: Frequencia: %d\n",root->value,root->frequencia);
        inOrder(root->right);
    }
}
int CompressorHuffmanAntigo::getByteFrequency(FILE* arq, struct Node **root)
{
    int tiposDeCaracteres = 0;
    unsigned char c;
    while(!feof(arq))
    {
        fscanf(arq, "%c", &c);
        if(!feof(arq))
            tiposDeCaracteres = AddNode(root, c, tiposDeCaracteres);
    }
    //c = EOF;
    //AddNode(root, c);
    return tiposDeCaracteres;
}

int CompressorHuffmanAntigo::AddNode(Node** root, char value, int tiposDeCaracteres)
{
    if((*root) == NULL)
    {
        (*root) = (Node*)malloc(sizeof(Node));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->value = value;
        (*root)->frequencia = 1;
        tiposDeCaracteres++;
    }

    else
    {
        if(value==(*root)-> value)
            (*root)->frequencia++;
        else
        {
            if(value>(*root)->value)
                tiposDeCaracteres = AddNode(&(*root)->right,value, tiposDeCaracteres);
            else
                tiposDeCaracteres = AddNode(&(*root)->left,value, tiposDeCaracteres);
        }
    }
    return tiposDeCaracteres;
}
void CompressorHuffmanAntigo::treeToList_L(Node* n, ListaDENode** head, ListaDENode** tail)
{
    if((*head) == NULL)
    {
        (*head) = (ListaDENode*)malloc(sizeof(ListaDENode));
        //(*head)->no = n;// se fosse ao contrário tiraria-se as próximas 3 linhas
        (*head)->no = (Node*)malloc(sizeof(Node));
        (*head)->no->frequencia = n->frequencia;
        (*head)->no->value = n->value;
        (*head)->no->left = NULL;
        (*head)->no->right = NULL;
        (*head)->no->parent = NULL;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        *tail = *head;
    }
    else
    {
        ListaDENode* temp=NULL;
        temp = (ListaDENode*)malloc(sizeof(ListaDENode));
        //temp->no = n;
        temp->no = (Node*)malloc(sizeof(Node));
        temp->no->value = n->value;
        temp->no->frequencia = n->frequencia;
        temp->no->left = NULL;
        temp->no->right = NULL;
        temp->no->parent = NULL;
        temp->prev = (*tail);
        temp->next = NULL;
        (*tail)->next=temp;
        (*tail) = temp;
    }
}

void CompressorHuffmanAntigo::walkTree_L(struct Node *root, ListaDENode ** head, ListaDENode** tail)
{
    if(root != NULL)
    {
        walkTree_L(root->left,head,tail);
        treeToList_L(root,head,tail);
        walkTree_L(root->right,head,tail);
    }
}

void CompressorHuffmanAntigo::InsertionSort_L(ListaDENode* node)
{
    ListaDENode *aux1=NULL, *aux2=NULL, *temp = NULL;
    Node* eleito=NULL;

    for(aux1 = node->next ; aux1!=NULL ; aux1=aux1->next)
    {
        eleito = aux1->no;
        aux2 = aux1->prev;
        temp = aux2;
        while((aux2!=NULL) && (eleito->frequencia < aux2->no->frequencia))
        {
            aux2->next->no = aux2->no;
            temp = aux2;
            aux2 = aux2->prev;
        }
        if(aux2 != NULL)
        {
            aux2->next->no = eleito;
        }
        else
        {
            temp->no = eleito;
        }
    }
}
void CompressorHuffmanAntigo::inOrderList_L(ListaDENode *root)
{
    if(root != NULL)
    {
        //printf("\nlista->no-valor = %c\nlista->no->frequencia = %d\nlista->no = %p\nlista->no->parent = %p \nlista->no->left = %p\nlista->no->right = %p\n",lista->no->value, lista->no->frequencia, lista->no, lista->no->parent,lista->no->left,lista->no->right);//para debug
        printf("Valor: %c :: Frequencia: %d\n",root->no->value,root->no->frequencia);
        inOrderList_L(root->next);
    }
}

Node * CompressorHuffmanAntigo::BuildHuffmanTree(ListaDENode* lista, Node* arvore)
{
    Node * menor1 = NULL;
    Node * menor2 = NULL;
    Node * temp = NULL;
    InsertionSort_L(lista);
    //inOrderList_L(lista);
    while(lista->next != NULL)
    {
        menor1 = lista->no;
        menor2 = lista->next->no;
        lista = lista->next;
        temp = (Node*)malloc(sizeof(Node));
        temp->left = menor1;
        menor1->parent = temp;// indicando pai
        temp->right = menor2;
        menor2->parent = temp;// indicando pai
        temp->value = 0;
        temp->frequencia = menor1->frequencia + menor2->frequencia;
        lista->no = temp;
        //printf("\nAntes do InsertionSort\nlista->no->value = %c\nlista->no = %p\nlista->no->left = %p\nlista->no->right = %p\nlista->no->parent = %p\n", lista->prev->no->value,lista->prev->no, lista->no->left, lista->no->right, lista->no->parent);
        InsertionSort_L(lista);
        //lista->no = temp;
        //printf("\nDepois do InsertionSort\nlista->no->value = %c\nlista->no = %p\nlista->no->left = %p\nlista->no->right = %p\nlista->no->parent = %p\n", lista->no->value, lista->no, lista->no->left, lista->no->right, lista->no->parent);
        //system("PAUSE");
    }
    //arvore = lista->no;
    lista->no->parent == NULL;// tem que fazer isso fora;
    //inOrder(lista->no);
    return lista->no;
}

int CompressorHuffmanAntigo::qtdNode(Node * arvore, int qtdNodeA)
{
    if(arvore != NULL)
    {
        qtdNodeA = qtdNode(arvore->left, qtdNodeA);
        qtdNodeA = qtdNode(arvore->right, qtdNodeA);
        qtdNodeA++;
    }
    return qtdNodeA;
}

int CompressorHuffmanAntigo::qtdNodeTree(Node *arvore)
{
    int qtdNodeA = 0;
    return qtdNode(arvore, qtdNodeA);
}

int CompressorHuffmanAntigo::achaFolha(unsigned char ** table, Node * arvore, int posFolha, int numNodeTree)
{
    //system("PAUSE");
    if(arvore != NULL)
    {
        posFolha = achaFolha(table, arvore->left, posFolha, numNodeTree);
        posFolha = achaFolha(table, arvore->right, posFolha, numNodeTree);
        //printf("\nvai verificar o if e posFolha = %d\n", posFolha);
        if(arvore->left == NULL && arvore->right == NULL)
        {
            //printf("\npassou do if\narvore = %p arvore->parent = %p arvore->left = %p arvore->right 4= %p\n", arvore, arvore->parent, arvore->left, arvore->right);
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
                if(arvore != NULL)
                {
                    if(j == 0)
                    {
                        table[posFolha][j] = arvore->value;
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
                            if(arvore->parent!=NULL)  // se só tiver 1 nó será verificado antes de utilizar essa função
                            {
                                //printf("\narvore->parent->left = %p\n", arvore->parent->left);
                                if(arvore->parent != NULL && arvore == arvore->parent->left)
                                {
                                    //printf("\ndo pai foi pra esquerda\n");
                                    table[posFolha][j] = '0';
                                    arvore = arvore->parent;
                                }
                                else
                                {
                                    //printf("\narvore->parent->right = %p\n", arvore->parent->right);
                                    if(arvore->parent->right != NULL && arvore == arvore->parent->right)
                                    {
                                        //printf("\ndo pai foi pra direita\n");
                                        table[posFolha][j] = '1';
                                        arvore = arvore->parent;
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

void CompressorHuffmanAntigo::invertTable(unsigned char ** table, int numNodeTree, int typeNodeTree)
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

unsigned char ** CompressorHuffmanAntigo::tableTree(Node * arvore, int numNodeTree, int typeNodeTree)
{
    int test=0;
    //printf("\nentrou na tableTree\n");
    unsigned char ** table = (unsigned char**)malloc(sizeof(unsigned char*)*typeNodeTree);/**(numNodeTree+2));isso esse pedaço eu vou alocar na outra função a cada loop*/
    test = achaFolha(table, arvore, 0, numNodeTree);
    //printf("\npassou da acha folha\n");
    invertTable(table, numNodeTree, typeNodeTree);
    return table;
}

unsigned char * CompressorHuffmanAntigo::divideTableVector(unsigned char ** table, int numNodeTree, int typeNodeTree)
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

void CompressorHuffmanAntigo::tabelaToTree(unsigned char ** table, Node ** huffmanTree, int numNodeTree, int typeNodeTree)
{
    int i, j;
    Node * nodeTemp = (*huffmanTree);
    nodeTemp = (Node*)malloc(sizeof(Node));
//	printf(\nnodeTemp
    nodeTemp->value = 0;
    nodeTemp->frequencia = 0;
    nodeTemp->left = NULL;
    nodeTemp->right = NULL;
    nodeTemp->parent = NULL;
    (*huffmanTree) = nodeTemp;

    //char * VectorValue = divideTableVector(table, numNodeTree, typeNodeTree);
    for(i = 0; i < typeNodeTree; i++)
    {
        //for(j = 1; (j < numNodeTree+2 - 1) && (table[i][j] != '\0'); j++)
        for(j = 1; (j < numNodeTree-1) && (table[i][j] != '\0'); j++)
        {

            if(table[i][j] == '1')
            {
                if(nodeTemp->right == NULL)
                {
                    nodeTemp->right = (Node*)malloc(sizeof(Node));
                    nodeTemp->right->value = 0;
                    nodeTemp->right->frequencia = 0;
                    nodeTemp->right->left = NULL;
                    nodeTemp->right->right = NULL;
                    nodeTemp->right->parent = nodeTemp;
                }
                nodeTemp = nodeTemp->right;
            }
            else
            {
                if(table[i][j] == '0')
                {
                    if(nodeTemp->left == NULL)
                    {
                        nodeTemp->left = (Node*)malloc(sizeof(Node));
                        nodeTemp->left->value = 0;
                        nodeTemp->left->frequencia = 0;
                        nodeTemp->left->left = NULL;
                        nodeTemp->left->right = NULL;
                        nodeTemp->left->parent = nodeTemp;
                    }
                    nodeTemp = nodeTemp->left;
                }
            }
        }
        nodeTemp->value = table[i][0];
        nodeTemp = (*huffmanTree);
    }
}
/*
-------------Obs: Sequencia de gravação da próxima função---------------

1) qtdTiposCaracter %d
2) numNodeTree      %d
3) cada elemento table[i][j] em %c //teram que ser realocados no momento da descompressão
4) conteudo do arquivo comprimido em %c
5) restante do conteudo com padding em %c
6) quantidade de bits de padding que foram inseridos em %c

Na leitura para descompressão, a ordem tem de ser mantida
*/

void CompressorHuffmanAntigo::convertCode(FILE * arquivoDescomprimido, unsigned char ** tabela, char *nomeArquivoComprimido, int qtdTiposCaracter, int numNodeTree, char * extencaoArquivoDescomprimido)
{
    int i = 0, j = 0;
	int contCaracterNome = 0;
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

    for(i = 0; i < qtdTiposCaracter; i++)
    {
        for(j = 0; j==0 || tabela[i][j] != '\0'; j++)
        {
            fprintf(arquivoComprimido, "%c", tabela[i][j]);
        }

        fprintf(arquivoComprimido, "%c", tabela[i][j]);
    }

    unsigned char c;// recebe o byte lido do arquivo descomprimido
    char binario[8];// vai conter o código bit a bit
    int contBin = 0;// conta em qual bit está o código
    unsigned char gravaArquivo; //variável que vai receber o valor em ASCII equivalente do código de binário[8]
    fseek(arquivoDescomprimido, 0, SEEK_SET);
    while(!feof(arquivoDescomprimido))
    {
        fscanf(arquivoDescomprimido, "%c", &c);
        if(!feof(arquivoDescomprimido)) // isso é pq se chegar no EOF significa que não é pra gravar o c por assim estaria gravando o EOF e na hora que for descomprimir e criar um novo arquivo ele terá dois EOF, o que não pode
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
                            fprintf(arquivoComprimido, "%c", gravaArquivo);// aqui estou gravando o dado convertido para byte
                            contBin = 0;//está sendo zerado para iniciar outro byte, ele é posto igual a zero apenas quando grava no arquivo
                        }
                    }
                    break;//ele faz o for até achar o 'c' equivalente na tabela, quando ele encontra pode encerrar o for para ler novamente outro caracter
                }
            }
        }
    }
    /*se contBin = 4 então faltam 4 espaços para completar 1byte, pois foi inserido o 3 e em seguida foi incrementado o 4, ou seja o 4 não foi inserido,
    se for igual a 2 então faltam 6 ou seja serão completado 8-contBin espaços*/
    if(contBin != 0)
    {
        for(i = contBin; i < 8; i++)
        {
            binario[i] = 0;
        }
        gravaArquivo = bintoASCII(binario);// converto o ultimo Byte junto com o padding
        fprintf(arquivoComprimido, "%c", gravaArquivo);//salvando esse byte
    }
    //agora preciso salvar quantos digitos de padding foi inserido no arquivo ou seja 8-contBin
    fprintf(arquivoComprimido, "%d", 8-contBin);//estou fazendo com %c pra ver se fica mais otimizado com menos espaço, mais pode dar mais certo com %d
    fclose(arquivoComprimido);
}

void CompressorHuffmanAntigo::CompressFile(char * nomeArquivoDescomprimido, char nomeArquivoComprimido[])
{
    //inicializando variaveis
    ListaDENode * listaDeBytes = NULL;
    ListaDENode * tail = NULL;
    Node * root = NULL;
    Node * treeHuffman = NULL;
    FILE * arquivoDescomprimido = NULL;
    int TiposCaracter = 0;
    unsigned char ** tabela = NULL;
    int numNodeTree = 0;

    //recebendo frequencias na arvore, transferindo para lista, contando quantos tipos diferentes de bytes contem na arvore e liberando a arvore
    if((arquivoDescomprimido = fopen(nomeArquivoDescomprimido, "rb")) == NULL)
    {
        printf("\nErro ao abrir arquivo %s", nomeArquivoDescomprimido);
        exit(1);
    }
	printf("\n-----------------------Lendo Arquivo---------------------------------");
	printf("\n---------------Analizando frequencia de bytes------------------------");
    TiposCaracter = getByteFrequency(arquivoDescomprimido,&root);
    fclose(arquivoDescomprimido);
    walkTree_L(root, &listaDeBytes, &tail);
    //criar função liberaArvore e liberar root

    //montando arvore de huffman e gerando tabela de correspondencia de valores
	printf("\n-----------------Criando a arvore de Huffman-------------------------");
    treeHuffman = BuildHuffmanTree(listaDeBytes, treeHuffman);
    treeHuffman->parent = NULL;

    numNodeTree = qtdNodeTree(treeHuffman);
	printf("\n---------Criando a Tabela de bytes com a arvore de Huffman-----------");
    tabela = tableTree(treeHuffman, numNodeTree, TiposCaracter);

    //iniciar precesso de conversão dos dados e armazenamento do arquivo comprimido
    if((arquivoDescomprimido = fopen(nomeArquivoDescomprimido, "rb")) == NULL)
    {
        printf("\nErro ao abrir arquivo %s", nomeArquivoDescomprimido);
        exit(1);
    }
	printf("\n-----------------------Comprimindo arquivo!--------------------------\n");
    convertCode(arquivoDescomprimido, tabela, nomeArquivoComprimido, TiposCaracter, numNodeTree, getExtencaoArquivo(nomeArquivoDescomprimido));
	printf("\n-----------------Arquivo comprimido com sucesso!---------------------\n");
    fclose(arquivoDescomprimido);
	
	FreeHuffmanTree(&root);
	printf("\nFree root");
	FreeListValue(&listaDeBytes);
	printf("\nFree listaDEBytes");
	//free(tail);
	//printf("\nFree tail");
	FreeTableBytes(&tabela, TiposCaracter);
    printf("\nFree tabela\n");

}
void CompressorHuffmanAntigo::DescompressFile(char ArquivoDescomprimido[], char ArquivoComprimido[])
{
    FILE* arqComprimido=NULL;
    FILE* arqDescomprimido = NULL;
    int qtdTiposCaracter,i,j,padding=200;
    unsigned char **tabela;
    unsigned char c;
    int numNodeTree;
    char extencaoArquivo[TAM_MAX_EXTENCAO];
    for(int i = 0; i < TAM_MAX_EXTENCAO; i++){
    	extencaoArquivo[i] = '\0';
	}
    char * ArquiDescomprimidoExtencao = (char*)malloc(sizeof(char)*(strlen(ArquivoDescomprimido)+TAM_MAX_EXTENCAO));

    printf("\nArquivoComprimido: %s",ArquivoComprimido);

    arqComprimido = fopen(ArquivoComprimido,"r+b");
    if(arqComprimido == NULL){
        printf("\nNao foi possivel abrir o arquivo %s",ArquivoComprimido);
        exit(1);
    }
    fseek(arqComprimido,-sizeof(char),SEEK_END);// acho que é int mais funciona com char pois padding nunca é maior que 7
    fscanf(arqComprimido,"%d",&padding);
    printf("\nO Padding lido foi: %d",padding);

    fseek(arqComprimido,0,SEEK_SET);
	for(int i = 0; i < TAM_MAX_EXTENCAO; i++){
		fscanf(arqComprimido,"%c",&extencaoArquivo[i]);
		if(extencaoArquivo[i] == '\0')
			break;
	}
    fscanf(arqComprimido,"%d",&qtdTiposCaracter);
    fseek(arqComprimido,sizeof(char),1);
    fscanf(arqComprimido,"%d",&numNodeTree);
    fseek(arqComprimido,sizeof(char),1);
    printf("\nQtdTiposCaracteres: %d",qtdTiposCaracter);

    printf("\nnumNodeTree: %d",numNodeTree);
    printf("\n");
    
    tabela = (unsigned char**)malloc(sizeof(unsigned char*)*qtdTiposCaracter);

    for(i = 0;i<qtdTiposCaracter;i++)
        tabela[i] = (unsigned char*)malloc(sizeof(unsigned char)*numNodeTree);

    for(i=0;i<qtdTiposCaracter;i++){
        for(j=0;j<numNodeTree;j++){
            fscanf(arqComprimido,"%c", &c);

            if(j != 0 && c == '\0'){
                tabela[i][j] = c;
                if(j<numNodeTree-1)
                fseek(arqComprimido, -sizeof(unsigned char), SEEK_CUR);
            }
            else{
                tabela[i][j] = c;
            }
        }
    }
        printf("\nA leitura da tabela foi realizada com sucesso\n");

        printf("\n---------Criando a arvore de Huffman pela Tabela-----------");
        Node* huffmanTree = NULL;
        tabelaToTree(tabela, &huffmanTree,numNodeTree,qtdTiposCaracter);

        printf("\n----------------Arvore criada com sucesso!-----------------");

        printf("\n---------Iniciando leitura do arquivo comprimido-----------\n");
		
		
		strcpy(ArquiDescomprimidoExtencao, ArquivoDescomprimido);
		strcat(ArquiDescomprimidoExtencao, extencaoArquivo);
        arqDescomprimido = fopen(ArquiDescomprimidoExtencao,"w+b");
        char bin[8];
        Node* temp=NULL;
        temp = huffmanTree;
		int test = 0;
		int cont = -1;// igual a -1 pois padding não pode ser igual a -1 logo de inicio, porem ele poderia ser igual a 0
		unsigned char gambiarra;
    while(!feof(arqComprimido))
    {

        fscanf(arqComprimido,"%c",&c);

		fscanf(arqComprimido, "%c", &gambiarra);
		if(!feof(arqComprimido)){
			fscanf(arqComprimido, "%c", &gambiarra);
			if(feof(arqComprimido)){
				cont = padding;
			}
			fseek(arqComprimido,-sizeof(char),1);
			fseek(arqComprimido,-sizeof(char),1);

			ascIItoBin(c,bin);

			for(i=0; i<8-cont; i++)
			{
				if(bin[i] == 1)
				{
					temp = temp->right;
				}

				if(bin[i] == 0)
				{
					temp = temp->left;
				}
				if(temp->left == NULL && temp->right == NULL)
				{
					fprintf(arqDescomprimido,"%c",temp->value);
					temp = huffmanTree;
				}
			}
			if(cont == padding){//por conta da gambiarra
				break;
			}
		}
		else{
			break;
		}
    }
printf("\n------------Arquivo descomprimido com sucesso!-------------\n");


	FreeHuffmanTree(&huffmanTree);
    printf("\nfree huffmanTree");
	FreeTableBytes(&tabela, qtdTiposCaracter);
    printf("\nfree tabela\n");
}

void CompressorHuffmanAntigo::FreeHuffmanTree(Node ** arvore){
	if((*arvore) != NULL){
		FreeHuffmanTree(&((*arvore)->left));
		FreeHuffmanTree(&((*arvore)->right));
		free((*arvore));
	}
}

void CompressorHuffmanAntigo::FreeListValue(ListaDENode ** lista){
	if((*lista) != NULL){
		FreeListValue(&((*lista)->next));
		free((*lista));
	}
}

void CompressorHuffmanAntigo::FreeTableBytes(unsigned char *** tabela, int qtdTiposCaracter){
	int i = 0, j = 0; 
	unsigned char ** test = (*tabela);
	for(i = 0; i < qtdTiposCaracter; i++){
		free(test[i]);
	}
	free(test);
}


//funções para maniputação com binários e em ASCII

char CompressorHuffmanAntigo::bintoASCII(char binario[8])
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

void CompressorHuffmanAntigo::ascIItoBin(unsigned char let, char bin[8])
{
    int i;
    int j;
    for(i = 0; i<8; i++)
    {

        bin[7-i] = let%2;
        let = let / 2;
    }
}

int CompressorHuffmanAntigo::imprimeBIN(char t[9])
{
    int i = 0;
    int imprime = 0;
    for(i = 0; i < 8; i++)
    {
        imprime += t[7-i]*pow(10, i);
    }
    return imprime;
}

char * CompressorHuffmanAntigo::toStringBin(char t[9])
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

char * CompressorHuffmanAntigo::getExtencaoArquivo(char * nomeArquivo){
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


void CompressorHuffmanAntigo::setNomeArquivoEntrada(char * nomeArquivoEntrada){
	this->nomeArquivoEntrada = nomeArquivoEntrada;
}
char * CompressorHuffmanAntigo::getNomeArquivoEntrada(){
	return nomeArquivoEntrada;
}

void CompressorHuffmanAntigo::setNomeArquivoSaida(char * nomeArquivoSaida){
	this->nomeArquivoSaida = nomeArquivoSaida;
}
char * CompressorHuffmanAntigo::getNomeArquivoSaida(){
	return nomeArquivoSaida;
}

bool CompressorHuffmanAntigo::compress(){
	CompressFile(nomeArquivoEntrada, nomeArquivoSaida);
	return true;
}
bool CompressorHuffmanAntigo::descompress(){
	DescompressFile(nomeArquivoSaida, nomeArquivoEntrada);
	return true;
}

CompressorHuffmanAntigo::~CompressorHuffmanAntigo()
{
}
