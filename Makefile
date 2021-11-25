CXX = clang++

main: main.o
	$(CXX) main.o -o main

main.o: main.cpp
	$(CXX) -c main.cpp

catch.o: catch/catchmain.cpp
	$(CXX) -c catch/catchmain.cpp -o catch.o

streamer.o: streamer/streamer.cpp streamer/streamer.h
	$(CXX) -c streamer/streamer.cpp

smain.o: streamer/main.cpp streamer/streamer.h
	$(CXX) -c streamer/main.cpp -o smain.o

stest.o: streamer/tests/streamer-tests.cpp
	$(CXX) -c streamer/tests/streamer-tests.cpp -o stest.o

streamer_main: streamer.o smain.o
	$(CXX) streamer.o smain.o -o streamer_main 

streamer_test: streamer.o stest.o catch.o
	$(CXX) streamer.o stest.o catch.o -o streamer_test


CSVParser.o: CSVParser/CSVParser.cpp CSVParser/CSVParser.h
	$(CXX) -c CSVParser/CSVParser.cpp

CSVtest.o: CSVParser/tests/CSVParser-tests.cpp
	$(CXX) -c CSVParser/tests/CSVParser-tests.cpp -o CSVtest.o

CSVParser_test: streamer.o CSVtest.o CSVParser.o catch.o
	$(CXX) streamer.o CSVtest.o CSVParser.o catch.o -o CSVParser_test

graph.o: graph/graph.cpp graph/graph.h
	$(CXX) -c graph/graph.cpp

graphtest.o: graph/tests/graph-tests.cpp
	$(CXX) -c graph/tests/graph-tests.cpp -o graphtest.o

graph_test: graph.o graphtest.o catch.o streamer.o CSVParser.o
	$(CXX) graph.o graphtest.o catch.o streamer.o CSVParser.o -o graph_test


clean:
	rm main streamer_main streamer_test CSVParser_test graph_test *.o

.PHONY: clean