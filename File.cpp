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
	filename.append(this->ext);
	unsigned char padding = '0';
	
	// Open file
	std::FILE *file_pointer = std::fopen(&filename[0], "rb");
	
	if(file_pointer == nullptr){
		//fclose(file_pointer); can't close a nullptr
		std::cout << "Couln't open file for getPadding() " << std::endl;
		return padding;
	}
	else{
		std::fseek(file_pointer, -2, SEEK_END); // seek the end of file - 2 byte
		std::fread(&padding, sizeof(char), sizeof(char), file_pointer); // read padding
		fclose(file_pointer); // close file
	} 
	return padding;
}

unsigned int File::read(unsigned char *buffer, const unsigned int size){

	if(file_is_open) {
		return std::fread(buffer, sizeof(char), size, this->file_pointer);
		
	}
	std::cout << "File not open" << std::endl;
	return 0;
}

unsigned int File::read(unsigned int *buffer, const unsigned int size){
	if(file_is_open) {
		return std::fread(buffer, sizeof(unsigned int), size, this->file_pointer);
	}
	std::cout << "File not open" << std::endl;
	return 0;
}

File::~File(){
	if(file_pointer)
		delete file_pointer;
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
		std::cout << "File not find! getArrayFrequency()" << std::endl;
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

char File::getExt() const {
	return (*this->ext);
}

void File::write(const unsigned char *ArrayDados, const unsigned int size){
	std::string filename(this->filename);
	filename.append(this->ext);
	if(file_is_open){
		unsigned int write_bytes = std::fwrite((const void*) ArrayDados, sizeof(char), size, file_pointer);
		std::cout << write_bytes << std::endl;
	}
	else{
		std::cout << "File not open" << std::endl;
		return;
	}
}


void File::write(const unsigned int *ArrayDados, const unsigned int size){
	if(file_is_open){
		unsigned int write_bytes = std::fwrite((const void*) ArrayDados, sizeof(int), size, file_pointer);
		std::cout << write_bytes << std::endl;
	}
	else{
		// error flag is not true
		std::cout << "File not open" << std::endl;
	}
}

void File::setTypeAction(const bool typeAction){

}

void File::operator = (DadosCompressorIF & copia){

}

bool File::setOpenFile(bool for_read, bool append){
	std::string filename(this->filename);
	filename.append(this->ext);
	this->append = append;
	
	if(for_read) {
		this->file_pointer = std::fopen(&filename[0], "r");
	}
	else {
		if(append)
			this->file_pointer = std::fopen(&filename[0], "a");
		else
			this->file_pointer = std::fopen(&filename[0], "w");
	}
	
	if(this->file_pointer) {
		file_is_open = true;
		return true;
	}
	
	else {
		file_is_open = false;
		return false;
	}
	return false;
}
bool File::setCloseFile(){
	if(file_is_open){
		fclose(this->file_pointer);	
		return true;
	}
	return false; // file already close
}

