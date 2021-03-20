CXXFLAGS = -Wall -Wextra -pedantic -std=c++11
LIBS =
SRC = main.cpp schema.cpp sqlparser.cpp
OBJ = main.o schema.o sqlparser.o

cylinder: $(OBJ)
	$(CXX) $(LIBS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	$(RM) $(OBJ) cylinder
