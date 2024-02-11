#include "operation.h"

#include <cmath>
#include <limits>

Operation::Operation(const Data &operands) 
{
    if (!operands.empty()) {
        setOperands(operands);
    }
}

void Operation::setOperands(const Data &operands)
{
    for (const auto operand : operands) {
        m_operands.push_back(operand);
    }
}


MultiplyByOperation::MultiplyByOperation(const Data &operands) :
    Operation(operands)
{
}

std::shared_ptr<Element> MultiplyByOperation::processOperation(const std::shared_ptr<Element> element) 
{
    if (m_operands.empty()) 
        long double result = element->getValue() * MULTIPLY_BY_OPERAND;

    long double result = element->getValue() * m_operands.front()->getValue();

    if (result > std::numeric_limits<long double>::max())
        throw CalculationError("Overflow detected in calculation");

    return ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE, result);
}


LogarithmBaseOperation::LogarithmBaseOperation(const Data &operands) :
    Operation(operands)
{
}

std::shared_ptr<Element> LogarithmBaseOperation::processOperation(const std::shared_ptr<Element> element) 
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


PowerOperation::PowerOperation(const Data &operands) :
    Operation(operands)
{
}

std::shared_ptr<Element> PowerOperation::processOperation(const std::shared_ptr<Element> element) 
{
    if (m_operands.empty()) 
        long double result = pow(element->getValue(), POWER_OPERAND);

    long double result = pow(element->getValue(), m_operands.front()->getValue());

    if (result > std::numeric_limits<long double>::max())
        throw CalculationError("Overflow detected in calculation");

    return ElementsFactory<long double>().createElement(ElementType::LONG_DOUBLE, result);
}


std::unique_ptr<Operation> OperationsFactory::createOperation(const OperationType type
                                                              , const Data &operands) 
{
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
