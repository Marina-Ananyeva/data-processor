#include "cash.h"

void Cash::addResult(const Data &result) 
{
    if (m_cash.size() > CASH_SIZE) {
         m_cash.erase(m_cash.begin());
    }
    m_cash.push_back(result);
}

size_t Cash::getCashSize() const
{
    return m_cash.size();
}

const std::vector<Data> &Cash::getCash() const {
    return m_cash;
}

const Data &Cash::getLastCash() const {
    return m_cash.back();
}
