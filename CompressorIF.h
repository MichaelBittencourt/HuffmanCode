#ifndef COMPRESSOR_IF_H
#define COMPRESSOR_IF_H

class CompressorIF{
	public:
		CompressorIF(){
		// empty
		}
		
		virtual bool compress() = 0;  // Abstract method
		virtual bool decompress() = 0; // Abstract method
		
		virtual ~CompressorIF(){
		// empty
		}

};

#endif
