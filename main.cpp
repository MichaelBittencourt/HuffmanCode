#include<stdio.h>
#include<stdlib.h>
#include "CompressorIF.h"
#include "CompressorHuffmanAntigo.h"

int main(int argc, char *args[])
{
	if(argc == 1){
		system("start cmd");
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
//		CompressorHuffmanAntigo * compressor = new CompressorHuffmanAntigo(args[2], args[3]);
				
        if(strcmp(args[1], "-c")==0)
        {
			compressor->compress();//				CompressFile(args[2], args[3]);//comprimir arquivo
        }
        else
        {
            if(strcmp(args[1], "-x")==0)
            {
                 compressor->descompress(); //DescompressFile(args[3],args[2]);//descomprimir arquivo
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
