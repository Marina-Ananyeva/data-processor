#pragma once

#include <memory>
#include <vector>

#include "common.h"
#include "input_data.h"
#include "processor.h"
#include "output_data.h"
#include "settings.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для решения задачи
class Solution {
public:
    Solution() = default;

    Solution(const DataFiles &filesName);

    void process();

    ~Solution() = default;

private:
    DataFiles m_filesName;
    SettingsParams m_settings;
    InputData m_inputData;
    OutputData m_outputData;
    std::vector<std::unique_ptr<DataProcessor>> m_processors;
};