#include <iostream>

#include "LazySequence.hpp"
#include "FibonacciGenerator.hpp"
#include "ArithmeticProgressionGenerator.hpp"
#include "FactorialGenerator.hpp"

#include "LazySequenceReadOnlyStream.hpp"
#include "SequenceReadOnlyStream.hpp"
#include "StreamStatisticsProcessor.hpp"

int main() {
    int items[] = {1, 3, 5, 1, 5, 0, 235, 234, 1};
    MutableArraySequence<int> sequence(items, 9);
    
    SequenceReadOnlyStream<int> stream(&sequence);

    OnlineStatistics<int> statistics;

    StreamStatisticsProcessor<int>::ProcessAll(stream, statistics);

    std::cout << "Count = " << statistics.GetCount() << std::endl;
    std::cout << "Maximum = " << statistics.GetMax() << std::endl;
    std::cout << "Minimum = " << statistics.GetMin() << std::endl;
    std::cout << "Mean = " << statistics.GetMean() << std::endl;
    std::cout << "Sum = " << statistics.GetSum() << std::endl;

    


    return 0;
}











/*int fib_start[] = {0, 1};

    LazySequence<int> fib(fib_start, 2, new FibonacciGenerator());

    std::cout << "Fibonacci:\n";
    std::cout << "fib[0] = " << fib.Get(0) << std::endl;
    std::cout << "fib[1] = " << fib.Get(1) << std::endl;
    std::cout << "fib[2] = " << fib.Get(2) << std::endl;
    std::cout << "fib[10] = " << fib.Get(10) << std::endl;
    std::cout << "Materialized: " << fib.GetMaterializedCount() << std::endl;

    int arith_start[] = {0};
    int step = 5;

    LazySequence<int> arith(arith_start, 1, new ArithmeticProgressionGenerator(step));

    std::cout << "\nArithmetic progression:\n";
    std::cout << "a[0] = " << arith.Get(0) << std::endl;
    std::cout << "a[1] = " << arith.Get(1) << std::endl;
    std::cout << "a[2] = " << arith.Get(2) << std::endl;
    std::cout << "a[3] = " << arith.Get(3) << std::endl;
    std::cout << "a[100] = " << arith.Get(100) << std::endl;
    std::cout << "Materialized: " << arith.GetMaterializedCount() << std::endl;

    unsigned long long fact_start[] = {1};

    LazySequence<unsigned long long> fact(fact_start, 1, new FactorialGenerator());

    std::cout << "\nFactorials:\n";
    std::cout << "fact[0] = " << fact.Get(0) << std::endl;
    std::cout << "fact[1] = " << fact.Get(1) << std::endl;
    std::cout << "fact[2] = " << fact.Get(2) << std::endl;
    std::cout << "fact[3] = " << fact.Get(3) << std::endl;
    std::cout << "fact[10] = " << fact.Get(10) << std::endl;
    std::cout << "Materialized: " << fact.GetMaterializedCount() << std::endl;*/



/*
int items[] = {10, 20, 30};
    MutableArraySequence<int> seq(items, 3);

    SequenceReadOnlyStream<int> seq_stream(&seq);

    seq_stream.Open();

    std::cout << "Sequence stream: \n";
    while (!seq_stream.IsEndOfStream()) {
        std::cout << seq_stream.Read() << ' ';
    }

    std::cout << "\nPosition: " << seq_stream.GetPosition() << std::endl;

    seq_stream.Seek(1);
    std::cout << "after seek = " << seq_stream.Read();

    seq_stream.Close();

    std::cout << "\n------------------------------------------------------------------------------------\n";

    int items2[] = {0, 1};
    LazySequence<int> lazy_seq(items2, 2, new FibonacciGenerator());

    LazySequenceReadOnlyStream<int> lazy_stream(&lazy_seq);

    lazy_stream.Open();

    std::cout << "\nLazy stream: \n";

    for (int i = 0; i < 10; i++) {
        std::cout << lazy_stream.Read() << ' '; 
    }

    std::cout << "\nPosition: " << lazy_stream.GetPosition() << std::endl;
    lazy_stream.Seek(15);
    std::cout << "after seek = " << lazy_stream.Read() << std::endl;


*/