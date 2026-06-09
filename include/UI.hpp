#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>

#include "MutableArraySequence.hpp"
#include "LazySequence.hpp"
#include "FibonacciGenerator.hpp"
#include "ArithmeticProgressionGenerator.hpp"
#include "FactorialGenerator.hpp"
#include "SequenceReadOnlyStream.hpp"
#include "LazySequenceReadOnlyStream.hpp"
#include "OnlineStatistics.hpp"
#include "StreamStatisticsProcessor.hpp"

bool ReadSizeT(const char* message, size_t& value) {
    long long temp = 0;

    std::cout << message;
    std::cin >> temp;

    if (!std::cin || temp < 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка ввода. Нужно ввести неотрицательное целое число\n";
        return false;
    }

    value = static_cast<size_t>(temp);
    return true;
}

bool ReadInt(const char* message, int& value) {
    std::cout << message;
    std::cin >> value;

    if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Ошибка ввода. Нужно ввести целое число\n";
        return false;
    }

    return true;
}

template<typename T>
void PrintStatistics(const OnlineStatistics<T>& statistics) {
    if (statistics.IsEmpty()) {
        std::cout << "Статистика пуста\n";
        return;
    }

    std::cout << "Количество элементов: " << statistics.GetCount() << std::endl;
    std::cout << "Минимум: " << statistics.GetMin() << std::endl;
    std::cout << "Максимум: " << statistics.GetMax() << std::endl;
    std::cout << "Сумма: " << statistics.GetSum() << std::endl;
    std::cout << "Среднее: " << statistics.GetMean() << std::endl;
}

template<typename T>
void PrintFirstN(const Sequence<T>& sequence, size_t count, bool is_infinite) {
    if (!is_infinite) {
        size_t length = sequence.GetLength();

        if (count > length) {
            std::cout << "Запрошено больше элементов, чем есть в последовательности\n";
            std::cout << "Будут показаны все доступные элементы\n";
            count = length;
        }
    }

    std::cout << "\nПервые " << count << " элементов:\n";

    for (size_t i = 0; i < count; ++i) {
        std::cout << "[" << i << "] = " << sequence.Get(i) << std::endl;
    }
}

template<typename T>
void PrintWindow(const Sequence<T>& sequence, size_t current_position, size_t radius, bool is_infinite) {
    std::cout << "\nОкно последовательности вокруг позиции " << current_position - 1 << ":\n";

    if (!is_infinite && sequenceGetLength() == 0) {
        std::cout << "Последовательность пуста\n";
        return;
    }

    size_t start = 0;

    if (current_position > radius) {
        start = current_position - radius;
    }

    size_t end = current_position + radius;

    if (!is_infinite) {
        size_t length = sequence.GetLength();

        if (start >= length) {
            start = length - 1;
        }

        if (end >= length) {
            end = length - 1;
        }
    }

    for (size_t i = start; i <= end; ++i) {
        std::cout << "[" << i << "] = " << sequence.Get(i);

        if (i == current_position) {
            std::cout << "   <- следующий Read()";
        }

        std::cout << std::endl;
    }

    if (!is_infinite && current_position >= sequence.GetLength()) {
        std::cout << "Текущая позиция находится в конце потока\n";
    }
}

template<typename T>
void PrintLazyState(const char* name, const LazySequence<T>& sequence, const LazySequenceReadOnlyStream<T>& stream) {
    std::cout << "\n---------- Состояние ----------\n";
    std::cout << "Последовательность: " << name << std::endl;
    std::cout << "Тип: LazySequence\n";
    std::cout << "Режим: ";
    std::cout << (sequence.IsInfinite() ? "бесконечная" : "конечная") << std::endl;
    std::cout << "Позиция stream: " << stream.GetPosition() << std::endl;
    std::cout << "Материализовано элементов: " << sequence.GetMaterializedCount() << std::endl;
}

