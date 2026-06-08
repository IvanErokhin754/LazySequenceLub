#ifndef READ_ONLY_STREAM_HPP
#define READ_ONLY_STREAM_HPP

#include <cstddef>

template<typename T>
class ReadOnlyStream {
public:
    virtual bool IsEndOfStream() const = 0;
    virtual T Read() = 0;
    virtual size_t GetPosition() const = 0;
    virtual bool IsCanSeek() const = 0;
    virtual size_t Seek(size_t index) = 0;
    virtual bool IsCanGoBack() const = 0;
    virtual void Open() = 0;
    virtual void Close() = 0;

    virtual ~ReadOnlyStream() = default;
};

#endif /* READ_ONLY_STREAM_HPP */
