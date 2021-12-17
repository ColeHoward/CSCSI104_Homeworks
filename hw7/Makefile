CXX = g++
CXXFLAGS = -g -Wall -std=c++11

all: avlbst.o floorplan.o bst.o

bst: bst.cpp bst.h
	$(CXX) $(CXXFLAGS) bst.cpp -o bst
	
floorplan: floorplan.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) floorplan.cpp -o floorplan

avlbst: avlbst.cpp  avlbst
	$(CXX) $(CXXFLAGS) avlbst.cpp -o avlbst

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)