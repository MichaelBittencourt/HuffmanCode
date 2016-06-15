#include <iostream>
#include <cstdio>
#include <cstring>
#include "DadosCompressorIF.h"
#define BUFFER_SIZE 256 // 10000384


class File : public DadosCompressorIF {
public:
	File(const char* filename);
	unsigned long* getArrayFrequency();
	unsigned int getCountByte(char byte);
	
	void write(const unsigned char* ArrayDados, const unsigned int size);
	void write(const unsigned int *ArrayDados, const unsigned int size);
	void setTypeAction(const bool typeAction);
	void operator = (DadosCompressorIF & copia);
	unsigned char getPadding();
	unsigned int read(unsigned char * buffer, const unsigned int size);
	unsigned int read(unsigned int * buffer, const unsigned int size);
	bool setOpenFile(bool for_read, bool append);
	bool setCloseFile();
	char* getExt() const;
	~File();
private:
	unsigned long* frequency = nullptr;
	char* filename = nullptr;
	char* ext = nullptr;
	FILE* file_pointer = nullptr;
	bool file_is_open = false;
	bool append = false;
	
};
