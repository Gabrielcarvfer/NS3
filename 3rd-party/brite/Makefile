# Makefile for BRITE 2.0

CC = g++ -Wall
CFLAGS = -shared -Wl,-soname,libbrite.so -o libbrite.so
MODELS=./Models

brite: Brite.o  BriteNode.o Edge.o Graph.o Topology.o Util.o Parser.o \
	Parser.o Model.o RouterModel.o ASModel.o RouterWaxmanModel.o \
	RouterBarabasiAlbertModel.o ASWaxmanModel.o ASBarabasiAlbertModel.o \
	TopDownHierModel.o BottomUpHierModel.o ImportedFileModel.o
	$(CC) $(CFLAGS) Brite.o Graph.o Topology.o BriteNode.o \
		Edge.o Util.o Parser.o Model.o RouterModel.o \
		ASModel.o RouterWaxmanModel.o RouterBarabasiAlbertModel.o \
		ASWaxmanModel.o ASBarabasiAlbertModel.o \
		TopDownHierModel.o BottomUpHierModel.o ImportedFileModel.o -lm -g

Brite.o: Brite.cc Brite.h
	$(CC) -fPIC -c Brite.cc -g

BriteNode.o: BriteNode.cc BriteNode.h
	$(CC) -fPIC -c BriteNode.cc -g

Edge.o: Edge.cc Edge.h
	$(CC) -fPIC -c Edge.cc -g

Util.o: Util.cc Util.h
	$(CC) -fPIC -c Util.cc -g

Graph.o: Graph.cc Graph.h
	$(CC) -fPIC -c Graph.cc -g

Topology.o: Topology.cc Topology.h
	$(CC) -fPIC -c Topology.cc -g

Parser.o: Parser.cc Parser.h
	$(CC) -fPIC -c Parser.cc -g

Model.o: $(MODELS)/Model.cc $(MODELS)/Model.h
	$(CC) -fPIC -c $(MODELS)/Model.cc -g

RouterModel.o: \
	$(MODELS)/RouterModel.cc $(MODELS)/RouterModel.h
	$(CC) -fPIC -c $(MODELS)/RouterModel.cc -g

RouterWaxmanModel.o: \
	$(MODELS)/RouterWaxmanModel.cc $(MODELS)/RouterWaxmanModel.h 
	$(CC) -fPIC -c $(MODELS)/RouterWaxmanModel.cc -g

RouterBarabasiAlbertModel.o: \
	$(MODELS)/RouterBarabasiAlbertModel.cc $(MODELS)/RouterBarabasiAlbertModel.h
	$(CC) -fPIC -c $(MODELS)/RouterBarabasiAlbertModel.cc -g

ASModel.o: \
	$(MODELS)/ASModel.cc $(MODELS)/ASModel.h
	$(CC) -fPIC -c $(MODELS)/ASModel.cc -g

ASWaxmanModel.o: \
	$(MODELS)/ASWaxmanModel.cc $(MODELS)/ASWaxmanModel.h 
	$(CC) -fPIC -c $(MODELS)/ASWaxmanModel.cc -g

ASBarabasiAlbertModel.o: \
	$(MODELS)/ASBarabasiAlbertModel.cc $(MODELS)/ASBarabasiAlbertModel.h
	$(CC) -fPIC -c $(MODELS)/ASBarabasiAlbertModel.cc -g

TopDownHierModel.o: \
	$(MODELS)/TopDownHierModel.cc $(MODELS)/TopDownHierModel.h
	$(CC) -fPIC -c $(MODELS)/TopDownHierModel.cc  -g	

BottomUpHierModel.o: \
	$(MODELS)/BottomUpHierModel.cc $(MODELS)/BottomUpHierModel.h
	$(CC) -fPIC -c $(MODELS)/BottomUpHierModel.cc  -g	

ImportedFileModel.o: \
	$(MODELS)/ImportedFileModel.cc $(MODELS)/ImportedFileModel.h
	$(CC) -fPIC -c $(MODELS)/ImportedFileModel.cc  -g	

clean:
	rm -f *.o *~ *.so
