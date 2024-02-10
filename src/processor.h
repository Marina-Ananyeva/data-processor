#pragma once

#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "cash.h"
#include "input_data.h"
#include "operation.h"
#include "output_data.h"
#include "settings.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Базовый класс для обработчика операций
class DataProcessor {
public:
    DataProcessor(OperationType type, const Data &operands = 
                        Data{}) :
    m_type(type),
    m_operation(std::move(OperationsFactory().createOperation(type, operands)))
    {
    }
    ~DataProcessor() = default;

    virtual Data process(const std::vector<Data> &data) const
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

    OperationType getType() const
    {
        return m_type;
    }

protected:
    OperationType m_type;
    std::unique_ptr<Operation> m_operation;
};

// Производные классы для различных операций
class MultiplyByProcessor : public DataProcessor {
public:
    MultiplyByProcessor(OperationType type, const Data &operands = 
                        Data{}) :
        DataProcessor(type, operands) 
    {
    }
};

class LogarithmBaseProcessor : public DataProcessor {
private:
    int base;

public:
    LogarithmBaseProcessor(OperationType type, const Data &operands = 
                          Data{}) :
        DataProcessor(type, operands) 
    {
    }
};

class PowerProcessor : public DataProcessor {
private:
    int exponent;

public:
    PowerProcessor(OperationType type, const Data &operands = 
                  Data{}) :
        DataProcessor(type, operands) 
    {
    }
};

class AverageLastProcessor : public DataProcessor {
public:
    AverageLastProcessor(OperationType type, const Data &operands = 
                        Data{}) :
        DataProcessor(type, operands) 
    {
    }

    Data process(const std::vector<Data> &data) const override {
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
};

// Фабрика для создания обработчиков операций
class DataProcessorFactory {
public:
    static std::unique_ptr<DataProcessor> createProcessor(const OperationType type
                                              , const Data &operands = 
                                              Data{}) {
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
};