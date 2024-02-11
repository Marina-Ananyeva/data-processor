#pragma once

#include <memory>
#include <vector>

#include "common.h"
#include "element.h"

using Data = std::vector<std::shared_ptr<Element>>;

class Operation
{
public:
    Operation() = default;

    Operation(const Data &operands = Data{});

    virtual std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) = 0;

    ~Operation() = default;

protected:
    Data m_operands;

private:
    void setOperands(const Data &operands);
};

class MultiplyByOperation final : public Operation
{
public:
    MultiplyByOperation() = default;

    MultiplyByOperation(const Data &operands = Data{});

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override;
};

class LogarithmBaseOperation final : public Operation
{
public:
    LogarithmBaseOperation() = default;

    LogarithmBaseOperation(const Data &operands = Data{});

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override;
};

class PowerOperation final : public Operation
{
public:
    PowerOperation() = default;

    PowerOperation(const Data &operands = Data{});

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override;
};

// Фабрика для создания операций
class OperationsFactory 
{
public:
    OperationsFactory() = default;

    std::unique_ptr<Operation> createOperation(const OperationType type, const Data &operands =
                                              Data{});

    ~OperationsFactory() = default;
};