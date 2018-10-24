LSH_INCLUDE_DIR = ./LSH/include
LSH_OBJECT_DIR = ./LSH/object
LSH_SOURCE_DIR = ./LSH/source

CUBE_INCLUDE_DIR = ./HypercubeLSH/include
CUBE_SOURCE_DIR = ./HypercubeLSH/source
CUBE_OBJECT_DIR = ./HypercubeLSH/object

#common directories with shared code
CMN_INCLUDE_DIR = ./Shared/include
CMN_SOURCE_DIR = ./Shared/source

CC = g++
CFLAGS=-g -I$(CMN_INCLUDE_DIR)
OUT = lsh

_DEPS = Euclidean.hpp LSH.hpp ReadInput.hpp
_CMN_DEPS = CosineSimilarity.hpp ErrorCodes.hpp HashTable.hpp Metric.hpp myvector.hpp utility.hpp WriteOutput.hpp
#pattern matching from  _DEPS to include directory
LSH_DEPS = $(patsubst %,$(LSH_INCLUDE_DIR)/%,$(_DEPS))
CUBE_DEPS = $(patsubst %,$(CUBE_INCLUDE_DIR)/%,$(_DEPS))
CMN_DEPS = $(patsubst %,$(CMN_INCLUDE_DIR)/%,$(_CMN_DEPS))

_OBJ = Euclidean.o main.o LSH.o ReadInput.o
_CMN_OBJ = CosineSimilarity.o HashTable.o Metric.o myvector.o utility.o WriteOutput.o
#same pattern matching principe
LSH_OBJ = $(patsubst %,$(LSH_OBJECT_DIR)/%,$(_OBJ))
CUBE_OBJ = $(patsubst %,$(CUBE_OBJECT_DIR)/%,$(_OBJ))
CMN_OBJ = $(patsubst %,$(OBJECT_DIR)/%,$(_CMN_OBJ))

.PHONY: clean

############goals#######################

#rules for common/shared directory
$(LSH_OBJECT_DIR)/%.o: $(CMN_SOURCE_DIR)/%.cpp $(CMN_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LSH_INCLUDE_DIR)

$(CUBE_OBJECT_DIR)/%.o: $(CMN_SOURCE_DIR)/%.cpp $(CMN_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(CUBE_INCLUDE_DIR)

#rules for all non-shared
$(LSH_OBJECT_DIR)/%.o: $(LSH_SOURCE_DIR)/%.cpp $(LSH_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(LSH_INCLUDE_DIR)

$(CUBE_OBJECT_DIR)/%.o: $(CUBE_SOURCE_DIR)/%.cpp $(CUBE_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(CUBE_INCLUDE_DIR)

#default goal
$(OUT): $(LSH_OBJ) $(patsubst %,$(LSH_OBJECT_DIR)/%,$(_CMN_OBJ))
	@echo "Compiling lsh..."
	$(CC) -o $@ $^ $(CFLAGS) -I$(LSH_INCLUDE_DIR)

#cube goal
cube: $(CUBE_OBJ) $(patsubst %,$(CUBE_OBJECT_DIR)/%,$(_CMN_OBJ))
	@echo "Compiling cube..."
	$(CC) -o $@ $^ $(CFLAGS) -I$(CUBE_INCLUDE_DIR)

count:
	wc $(LSH_SOURCE_DIR)/*.cpp $(CUBE_SOURCE_DIR)/*.cpp $(LSH_INCLUDE_DIR)/*.hpp $(CUBE_INCLUDE_DIR)/*.hpp $(CMN_SOURCE_DIR)/*.cpp $(CMN_INCLUDE_DIR)/*.hpp

clean:
	rm -f $(CUBE_OBJECT_DIR)/*.o $(LSH_OBJECT_DIR)/*.o ./cube ./lsh
