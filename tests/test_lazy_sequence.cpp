#include <gtest/gtest.h>

#include <stdexcept>

#include "Sequence.hpp"
#include "LazySequence.hpp"
#include "FibonacciGenerator.hpp"
#include "ArithmeticProgressionGenerator.hpp"
#include "FactorialGenerator.hpp"

TEST(LazySequenceTests, FiniteSequenceStoresInitialItems) {
    int items[] = {10, 20, 30};

    LazySequence<int> sequence(items, 3);

    EXPECT_FALSE(sequence.IsInfinite());
    EXPECT_EQ(sequence.GetLength(), 3u);
    EXPECT_EQ(sequence.GetMaterializedCount(), 3u);

    EXPECT_EQ(sequence.Get(0), 10);
    EXPECT_EQ(sequence.Get(1), 20);
    EXPECT_EQ(sequence.Get(2), 30);

    EXPECT_EQ(sequence.GetFirst(), 10);
    EXPECT_EQ(sequence.GetLast(), 30);
}

TEST(LazySequenceTests, FiniteSequenceThrowsOnOutOfRangeIndex) {
    int items[] = {10, 20, 30};

    LazySequence<int> sequence(items, 3);

    EXPECT_THROW(sequence.Get(3), std::out_of_range);
    EXPECT_THROW(sequence.Get(1000), std::out_of_range);
}

TEST(LazySequenceTests, FibonacciSequenceGeneratesValuesLazily) {
    int start[] = {0, 1};

    LazySequence<int> fibonacci(start, 2, new FibonacciGenerator());

    EXPECT_TRUE(fibonacci.IsInfinite());
    EXPECT_EQ(fibonacci.GetMaterializedCount(), 2u);

    EXPECT_EQ(fibonacci.Get(0), 0);
    EXPECT_EQ(fibonacci.Get(1), 1);

    EXPECT_EQ(fibonacci.GetMaterializedCount(), 2u);
    EXPECT_EQ(fibonacci.Get(2), 1);
    EXPECT_EQ(fibonacci.Get(3), 2);
    EXPECT_EQ(fibonacci.Get(4), 3);
    EXPECT_EQ(fibonacci.Get(5), 5);
    EXPECT_EQ(fibonacci.Get(10), 55);
    EXPECT_EQ(fibonacci.GetMaterializedCount(), 11u);
}

TEST(LazySequenceTests, InfiniteSequenceThrowsOnGetLengthAndGetLast) {
    int start[] = {0, 1};

    LazySequence<int> fibonacci(start, 2, new FibonacciGenerator());

    EXPECT_THROW(fibonacci.GetLast(), std::logic_error);
    EXPECT_THROW(fibonacci.GetLength(), std::logic_error);
}

TEST(LazySequenceTests, ArithmeticProgressionGeneratesCorrectValues) {
    int start[] = {3};

    LazySequence<int> progression(start, 1, new ArithmeticProgressionGenerator());

    EXPECT_TRUE(progression.IsInfinite());

    EXPECT_EQ(progression.Get(0), 3);
    EXPECT_EQ(progression.Get(1), 8);
    EXPECT_EQ(progression.Get(2), 13);
    EXPECT_EQ(progression.Get(3), 18);
    EXPECT_EQ(progression.Get(5), 28);
}