template<typename T>
void RunLazyExplorer(const char* name, LazySequence<T>& sequence) {
    LazySequenceReadOnlyStream<T> stream(&sequence);
    stream.Open();

    bool running = true;

    while (running) {
        PrintLazyState(name, sequence, stream);
        PrintWindow(sequence, stream.GetPosition(), 3, sequence.IsInfinite());

        std::cout << "\nДействия:\n";
        std::cout << "1) Read next — прочитать следующий элемент потока\n";
        std::cout << "2) Seek(index) — перейти к позиции\n";
        std::cout << "3) Get(index) — получить элемент LazySequence по индексу\n";
        std::cout << "4) Показать первые N элементов\n";
        std::cout << "5) Посчитать статистику первых N элементов\n";
        std::cout << "6) Показать окно вокруг текущей позиции\n";
        std::cout << "0) Назад\n";
        std::cout << "Выберите пункт: ";

        int command = -1;
        std::cin >> command;

        try {
            switch (command) {
                case 1: {
                    T value = stream.Read();
                    std::cout << "Read() вернул: " << value << std::endl;
                    break;
                }

                case 2: {
                    size_t index = 0;

                    if (!ReadSizeT("Введите индекс: ", index)) {
                        break;
                    }

                    stream.Seek(index);
                    std::cout << "Позиция потока изменена на " << index << std::endl;
                    break;
                }

                case 3: {
                    size_t index = 0;

                    if (!ReadSizeT("Введите индекс: ", index)) {
                        break;
                    }

                    std::cout << "sequence.Get(" << index << ") = " << sequence.Get(index) << std::endl;

                    std::cout << "Материализовано элементов: " << sequence.GetMaterializedCount() << std::endl;
                    break;
                }

                case 4: {
                    size_t count = 0;

                    if (!ReadSizeT("Сколько элементов показать: ", count)) {
                        break;
                    }

                    PrintFirstN(sequence, count, sequence.IsInfinite());

                    std::cout << "Материализовано элементов: " << sequence.GetMaterializedCount() << std::endl;
                    break;
                }

                case 5: {
                    size_t count = 0;

                    if (!ReadSizeT("Сколько первых элементов обработать: ", count)) {
                        break;
                    }

                    LazySequenceReadOnlyStream<T> statistics_stream(&sequence);
                    OnlineStatistics<T> statistics;

                    StreamStatisticsProcessor<T>::ProcessFirstNElements(statistics_stream, statistics, count);

                    std::cout << "\nСтатистика первых " << count << " элементов:\n";
                    PrintStatistics(statistics);

                    std::cout << "Материализовано элементов: " << sequence.GetMaterializedCount() << std::endl;
                    break;
                }

                case 6: {
                    size_t radius = 0;

                    if (!ReadSizeT("Введите радиус окна: ", radius)) {
                        break;
                    }

                    PrintWindow(sequence, stream.GetPosition(), radius, sequence.IsInfinite());
                    break;
                }

                case 0:
                    running = false;
                    break;

                default:
                    std::cout << "Неизвестная команда\n";
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Ошибка: " << error.what() << std::endl;
        }
    }

    stream.Close();
}

void RunFiniteSequenceExplorer() {
    std::cout << "\n---------- Конечная Sequence ----------\n";

    size_t count = 0;

    if (!ReadSizeT("Введите количество элементов: ", count)) {
        return;
    }

    if (count == 0) {
        std::cout << "Пустую последовательность сейчас не создаём\n";
        return;
    }

    int* items = new int[count];

    try {
        for (size_t i = 0; i < count; ++i) {
            std::cout << "items[" << i << "] = ";
            std::cin >> items[i];

            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                delete[] items;
                std::cout << "Ошибка ввода элемента\n";
                return;
            }
        }

        MutableArraySequence<int> sequence(items, static_cast<int>(count));
        delete[] items;
        items = nullptr;

        SequenceReadOnlyStream<int> stream(&sequence);
        stream.Open();

        bool running = true;

        while (running) {
            std::cout << "\n---------- Состояние ----------\n";
            std::cout << "Последовательность: ручная конечная Sequence\n";
            std::cout << "Тип: MutableArraySequence + SequenceReadOnlyStream\n";
            std::cout << "Длина: " << sequence.GetLength() << std::endl;
            std::cout << "Позиция stream: " << stream.GetPosition() << std::endl;

            PrintWindow(sequence, stream.GetPosition(), 5, false);

            std::cout << "\nДействия:\n";
            std::cout << "1) Read next — прочитать следующий элемент потока\n";
            std::cout << "2) Seek(index) — перейти к позиции\n";
            std::cout << "3) Get(index) — получить элемент Sequence по индексу\n";
            std::cout << "4) Показать первые N элементов\n";
            std::cout << "5) Посчитать статистику всей последовательности\n";
            std::cout << "6) Показать окно вокруг текущей позиции\n";
            std::cout << "0) Назад\n";
            std::cout << "Выберите пункт: ";

            int command = -1;
            std::cin >> command;

            try {
                switch (command) {
                    case 1: {
                        int value = stream.Read();
                        std::cout << "Read() вернул: " << value << std::endl;
                        break;
                    }

                    case 2: {
                        size_t index = 0;

                        if (!ReadSizeT("Введите индекс: ", index)) {
                            break;
                        }

                        stream.Seek(index);
                        std::cout << "Позиция потока изменена на " << index << std::endl;
                        break;
                    }

                    case 3: {
                        size_t index = 0;

                        if (!ReadSizeT("Введите индекс: ", index)) {
                            break;
                        }

                        std::cout << "sequence.Get(" << index << ") = " << sequence.Get(index) << std::endl;
                        break;
                    }

                    case 4: {
                        size_t n = 0;

                        if (!ReadSizeT("Сколько элементов показать: ", n)) {
                            break;
                        }

                        PrintFirstN(sequence, n, false);
                        break;
                    }

                    case 5: {
                        SequenceReadOnlyStream<int> statistics_stream(&sequence);
                        OnlineStatistics<int> statistics;

                        StreamStatisticsProcessor<int>::ProcessAll(
                            statistics_stream,
                            statistics
                        );

                        std::cout << "\nСтатистика всей последовательности:\n";
                        PrintStatistics(statistics);
                        break;
                    }

                    case 6: {
                        size_t radius = 0;

                        if (!ReadSizeT("Введите радиус окна: ", radius)) {
                            break;
                        }

                        PrintWindow(sequence, stream.GetPosition(), radius, false);
                        break;
                    }

                    case 0:
                        running = false;
                        break;

                    default:
                        std::cout << "Неизвестная команда\n";
                        break;
                }
            } catch (const std::exception& error) {
                std::cout << "Ошибка: " << error.what() << std::endl;
            }
        }

        stream.Close();
    } catch (...) {
        delete[] items;
        throw;
    }
}

