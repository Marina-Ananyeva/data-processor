#include "solution.h"

#include "cash.h"

Solution::Solution(const DataFiles &filesName) : 
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

void Solution::process() 
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
        currentData = processor->process(data);
        cash->addResult(currentData);
    }

    m_outputData.addResult(currentData);

    m_outputData.saveResultToFile(m_filesName.m_outputFileName);
}
