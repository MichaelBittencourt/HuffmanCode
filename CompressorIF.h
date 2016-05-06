#ifndef COMPRESSOR_IF_H
#define COMPRESSOR_IF_H

class CompressorIF{
	public:
		CompressorIF(){
		}
		
		virtual bool compress() = 0;
		virtual bool descompress() = 0;
		
		~CompressorIF(){
		}

};

#endif
