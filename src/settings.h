#pragma once

#include <memory>
#include <vector>

#include "common.h"
#include "element.h"

using Data = std::vector<std::shared_ptr<Element>>;

// Класс для настроек
class SettingsParams 
{
public:
    SettingsParams() = default;

    SettingsParams(const std::string &filename);

    const ElementType &getInputType() const;

    const ElementType &getOutputType() const;

    const std::vector<std::pair<OperationType, Data>> &getOperations() const;

    ~SettingsParams() = default;

private:
    ElementType m_inputType;
    ElementType m_outputType;
    std::vector<std::pair<OperationType, Data>> m_operations;
};