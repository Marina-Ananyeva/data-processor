#pragma once

#include <memory>
#include <vector>

#include "operation.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Базовый класс для обработчика операций
class DataProcessor 
{
public:
    DataProcessor() = default;

    DataProcessor(OperationType type, const Data &operands = Data{});

    virtual Data process(const std::vector<Data> &data) const;

    virtual Data processPar(const std::vector<Data> &data) const;

    OperationType getType() const;

    ~DataProcessor() = default;

protected:
    OperationType m_type;
    std::unique_ptr<Operation> m_operation;
};

// Производные классы для различных операций
class MultiplyByProcessor : public DataProcessor 
{
public:
    MultiplyByProcessor(OperationType type, const Data &operands = Data{});
};

class LogarithmBaseProcessor : public DataProcessor 
{
public:
    LogarithmBaseProcessor(OperationType type, const Data &operands = Data{});
};

class PowerProcessor : public DataProcessor 
{
public:
    PowerProcessor(OperationType type, const Data &operands = Data{});
};

class AverageLastProcessor : public DataProcessor 
{
public:
    AverageLastProcessor(OperationType type, const Data &operands = Data{});

    Data process(const std::vector<Data> &data) const override;

    Data processPar(const std::vector<Data> &data) const override;
};

// Фабрика для создания обработчиков операций
class DataProcessorFactory 
{
public:
    DataProcessorFactory() = default;

    std::unique_ptr<DataProcessor> createProcessor(const OperationType type, const Data &operands =
                                                   Data{});

    ~DataProcessorFactory() = default;
};