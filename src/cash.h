#pragma once

#include <memory>
#include <vector>

#include "element.h"

const int CASH_SIZE = 10;

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для хранения последних 10 результатов расчета
class Cash {
public:
    Cash() = default;

    void addResult(const Data &result) {
        if (m_cash.size() > CASH_SIZE) {
            m_cash.erase(m_cash.begin());
        }
        m_cash.push_back(result);
    }

    size_t getCashSize() const
    {
        return m_cash.size();
    }

    const std::vector<Data> &getCash() const {
        return m_cash;
    }

    const Data &getLastCash() const {
        return m_cash.back();
    }

private:
    std::vector<Data> m_cash;
};