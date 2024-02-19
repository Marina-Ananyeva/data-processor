#include "processor.h"

#include <algorithm>
#include <execution>
#include <limits>
#include <string>

DataProcessor::DataProcessor(OperationType type, const Data &operands) :
    m_type(type),
    m_operation(std::move(OperationsFactory().createOperation(type, operands)))
{
}

// последовательная обработка
Data DataProcessor::process(const std::vector<Data> &data) const
{
    if(data.empty())
        return Data{};

    size_t n = data.front().size();
    Data result(n);
    for (size_t i = 0; i < n; ++i) {
        result[i] = m_operation->processOperation(data.front()[i]);
    }

    return std::move(result);
}

// параллельная обработка
Data DataProcessor::processPar(const std::vector<Data> &data) const
{
    if(data.empty())
        return Data{};

    Data result(data.front().size());
    std::transform(std::execution::par, data.front().begin(), data.front().end(), result.begin()
                , [&result, this](const auto element) {
                        return m_operation->processOperation(element);
                    });

    return std::move(result);
}

OperationType DataProcessor::getType() const
{
    return m_type;
}


MultiplyByProcessor::MultiplyByProcessor(OperationType type, const Data &operands) :
    DataProcessor(type, operands) 
{
}


LogarithmBaseProcessor::LogarithmBaseProcessor(OperationType type, const Data &operands) :
    DataProcessor(type, operands) 
{
}


PowerProcessor::PowerProcessor(OperationType type, const Data &operands) :
    DataProcessor(type, operands) 
{
}


AverageLastProcessor::AverageLastProcessor(OperationType type, const Data &operands) :
    DataProcessor(type, operands) 
{
}

// последовательная обработка
Data AverageLastProcessor::process(const std::vector<Data> &data) const 
{
    Data result;
    int dataSize = static_cast<int>(data.size());
    int averageSize = std::min(dataSize, AVERAGE_COUNT);
    if (averageSize != 0) {
        int countOfElements = data.front().size();
        result.resize(countOfElements);
        for (int i = 0; i < countOfElements; ++i) {
            long double sum = 0.0;
            for (const auto &elements : data) {
                if (elements[i]->getType() == ElementType::INT ||
                    elements[i]->getType() == ElementType::FLOAT ||
                    elements[i]->getType() == ElementType::DOUBLE ||
                    elements[i]->getType() == ElementType::LONG_DOUBLE) {
                        sum += elements[i]->getValue();
                    } else {
                        throw CalculationError("Not for summation data type");
                    }
            }

            if (sum > std::numeric_limits<long double>::max())
                throw CalculationError("Overflow detected in calculation");

            long double value = sum / averageSize;
            auto element = ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE
                                                                            , value);
            result[i] = std::move(element);
        }
    } else {
        throw CalculationError("There are no previous calculations");
    }
    return std::move(result);
}

// параллельная обработка
Data AverageLastProcessor::processPar(const std::vector<Data> &data) const 
{
    Data result;
    int dataSize = static_cast<int>(data.size());
    int averageSize = std::min(dataSize, AVERAGE_COUNT);
    if (averageSize != 0) {
        int countOfElements = data.front().size();
        result.resize(countOfElements);
        for (int i = 0; i < countOfElements; ++i) {
            long double sum = 0.0;
            std::for_each(std::execution::par, data.begin(), data.end(), [&i, &sum](const Data &elements) {
                if (elements[i]->getType() == ElementType::INT ||
                    elements[i]->getType() == ElementType::FLOAT ||
                    elements[i]->getType() == ElementType::DOUBLE ||
                    elements[i]->getType() == ElementType::LONG_DOUBLE) {
                        sum += elements[i]->getValue();
                    } else {
                        throw CalculationError("Not for summation data type");
                    }
            });

            if (sum > std::numeric_limits<long double>::max())
                throw CalculationError("Overflow detected in calculation");

            long double value = sum / averageSize;
            auto element = ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE
                                                                            , value);
            result[i] = std::move(element);
        }
    } else {
        throw CalculationError("There are no previous calculations");
    }
    return std::move(result);
}


std::unique_ptr<DataProcessor> DataProcessorFactory::createProcessor(const OperationType type
                                                                    , const Data &operands) 
{
    switch (type) {
    case OperationType::MULTIPLY:
        return std::make_unique<MultiplyByProcessor>(type, operands);
    case OperationType::LOG:
        return std::make_unique<LogarithmBaseProcessor>(type, operands);
    case OperationType::POWER:
        return std::make_unique<PowerProcessor>(type, operands);
    case OperationType::AVERAGE:
        return std::make_unique<AverageLastProcessor>(type, operands);
    default:
        return nullptr;
    }
}