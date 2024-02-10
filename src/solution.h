#pragma once

#include <string>
#include <vector>

#include "cash.h"
#include "input_data.h"
#include "operation.h"
#include "processor.h"
#include "output_data.h"
#include "settings.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для решения задачи
class Solution {
public:
    Solution() = default;
    Solution(const DataFiles &filesName) : 
        m_filesName(filesName),
        m_settings(filesName.m_configFileName),
        m_inputData(filesName.m_inputFileName, m_settings.getInputType()), 
        m_outputData(m_settings.getOutputType())
    {
        const std::vector<std::pair<OperationType, Data>> operations = m_settings.getOperations();
        for (const auto &[type, operands] : operations) {
            m_processors.push_back(std::move(DataProcessorFactory().createProcessor(type, operands)));
        }
    }

    ~Solution() = default;

    void process() {
        std::unique_ptr<Cash> cash = std::make_unique<Cash>();
        Data currentData = m_inputData.getData();
        for (const auto &processor : m_processors) {
            std::vector<Data> data;
            if (processor->getType() == OperationType::AVERAGE) {
                data = cash->getCash();
            } else {
                data.push_back(currentData);
            }
            currentData = processor->process(data);
            cash->addResult(currentData);
        }

        m_outputData.addResult(currentData);

       m_outputData.saveResultToFile(m_filesName.m_outputFileName);
    }

private:
    DataFiles m_filesName;
    SettingsParams m_settings;
    InputData m_inputData;
    OutputData m_outputData;
    std::vector<std::unique_ptr<DataProcessor>> m_processors;
};