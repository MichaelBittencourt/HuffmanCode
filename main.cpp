#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CompressorIF.h"
#include "CompressorHuffmanAntigo.h"
#include "CompressorHuffman.h"
#include "File.h"

//#define DEBUG

#ifdef DEBUG

int main(){

	File file("test.txt");
	
	unsigned long* array_frequency = file.getArrayFrequency();


	for(int i = 0; i < 256; i++){
		std::cout << array_frequency[i] << std::endl;
	}
	
	return 0;
}

#else
using namespace std;

int main(int argc, char *args[])
{

	
	if(argc != 4)
    {
        printf("\nParametros invalidos\n");
        exit(1);
    }
    else
    {
    	/***************For this compressor ******************/
		//CompressorIF * compressor =  new CompressorHuffmanAntigo(args[2], args[3]);
		//DadosTest d;
		//DadosCompressorIF & dados(d);// = new DadosTest();		
		//CompressorIF * compressor =  new CompressorExemplo(*(new DadosTest()));
		CompressorIF * compressor =  new CompressorHuffman(*(new File(args[2])), *(new File(args[3])));
    	/***************For this compressor ******************/
				
        if(strcmp(args[1], "-c")==0)
        {
        	// to compress file CompressFile(args[2], args[3]) 	 	
			compressor->compress();
        }
        else
        {
            if(strcmp(args[1], "-x")==0)
            {
            	// to decompress file DecompressFile(args[3],args[2])
                 compressor->decompress();
            }
            else
            {
                printf("\nParametros invalidos\n");
                exit(1);
            }
        }
		delete compressor;
    }
    return EXIT_SUCCESS;
}
#endif
