CPP=g++

OBJECTS=libs/basic.o libs/bitrankw32int.o libs/kTree.o libs/Count.o\
		libs/knnpq.o libs/knnir.o

BINS=getKNNPQ getKNNIR generateKtFromPointList getTimeKNNIR getTimeKNNPQ
		
CPPFLAGS=-std=c++11 -O3 -DNDEBUG
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: clean bin

bin: $(OBJECTS) $(BINS)

getKNNPQ:
	g++ $(CPPFLAGS) -o $(DEST)/getKNNPQ getKNNPQ.cpp $(OBJECTS) -lm

getKNNIR:
	g++ $(CPPFLAGS) -o $(DEST)/getKNNIR getKNNIR.cpp $(OBJECTS) -lm

generateKtFromPointList:
	g++ $(CPPFLAGS) -o $(DEST)/generateKtFromPointList generateKtFromPointList.cpp $(OBJECTS) -lm

getTimeKNNIR:
	g++ $(CPPFLAGS) -o $(DEST)/getTimeKNNIR getTimeKNNIR.cpp $(OBJECTS) -lm

getTimeKNNPQ:
	g++ $(CPPFLAGS) -o $(DEST)/getTimeKNNPQ getTimeKNNPQ.cpp $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)

