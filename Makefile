CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

APP = app
TEST_BIN = tests_run

SRC = src/main.cpp
TEST_SRC = tests/main_tests.cpp \
           tests/test_generators.cpp \
           tests/test_lazy_sequence.cpp \
           tests/test_streams.cpp \
           tests/test_statistics.cpp

GTEST_FLAGS = -lgtest -pthread

all: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP)

$(TEST_BIN): $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -o $(TEST_BIN) $(GTEST_FLAGS)

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(APP) $(TEST_BIN)

.PHONY: all test clean