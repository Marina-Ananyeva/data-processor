#pragma once

#include <execution>
#include <memory>
#include <vector>

#include "cash.h"
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

    template <class ExecutionPolicy>
    void process(const ExecutionPolicy& policy);

    ~Solution() = default;

private:
    DataFiles m_filesName;
    SettingsParams m_settings;
    InputData m_inputData;
    OutputData m_outputData;
    std::vector<std::unique_ptr<DataProcessor>> m_processors;
};

template <class ExecutionPolicy>
void Solution::process(const ExecutionPolicy& policy) 
{
    std::unique_ptr<Cash> cash = std::make_unique<Cash>();
    Data currentData = m_inputData.getData();
    for (const auto &processor : m_processors) {
        std::vector<Data> data;
        if (processor->getType() == OperationType::AVERAGE) {
            data = cash->getCash();
        } else {
            data.push_back(currentData);
        }
        if (std::is_same_v<ExecutionPolicy, std::execution:: sequenced_policy>)
            currentData = processor->process(data);
        else 
            currentData = processor->process(data);
        cash->addResult(currentData);
    }

    m_outputData.addResult(currentData);

    m_outputData.saveResultToFile(m_filesName.m_outputFileName);
}