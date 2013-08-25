# Compiler flags...
CPP_COMPILER = g++
CPP_Flags = -Wall -c

all: ClusterKMedoids

ClusterKMedoids: clean hp0010ClusterMain.o hp0010ClusterFileWriter.o hp0010ClusterParser.o hp0010ClusterOutputData.o hp0010ClusterNormalization.o hp0010ClusterKMedoid.o
		$(CPP_COMPILER) hp0010ClusterMain.o hp0010ClusterFileWriter.o hp0010ClusterParser.o hp0010ClusterOutputData.o hp0010ClusterNormalization.o hp0010ClusterKMedoid.o -o hp0010ClusterKMedoids

hp0010ClusterMain.o: hp0010ClusterMain.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterMain.cpp

hp0010ClusterFileWriter.o: hp0010ClusterFileWriter.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterFileWriter.cpp

hp0010ClusterParser.o: hp0010ClusterParser.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterParser.cpp

hp0010ClusterOutputData.o: hp0010ClusterOutputData.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterOutputData.cpp

hp0010ClusterNormalization.o: hp0010ClusterNormalization.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterNormalization.cpp

hp0010ClusterKMedoid.o: hp0010ClusterKMedoid.cpp
		$(CPP_COMPILER) $(CPP_Flags) hp0010ClusterKMedoid.cpp
		
clean:
	rm -f *.o
