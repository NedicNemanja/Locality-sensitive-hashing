INCLUDE_DIR = ./include
SOURCE_DIR = ./source
OBJECT_DIR = ./object

CC = g++
CFLAGS=-g -I$(INCLUDE_DIR)
OUT = lhs

_DEPS =  Bucket.hpp ErrorCodes.hpp Euclidean.hpp HashTable.hpp Metric.hpp myvector.hpp ReadInput.hpp utility.hpp
#pattern matching from  _DEPS to include directory
DEPS = $(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ = Bucket.o Euclidean.o HashTable.o main.o Metric.o myvector.o ReadInput.o utility.o
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
	rm -f $(OBJECT_DIR)/*.o ./lhs
