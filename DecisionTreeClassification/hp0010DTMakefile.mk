# Compiler flags...
CPP_COMPILER = g++
CPP_Flags = -Wall -c

all: DT

DT: clean hp0010DTMain.o hp0010DTFileWriter.o hp0010DTParser.o hp0010DTOutputData.o  
		$(CPP_COMPILER) hp0010DTMain.o hp0010DTFileWriter.o hp0010DTParser.o hp0010DTOutputData.o  -o hp0010DT

hp0010DTMain.o: hp0010DTMain.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010DTMain.cpp

hp0010DTFileWriter.o: hp0010DTFileWriter.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010DTFileWriter.cpp

hp0010DTParser.o: hp0010DTParser.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010DTParser.cpp

hp0010DTOutputData.o: hp0010DTOutputData.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010DTOutputData.cpp


		
clean:
	rm -f *.o
