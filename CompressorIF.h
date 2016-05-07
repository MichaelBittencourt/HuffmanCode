#ifndef COMPRESSOR_IF_H
#define COMPRESSOR_IF_H

class CompressorIF{
	public:
		CompressorIF(){
		// empty
		}
		
		virtual bool compress() = 0;
		virtual bool decompress() = 0;
		
		~CompressorIF(){
		// empty
		}

};

#endif
