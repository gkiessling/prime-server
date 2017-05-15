HEADERS = src/$(wildcard *.h) thirdparty/$(wildcard *.h*) thirdparty/rapidjson/$(wildcard *.h)
INCLUDE = -Isrc -Ithirdparty -Ithirdparty/rapidjson
CPP = g++
#CFLAGS = -std=c++11 -O0 -g3 -Wall
CFLAGS = -std=c++11 -O2 -Wall

.PHONY: default all clean test

default: prime-client prime-server
all: default

prime-client: src/PrimeClient.o src/prime-client.o
	$(CPP) $(CFLAGS) -o prime-client src/PrimeClient.o src/prime-client.o

prime-server: CFLAGS += -DINFINT_USE_EXCEPTIONS	
prime-server: src/PrimeServer.o src/prime-server.o src/PrimeValidator.o src/PrimeClient.o
	$(CPP) $(CFLAGS) -o prime-server src/PrimeServer.o src/prime-server.o src/PrimeValidator.o src/PrimeClient.o
	
test: test/tests-main
	test/tests-main

test/tests-main: CFLAGS += -DINFINT_USE_EXCEPTIONS
test/tests-main: test/tests-main.o test/PrimeValidatorTests.o src/PrimeValidator.o
	$(CPP) $(CFLAGS) -o test/tests-main test/tests-main.o test/PrimeValidatorTests.o src/PrimeValidator.o
	
src/%.o: src/%.cpp $(HEADERS)
	$(CPP) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
test/%.o: test/%.cpp $(HEADERS)
	$(CPP) $(CFLAGS) $(INCLUDE) -c $< -o $@
	
clean:
	rm -rf src/*.o test/*.o
	rm -rf prime-client prime-server test/tests-main
