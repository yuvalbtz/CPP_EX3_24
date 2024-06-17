CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Define targets
TEST_TARGET = test
DEMO_TARGET = demo

# Source files
SOURCES = monopoly_card.cpp road_building_card.cpp \
          year_of_plenty_card.cpp board.cpp catan.cpp \
          city.cpp knight_card.cpp player.cpp \
          road.cpp settlement.cpp tile.cpp \

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Test and demo source files
TEST_SOURCES = test_player.cpp
DEMO_SOURCES = Demo.cpp

# Test and demo object files
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)

# Default target
all: $(DEMO_TARGET)

# Rule for test target
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(OBJECTS) $(TEST_OBJECTS)

# Rule for demo target
$(DEMO_TARGET): $(OBJECTS) $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET) $(OBJECTS) $(DEMO_OBJECTS)

# Generic rule for compiling .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TEST_TARGET) $(DEMO_TARGET) $(OBJECTS) $(TEST_OBJECTS) $(DEMO_OBJECTS)