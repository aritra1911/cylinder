CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBS =
SRC = main.cpp schema.cpp sqlparser.cpp
OBJ = main.o schema.o sqlparser.o

.PHONY: clean

cylinder: $(OBJ)
	$(CXX) $(LIBS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c -o $@ $<

clean:
	$(RM) $(OBJ) cylinder
