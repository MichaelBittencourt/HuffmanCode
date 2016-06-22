#include "File.h"


File::File(const char* filename){
	unsigned int i = 0;
//	for (; filename[i] != '.' && filename[i] != '\0'; i++);
	for(i = strlen(filename); i >= 0 ; i--){
		if(filename[i] == '.'){
			break;
		}
	}
	
	if(i < 0){
		// error ... is not a valid file
	}
	else{
		this->filename = new char[i+1];
		for(unsigned int k = 0; k < i; k++)
			this->filename[k] = filename[k];
		this->filename[i] = '\0';

		this->ext = new char[std::strlen(filename) - i+1];
		unsigned int k = 0;
		for(; strlen(filename) - i; k++) //Renno doido do krai.rsrsrsrs Essa porra pega pq ele incrementa o i quando i = strlen o loop quebra.
			this->ext[k] = filename[i++];
		this->ext[k] = '\0';
	
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

unsigned char* File::intToChar(unsigned int n){
	unsigned char *bytes = new unsigned char(4);
	bytes[0] = (n >> 24) & 0xFF;
	bytes[1] = (n >> 16) & 0xFF;
	bytes[2] = (n >> 8) & 0xFF;
	bytes[3] = n & 0xFF;
	return bytes;
}

unsigned int File::charToInt(unsigned char byte[4]){
	unsigned int num;
	num = (byte[0] << 24) + (byte[1] << 16) + (byte[2] << 8) + byte[3];
	return num;
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

char* File::getExt(){
	return this->ext;
}

char* File::getFilename(){
	return this->filename;

}

void File::write(const unsigned char *ArrayDados, const unsigned int size){
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
	std::string ext(this->ext);
	filename += ext;
	std::cout << "Nome Arquivo para Abrir = " << filename << std::endl;
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
		this->file_is_open = true;
		return true;
	}
	
	else {
		file_is_open = false;
		return false;
	}
	return false;
}
bool File::setCloseFile(){
	if(this->file_is_open){
		this->file_is_open = false;
		fclose(this->file_pointer);	
		return true;
	}
	return false; // file already close
}

unsigned int File::getBufferSize(){
	return BUFFER_SIZE;
}

bool File::getFileIsOpen(){
	return file_is_open;
}

