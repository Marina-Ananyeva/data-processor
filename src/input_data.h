#pragma once

#include <memory>
#include <string>
#include <vector>

#include "common.h"
#include "element.h"
#include "reader.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для входных данных
class InputData 
{
public:
    InputData() = default;

    InputData(const std::string &filename, ElementType type);

    const Data &getData() const;

    ~InputData() = default;

private:
    bool isNumber(const std::string &s) const;

    ElementType m_type;
    Data m_data;
};
