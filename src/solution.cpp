#include "solution.h"

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

