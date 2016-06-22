#ifndef FREQUENCY_DATA_H
#define FREQUENCY_DATA_H
#include <iostream>

class FrequencyData{
	
	protected:
	
		unsigned char byte_m;
		unsigned long frequency_m;
		FrequencyData* parent_m;
		FrequencyData* left_m;
		FrequencyData* right_m;

	public:

		FrequencyData();
		FrequencyData(unsigned char byte, unsigned long frequency);
		FrequencyData(unsigned char byte, unsigned long frequency, FrequencyData * parent, FrequencyData * left, FrequencyData * right);
		FrequencyData(unsigned char byte);
//		FrequencyData(FrequencyData fd);
//		FrequencyData(FrequencyData & data1, FrequencyData & data2);
		void setByte(const unsigned char byte);
		unsigned char getByte() const;
		void setFrequency(const unsigned long frequency);
		unsigned long getFrequency() const;
		void setParent(FrequencyData * & parent);
		FrequencyData * getParent() const;
		void setLeft(FrequencyData * & left);
		FrequencyData * getLeft() const;
		void setRight(FrequencyData * & right);
		FrequencyData * getRight() const;

		operator int();
		
		void operator = (const FrequencyData & fd);

		~FrequencyData();
		
};

#endif
