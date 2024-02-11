#pragma once

#include <memory>
#include <vector>

#include "element.h"

const int CASH_SIZE = 10;

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для хранения последних 10 результатов расчета
class Cash 
{
public:
    Cash() = default;

    void addResult(const Data &result);

    size_t getCashSize() const;

    const std::vector<Data> &getCash() const;

    const Data &getLastCash() const;

private:
    std::vector<Data> m_cash;
};