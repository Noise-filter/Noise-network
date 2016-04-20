CPP_FILES := $(wildcard src/Ä.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

test: $(OBJ_FILES)
	ar rcs $@ $^