CXX = clang++

main.o: main.cpp
	$(CXX) -c main.cpp

main: main.o
	$(CXX) main.o -o main

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

clean:
	rm main streamer_main streamer_test *.o

.PHONY: clean