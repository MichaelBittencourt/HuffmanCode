#include<stdio.h>
#include<stdlib.h>
#include "CompressorIF.h"
#include "CompressorHuffmanAntigo.h"
#include "CompressorHuffman.h"
#include "CompressorExemplo.h"
#include "DadosTest.h"

int main(int argc, char *args[])
{
	if(argc == 1){
		//system("start cmd");
		exit(0);
	}
    if(argc != 4)
    {
        printf("\nParametros invalidos\n");
        exit(1);
    }
    else
    {
		CompressorIF * compressor =  new CompressorHuffmanAntigo(args[2], args[3]);
		//DadosTest d;
		//DadosCompressorIF & dados(d);// = new DadosTest();		
		//CompressorIF * compressor =  new CompressorExemplo(*(new DadosTest()));
				
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
    }
    return EXIT_SUCCESS;
}
