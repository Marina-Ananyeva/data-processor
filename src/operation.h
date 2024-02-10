#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <optional>
#include <vector>

#include "common.h"
#include "element.h"

using Data = std::vector<std::shared_ptr<Element>>;

class Operation
{
public:
    Operation() = default;
    Operation(const Data &operands = 
             Data{}) 
    {
        if (!operands.empty()) {
            setOperands(operands);
        }
    }

    virtual std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) = 0;

    ~Operation() = default;

protected:
    Data m_operands;

private:
    void setOperands(const Data &operands)
    {
        for (const auto operand : operands) {
            m_operands.push_back(operand);
        }
    }
};

class MultiplyByOperation final : public Operation
{
public:
    MultiplyByOperation() = default;
    MultiplyByOperation(const Data &operands = 
                        Data{}) :
    Operation(operands)
    {
    }

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override
    {
        if (m_operands.empty()) 
            long double result = element->getValue() * MULTIPLY_BY_OPERAND;

        long double result = element->getValue() * m_operands.front()->getValue();

        if (result > std::numeric_limits<long double>::max())
            throw CalculationError("Overflow detected in calculation");

        return ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE, result);
    }
};

class LogarithmBaseOperation final : public Operation
{
public:
    LogarithmBaseOperation() = default;
    LogarithmBaseOperation(const Data &operands = 
                          Data{}) :
    Operation(operands)
    {
    }

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override
    {
        if (element->getValue() > 0) {
            if (m_operands.empty()) 
                long double result = log(element->getValue()) / log(LOGARITHM_BASE_OPERAND);
            long double result = log(element->getValue()) / log(m_operands.front()->getValue());

            if (result > std::numeric_limits<long double>::max())
                throw CalculationError("Overflow detected in calculation");

            return ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE, result);
        } else {
            throw CalculationError("Logarithm of zero or less is undefined");
        }
    }
};

class PowerOperation final : public Operation
{
public:
    PowerOperation() = default;
    PowerOperation(const Data &operands = 
                  Data{}) :
    Operation(operands)
    {
    }

    std::shared_ptr<Element> processOperation(const std::shared_ptr<Element> element) override
    {
        if (m_operands.empty()) 
            long double result = pow(element->getValue(), POWER_OPERAND);

        long double result = pow(element->getValue(), m_operands.front()->getValue());

        if (result > std::numeric_limits<long double>::max())
            throw CalculationError("Overflow detected in calculation");

        return ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE, result);
    }
};

// Фабрика для создания операций
class OperationsFactory {
public:
    OperationsFactory() = default;
    std::unique_ptr<Operation> createOperation(const OperationType type
                                              , const Data &operands = 
                                              Data{}) {
        switch (type) {
        case OperationType::MULTIPLY:
            return std::make_unique<MultiplyByOperation>(operands);
        case OperationType::LOG:
            return std::make_unique<LogarithmBaseOperation>(operands);
        case OperationType::POWER:
            return std::make_unique<PowerOperation>(operands);
        default:
            return nullptr;
        }
    }
};