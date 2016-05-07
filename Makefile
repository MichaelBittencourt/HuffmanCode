SRC = $(wildcard *.cpp)
HEADER = $(wildcard *.h)
GCC = g++
FLAGS = -Wall -Werror -pedantic
OTIMIZADOR = -O0
ASSEMBLER_FLAGS = -S -fno-asynchronous-unwind-tables

saida: $(SRC) $(HEADER) 
	$(GCC) $(FLAGS) $(OTIMIZADOR) -c $(SRC)
	$(GCC) $(FLAGS) $(OTIMIZADOR) *.o -o saida

_PHONE: assembly

assembly:
	$(GCC) $(FLAGS) $(OTIMIZADOR) $(ASSEMBLER_FLAGS) $(SRC) 

_PHONE: clean

clean:
	rm *.o *.s saida
