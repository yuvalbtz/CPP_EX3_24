CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =
TEST_TARGET = test_catan
TEST_SRC = test_player.cpp player.cpp board.cpp development_card.cpp
OBJS = catan.o player.o board.o development_card.o Demo.o

catan: $(OBJS)
	$(CXX) $(CXXFLAGS) -o catan $(OBJS) $(LDFLAGS)

Demo.o: Demo.cpp catan.hpp player.hpp board.hpp development_card.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp

catan.o: catan.cpp catan.hpp player.hpp board.hpp development_card.hpp
	$(CXX) $(CXXFLAGS) -c catan.cpp

test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(LDFLAGS)

player.o: player.cpp player.hpp board.hpp development_card.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp

development_card.o: development_card.cpp development_card.hpp
	$(CXX) $(CXXFLAGS) -c development_card.cpp

clean:
	rm -f *.o catan $(TEST_TARGET)
