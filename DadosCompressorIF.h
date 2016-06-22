#ifndef DADOS_COMPRESSOR_IF_H
#define DADOS_COMPRESSOR_IF_H



class DadosCompressorIF{
	public:
		DadosCompressorIF(){
		// empty
		}
		
		virtual unsigned int getCountByte(char byte) = 0; //Metodos Referente a leitura e escrita dos dados.
		/* Os metodos e estruturas aqui listadas devem tratar leitura e escritas dos dados, fornecendo
		o conjunto de bytes necessarios para implementação do compressor. */
		virtual unsigned long* getArrayFrequency() = 0;
		virtual unsigned char getPadding() = 0; //é um valor entre 0 e 7
		virtual unsigned int read(unsigned char * buffer, const unsigned int size) = 0; //Retorna a quantidade real de dados lidos em caso de chegar ao fim dos dados
		virtual unsigned int read(unsigned int * buffer, const unsigned int size) = 0;
		virtual void write(const unsigned char * ArrayDados, const unsigned int size) = 0;
		virtual void write(const unsigned int *ArrayDados, const unsigned int size) = 0;
		virtual void setTypeAction(const bool typeAction) = 0;
		virtual void operator = (DadosCompressorIF & copia) = 0;//colocar const eu acho. Não sei se devo colocar aqui
		virtual bool setOpenFile(bool for_read, bool append) = 0;
		virtual bool setCloseFile() = 0;
		virtual unsigned char* intToChar(unsigned int n) = 0;
		virtual unsigned int charToInt(unsigned char byte[4]) = 0;
		virtual char* getExt() = 0;
		virtual char* getFilename() = 0;
		virtual	unsigned int getBufferSize() = 0;
		virtual bool getFileIsOpen() = 0;
		virtual ~DadosCompressorIF(){
		// empty
		}
		
		//Constantes estaticas de classe destinadas ao uso com setTypeAction
		static const bool COMPRESS = true;
		static const bool DECOMPRESS = false;
		
};

#endif
