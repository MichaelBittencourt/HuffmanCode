class DadosCompressorIF{
	public:
		virtual void DadosCompressorIF() = 0;
		virtual getCountByte(char byte) = 0;//Metodos Referente a leitura e escrita dos dados.
		/*Os metodos e estruturas aqui listadas devem tratar leitura e escritas dos dados, fornecendo
		o conjunto de bytes necessarios para implementação do compressor.*/
		virtual void operator = (DadosCompressorIF copia) = 0;//colocar const eu acho. Não sei se devo colocar aqui
		virtual ~DadosCompressorIF() = 0;
}
