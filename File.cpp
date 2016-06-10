#include "File.h"


File::File(const char* filename){
	this->filename = filename;
}

unsigned int File::getCountByte(char byte){
	// nothing
	return 0;
}

unsigned char File::getPadding(){
	return 0;
}

unsigned int File::read(unsigned char * buffer, const unsigned int size){

	return 0;
}

File::~DadosCompressorIF(){
	if(frequency) 
		delete [] frequency;
	if(filename)
		delete [] filename;
}

unsigned long* File::getArrayFrequency(){

	frequency = new unsigned long[256];
	unsigned long read_bytes = 0;
	std::string buffer;
	buffer.resize(BUFFER_SIZE);
	
	// init frequency array with zeros
	for (unsigned int i = 0; i < 256; i++){
		frequency[i] = 0;
	}

	// Open file
	std::FILE * file_pointer = std::fopen(filename, "rb");	
	
	
	while(!feof(file_pointer)){
		if(file_pointer){
			read_bytes = std::fread(&buffer[0], sizeof(char), buffer.size(), file_pointer);
		}	
		else{
			// error
		}
		for(unsigned int i = 0; i < read_bytes; i++){
			frequency[(unsigned char)buffer[i]] += 1;
		}
	}
	std::fclose(file_pointer);
	return frequency;
}

void File::write(const unsigned char * ArrayDados, const unsigned int size){

}

void File::setTypeAction(const bool typeAction){

}

void File::operator = (DadosCompressorIF & copia){

}
