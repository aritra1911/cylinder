CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
LIBS =
SRC = main.cpp schema.cpp sqlparser.cpp field_type.cpp
OBJ = main.o schema.o sqlparser.o field_type.o

.PHONY: clean

cylinder: $(OBJ)
	$(CXX) $(LIBS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) -c -o $@ $<

clean:
	$(RM) $(OBJ) cylinder
