INCLUDE_DIR = ./include
SOURCE_DIR = ./source
OBJECT_DIR = ./object

CC = g++
CFLAGS=-g -I$(INCLUDE_DIR)
OUT = cube

_DEPS = CosineSimilarity.hpp ErrorCodes.hpp Euclidean.hpp HashTable.hpp Metric.hpp myvector.hpp LSH.hpp ReadInput.hpp utility.hpp WriteOutput.hpp
#pattern matching from  _DEPS to include directory
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ = CosineSimilarity.o Euclidean.o HashTable.o main.o Metric.o myvector.o LSH.o ReadInput.o utility.o WriteOutput.o
#same pattern matching principe
OBJ = $(patsubst %,$(OBJECT_DIR)/%,$(_OBJ))

.PHONY: clean

############goals#######################

#general rule for all object files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#default goal
$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

count:
	wc $(SOURCE_DIR)/*.cpp $(DEPS)

clean:
	rm -f $(OBJECT_DIR)/*.o ./cube
