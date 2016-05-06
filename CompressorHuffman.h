class CompressorHuffman : public CompressorIF{
	
	protected:
		DadosCompressorIF dados;
	
	public:
		void CompressorHuffman();
		
		~CompressorHuffman();
}