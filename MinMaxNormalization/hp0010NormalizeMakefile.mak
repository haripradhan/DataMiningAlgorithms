# Compiler flags...
CPP_COMPILER = g++
CPP_Flags = -Wall -c

all: hp0010Normalize

hp0010Normalize: clean main.o FileWriter.o Parser.o OutputData.o Normalization.o FileWriter.o
		$(CPP_COMPILER) main.o FileWriter.o Parser.o OutputData.o Normalization.o -o hp0010Normalize
main.o: main.cpp
		$(CPP_COMPILER) $(CPP_Flags) main.cpp

FileWriter.o: FileWriter.cpp
		$(CPP_COMPILER) $(CPP_Flags) FileWriter.cpp

Parser.o: Parser.cpp
		$(CPP_COMPILER) $(CPP_Flags) Parser.cpp

OutputData.o: OutputData.cpp
		$(CPP_COMPILER) $(CPP_Flags) OutputData.cpp

Normalization.o: Normalization.cpp
		$(CPP_COMPILER) $(CPP_Flags) Normalization.cpp
		
clean:
	rm -f *.o
