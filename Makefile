CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SANITIZE_FLAGS = -fsanitize=address -g

SRC = src/main.cpp
APP = app

#TEST_SRC = \
	

TEST_BIN = tests_run

GTEST_FLAGS = $(shell pkg-config --cflags --libs gtest_main)

all: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP)

$(TEST_BIN): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(GTEST_FLAGS) -o $(TEST_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

asan: CXXFLAGS += $(SANITIZE_FLAGS)
asan: clean $(APP)

asan-test: CXXFLAGS += $(SANITIZE_FLAGS)
asan-test: clean $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(APP) $(TEST_BIN)

.PHONY: all test asan asan-test clean