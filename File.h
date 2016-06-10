#include <iostream>
#include <cstdio>
#include "DadosCompressorIF.h"
#define BUFFER_SIZE 256 // 10000384


class File : public DadosCompressorIF {
public:
	File(const char* filename);
	unsigned long* getArrayFrequency();
	unsigned int getCountByte(char byte);
	void write(const unsigned char * ArrayDados, const unsigned int size);
	void setTypeAction(const bool typeAction);
	void operator = (DadosCompressorIF & copia);
	unsigned char getPadding();
	unsigned int read(unsigned char * buffer, const unsigned int size);
	~DadosCompressorIF();
private:
	unsigned long* frequency = nullptr;
	const char* filename = nullptr;
};
