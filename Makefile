CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =
TEST_TARGET = test_catan
TEST_SRC = test_player.cpp player.cpp board.cpp
OBJS = catan.o player.o board.o Demo.o

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o catan $(OBJS) $(LDFLAGS)

Demo.o: Demo.cpp catan.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

catan.o: catan.cpp catan.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c catan.cpp

test:$(TEST_TARGET)

$(TEST_TARGET):$(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(LDFLAGS)

player.o: player.cpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp

clean:
	rm -f *.o catan $(TEST_TARGET)
