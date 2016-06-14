SRC = $(wildcard *.cpp)
HEADER = $(wildcard *.h)
GCC = g++
FLAGS = -std=c++11 -Wall -Werror -pedantic
OTIMIZADOR = -O0
ASSEMBLER_FLAGS = -S -fno-asynchronous-unwind-tables

main: $(SRC) $(HEADER) 
	$(GCC) $(FLAGS) $(OTIMIZADOR) -c $(SRC)
	$(GCC) $(FLAGS) $(OTIMIZADOR) *.o -o main.out

debug: $(SRC) $(HEADER) 
	$(GCC) -g3 $(FLAGS) $(OTIMIZADOR) -c $(SRC)
	$(GCC) -g3 $(FLAGS) $(OTIMIZADOR) *.o -o main.out

_PHONE: assembly

assembly:
	$(GCC) $(FLAGS) $(OTIMIZADOR) $(ASSEMBLER_FLAGS) $(SRC) 

_PHONE: clean

clean:
	rm *.o *.s main.out
