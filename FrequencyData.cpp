
#include "FrequencyData.h"

FrequencyData::FrequencyData(){
	byte_m = 0;
	frequency_m = 0;
	parent_m = nullptr;
	left_m = nullptr;
	right_m = nullptr;
}

FrequencyData::FrequencyData(unsigned char byte, unsigned long frequency){
	byte_m = byte;
	frequency_m = frequency;
	parent_m = nullptr;
	left_m = nullptr;
	right_m = nullptr;
}

FrequencyData::FrequencyData(unsigned char byte, unsigned long frequency, FrequencyData * parent, FrequencyData * left, FrequencyData * right){
	byte_m = byte;
	frequency_m = frequency;
	parent_m = parent;
	left_m = left;
	right_m = right;
}

FrequencyData::FrequencyData(unsigned char byte){
	byte_m = byte;
	frequency_m = 0;
	parent_m = nullptr;
	left_m = nullptr;
	right_m = nullptr;
}

/*FrequencyData::FrequencyData(FrequencyData  fd){
	byte_m = fd.byte_m;
	frequency_m = fd.frequency_m;
	parent_m = fd.parent_m;
	left_m = fd.left_m;
	right_m = fd.right_m;
}*/

void FrequencyData::setByte(const unsigned char byte){
	byte_m = byte;
}

unsigned char FrequencyData::getByte() const{
	return byte_m;
}

void FrequencyData::setFrequency(const unsigned long frequency){
	frequency_m = frequency;
}

unsigned long FrequencyData::getFrequency() const{
	return frequency_m;
}

void FrequencyData::setParent(FrequencyData * & parent){
	parent_m = parent;
}

FrequencyData *  FrequencyData::getParent() const{
	return parent_m;
}

void FrequencyData::setLeft(FrequencyData * & left){
	left_m = left;
}

FrequencyData * FrequencyData::getLeft() const{
	return left_m;
}

void FrequencyData::setRight(FrequencyData * & right){
	right_m = right;
}

FrequencyData * FrequencyData::getRight() const{
	return right_m;
}

FrequencyData::operator int(){
	return frequency_m;
}

void FrequencyData::operator = (const FrequencyData & fd){
	byte_m = fd.byte_m;
	frequency_m = fd.frequency_m;
	parent_m = fd.parent_m;
	left_m = fd.left_m;
	right_m = fd.right_m;
//	return *this;
}
