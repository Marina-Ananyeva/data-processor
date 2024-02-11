#include "settings.h"

#include <fstream>
#include <string>

#include "reader.h"

SettingsParams::SettingsParams(const std::string& filename) 
{
    std::ifstream input(filename);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open settings file");
    }

    Reader reader;
    json::Dict settings{json::Load(input).GetRoot().AsDict()};

    for (const auto& [key, val] : settings) {
        if (key == "settings") {
            for (const auto& [key, val] : val.AsDict()) {
                if (key == "input") {
                    m_inputType = reader.readElemType(val.AsString());
                } else if (key == "operations") {
                    m_operations = reader.readOperations(val.AsArray());
                } else if (key == "output") {
                    m_outputType = reader.readElemType(val.AsString());
                }
            }
        }
    }

    input.close();
}

const ElementType &SettingsParams::getInputType() const 
{
    return m_inputType;
}

const ElementType &SettingsParams::getOutputType() const 
{
    return m_outputType;
}

const std::vector<std::pair<OperationType, Data>> &SettingsParams::getOperations() const 
{
    return m_operations;
}