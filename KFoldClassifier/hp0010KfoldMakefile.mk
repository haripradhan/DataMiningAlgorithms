# Compiler flags...
CPP_COMPILER = g++
CPP_Flags = -Wall -c

all: Kfold

Kfold: clean hp0010KfoldMain.o hp0010KfoldFileWriter.o hp0010KfoldParser.o hp0010KfoldOutputData.o  hp0010KfoldClassifier.o
		$(CPP_COMPILER) hp0010KfoldMain.o hp0010KfoldFileWriter.o hp0010KfoldParser.o hp0010KfoldOutputData.o hp0010KfoldClassifier.o -o hp0010KFold

hp0010KfoldMain.o: hp0010KfoldMain.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010KfoldMain.cpp

hp0010KfoldFileWriter.o: hp0010KfoldFileWriter.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010KfoldFileWriter.cpp

hp0010KfoldParser.o: hp0010KfoldParser.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010KfoldParser.cpp

hp0010KfoldOutputData.o: hp0010KfoldOutputData.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010KfoldOutputData.cpp

hp0010KfoldClassifier.o: hp0010KfoldClassifier.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010KfoldClassifier.cpp

		
clean:
	rm -f *.o
