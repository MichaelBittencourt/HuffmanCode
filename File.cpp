#include "File.h"


File::File(const char* filename){
	unsigned int i = 0;
	
	for (; filename[i] != '.' && filename[i] != '\0'; i++);
	
	if(filename[i] == '\0'){
		// error ... is not a valid file
	}
	else{
		this->filename = new char[i];
		for(unsigned k = 0; k < i; k++)
			this->filename[k] = filename[k];
		this->ext = new char[std::strlen(filename) - i];
		for(unsigned int k = 0; strlen(filename) - i; k++)
			this->ext[k] = filename[i++];		
	
	}
	std::cout << "Filename: " << this->filename << std::endl;
	std::cout << "Extension: " << this->ext << std::endl;
}

unsigned int File::getCountByte(char byte){
	// nothing
	std::string filename(this->filename);
	filename.append(this->ext);

	unsigned int frequency = 0;
	unsigned long read_bytes = 0;
	std::string buffer;
	buffer.resize(BUFFER_SIZE);

	// Open file
	std::FILE *file_pointer = std::fopen(&filename[0], "rb");
		
	if(file_pointer == nullptr){
		std::cout << "File not find! " << std::endl;
		return 0;
	}
	
	while(!feof(file_pointer)){
		if(file_pointer){
			read_bytes = std::fread(&buffer[0], sizeof(char), buffer.size(), file_pointer);
		}	
		else{
			// error
		}
		for(unsigned int i = 0; i < read_bytes; i++){
			if(buffer[i] == byte)
			frequency += 1;
		}
	}
	std::fclose(file_pointer);
	return frequency;
}

unsigned char File::getPadding(){
	std::string filename(this->filename);
	filename.append(".txt");
	unsigned char padding = '0';
	
	// Open file
	std::FILE *file_pointer = std::fopen(&filename[0], "rb");
	
	if(file_pointer == nullptr){
		//fclose(file_pointer); can't close a nullptr
		return padding;
	}
	else{
		std::fseek(file_pointer, -2, SEEK_END); // seek the end of file - 1 byte
		std::fread(&padding, sizeof(char), sizeof(char), file_pointer); // read padding
		fclose(file_pointer); // close file
	} 
	return padding;
}

unsigned int File::read(unsigned char * buffer, const unsigned int size){
	
	return 0;
}

File::~File(){
	if(frequency) 
		delete [] frequency;
	if(filename)
		delete [] filename;
}

unsigned long* File::getArrayFrequency(){
	
	std::string filename(this->filename);
	filename.append(this->ext);

	frequency = new unsigned long[256];
	unsigned long read_bytes = 0;
	std::string buffer;
	buffer.resize(BUFFER_SIZE);
	
	// init frequency array with zeros
	for (unsigned int i = 0; i < 256; i++){
		frequency[i] = 0;
	}

	// Open file
	std::FILE *file_pointer = std::fopen(&filename[0], "rb");
		
	if(file_pointer == nullptr){
		std::cout << "File not find! " << std::endl;
		return nullptr;
	}
	
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
	std::string filename(this->filename);
	filename.append(".hx2");
	
	std::FILE *file_pointer = std::fopen(&filename[0], "w");
	if(file_pointer == nullptr){
		// error could not open file for write, maybe in use?
		return;
	}
	unsigned int write_bytes = std::fwrite((const void*) ArrayDados, sizeof(char), size, file_pointer);
	std::cout << write_bytes << std::endl;
	fclose(file_pointer);
}

void File::setTypeAction(const bool typeAction){

}

void File::operator = (DadosCompressorIF & copia){

}
