.PHONY: all, clean

CC = gcc
CCFLAGS = -Wall -Wextra -Wvla -Werror -g -lm -std=c99

TARGET_HASH = libhashmap.a
TARGET_TEST = libhashmap_tests.a

TARGETS = $(TARGET_HASH) $(TARGET_TEST)

VECTOR_SRC = vector.c vector.h
HASH_SRC = hashmap.c hashmap.h pair.c pair.h $(VECTOR_SRC)
TEST_SRC = test_suite.c test_suite.h test_pairs.h hash_funcs.h $(HASH_SRC) $(VECTOR_SRC)

LIB_HASH_SRC = $(HASH_SRC) $(VECTOR_SRC)
LIB_HASH_OBJ = hashmap.o vector.o

LIB_TEST_SRC = test_suite.c test_suite.h test_pairs.h hash_funcs.h $(LIB_HASH_SRC)
LIB_TEST_OBJ = test_suite.o

OBJECTS = $(LIB_TEST_OBJ) $(LIB_HASH_OBJ)

all: $(TARGETS)

clean:
	$(RM) $(TARGETS) $(OBJECTS)

$(TARGET_HASH) : $(LIB_HASH_OBJ)
	ar rcs $(TARGET_HASH) $(LIB_HASH_OBJ)

$(TARGET_TEST) : $(LIB_TEST_OBJ)
	ar rcs $(TARGET_TEST) $(LIB_TEST_OBJ)

test_suite.o : $(TEST_SRC)
	$(CC) $(CCFLAGS) -c $<

hashmap.o : $(HASH_SRC)
	$(CC) $(CCFLAGS) -c $<

vector.o : $(VECTOR_SRC)
	$(CC) $(CCFLAGS) -c $<