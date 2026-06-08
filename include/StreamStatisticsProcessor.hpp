#ifndef STREAM_STATISTICS_PROCESSOR_HPP
#define STREAM_STATISTICS_PROCESSOR_HPP

#include <cstddef>
#include "ReadOnlyStream.hpp"
#include "OnlineStatistics.hpp"

template<typename T>
class StreamStatisticsProcessor {
public:
    static void ProcessAll(ReadOnlyStream<T>& stream, OnlineStatistics<T>& statistics) {
        stream.Open();

        while (!stream.IsEndOfStream()) {
            T value = stream.Read();
            statistics.Add(value);
        }

        stream.Close();
    }

    static void ProcessFirstNElements(ReadOnlyStream<T>& stream, OnlineStatistics<T>& statistics, size_t count) {
        stream.Open();

        for (size_t i = 0; i < count; i++) {
            if (stream.IsEndOfStream())
                break;
            
            T value = stream.Read();
            statistics.Add(value);
        }

        stream.Close();
    }
};

#endif /* STREAM_STATISTICS_PROCESSOR_HPP */
