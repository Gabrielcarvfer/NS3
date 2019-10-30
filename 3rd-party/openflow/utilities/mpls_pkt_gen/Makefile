all: pkt_gen

pkt_gen: csum.o mpls_pkt_gen.o 
	g++ -g csum.o mpls_pkt_gen.o -o pkt_gen

csum.o: csum.c
	gcc -g -c csum.c

mpls_pkt_get.o: mpls_pkt_gen.c
	gcc -g -c mpls_pkt_gen.c

clean:
	rm -rf *.o pkt_gen
