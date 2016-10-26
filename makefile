trader: main.o Asset.o
	g++ -g main.o Asset.o -o trader

main.o: main.cpp Asset.h
	g++ -g -c main.cpp

Asset.o: Asset.cpp Asset.h
	g++ -g -c Asset.cpp

clean:
	rm -rf *.o trader
