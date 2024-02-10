#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "element.h"
#include "reader.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для входных данных
class InputData {
public:
    InputData() = default;
    InputData(const std::string &filename, ElementType type);
    ~InputData() = default;

    const Data &getData() const;

private:
    bool isNumber(const std::string &s) const;

    ElementType m_type;
    Data m_data;
};
