#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <vector>

#include "common.h"
#include "element.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для выходных данных
class OutputData {
public:
    OutputData() = default;

    OutputData(ElementType type);

    void addResult(const Data &data);

    void saveResultToFile(const std::string &filename) const;

    ~OutputData() = default;

private:
    ElementType m_type;
    Data m_outputData;
};