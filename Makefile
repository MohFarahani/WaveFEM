# Configuration of the executable
TARGET = waveguide

INSTALL_PATH = $(PWD)

# Compiler configuration
CXX      = g++
CXXFLAGS = -Wall -ansi -pedantic
COMP = -c 
INC = 
INC_LIB = 
 
OBJ = main.o \
      Vertex.o\
      Triangle.o \
      Triangulation.o \
      Global.o \
      FEM.o \


default: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(INC) $(INC_LIB)

clean:
	@$(RM) waveguide *.o *.txt

