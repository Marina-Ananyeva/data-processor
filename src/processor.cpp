#include "processor.h"

#include <limits>
#include <string>

DataProcessor::DataProcessor(OperationType type, const Data &operands) :
    m_type(type),
    m_operation(std::move(OperationsFactory().createOperation(type, operands)))
{
}

Data DataProcessor::process(const std::vector<Data> &data) const
{
    Data result;
    if (!data.empty()) {
        for (const auto element : data.front()) {
            auto value = m_operation->processOperation(element);
            result.push_back(value);
        }
    }

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