void RunFibonacciExplorer() {
    int start[] = {0, 1};
    LazySequence<int> fibonacci(start, 2, new FibonacciGenerator());

    RunLazyExplorer("Fibonacci", fibonacci);
}

void RunArithmeticProgressionExplorer() {
    std::cout << "\n---------- Арифметическая прогрессия ----------\n";

    int first = 0;
    int step = 0;

    if (!ReadInt("Введите первый элемент: ", first)) {
        return;
    }

    if (!ReadInt("Введите шаг прогрессии: ", step)) {
        return;
    }

    int start[] = {first};
    LazySequence<int> progression(start, 1, new ArithmeticProgressionGenerator(step));

    RunLazyExplorer("Arithmetic progression", progression);
}

void RunFactorialExplorer() {
    std::cout << "\n---------- Факториалы ----------\n";
    std::cout << "Внимание: unsigned long long переполняется после 20!\n";

    unsigned long long start[] = {1};
    LazySequence<unsigned long long> factorials(start, 1, new FactorialGenerator());

    RunLazyExplorer("Factorials", factorials);
}

void PrintMainMenu() {
    std::cout << "\n--------------------\n";
    std::cout << "LazySequence и ReadOnlyStream\n";
    std::cout << "-------------------------------------\n";
    std::cout << "1) Создать конечную Sequence вручную\n";
    std::cout << "2) Открыть бесконечную Fibonacci LazySequence\n";
    std::cout << "3) Открыть бесконечную арифметическую прогрессию\n";
    std::cout << "4) Открыть бесконечную последовательность факториалов\n";
    std::cout << "0) Выход\n";
    std::cout << "Выберите пункт: ";
}

void StartUI() {
    bool running = true;

    while (running) {
        PrintMainMenu();

        int command;
        std::cin >> command;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Ошибка ввода команды\n";
            continue;
        }

        try {
            switch (command) {
                case 1:
                    RunFiniteSequenceExplorer();
                    break;

                case 2:
                    RunFibonacciExplorer();
                    break;

                case 3:
                    RunArithmeticProgressionExplorer();
                    break;

                case 4:
                    RunFactorialExplorer();
                    break;

                case 0:
                    running = false;
                    std::cout << "Выход из программы\n";
                    break;

                default:
                    std::cout << "Неизвестная команда\n";
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Ошибка: " << error.what() << std::endl;
        }
    }
}

#endif /* UI_HPP */