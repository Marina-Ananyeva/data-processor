#include "output_data.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdexcept>

OutputData::OutputData(ElementType type) :
    m_type(type)
{
}

void OutputData::addResult(const Data &data) 
{
    for (const auto &element : data) {
        try {
            long double number = element->getValue();
            if (m_type == ElementType::INT) {
                if (number > std::numeric_limits<int>::max())
                    throw CalculationError("Overflow detected in calculation");
                int value = static_cast<int>(round(number));
                auto newElement = ElementsFactory<int>().createElement(m_type, value);
                m_outputData.push_back(std::move(newElement));
            } else if (m_type == ElementType::FLOAT) {
                if (number > std::numeric_limits<float>::max())
                    throw CalculationError("Overflow detected in calculation");
                float value = static_cast<float>(number);
                auto newElement = ElementsFactory<float>().createElement(m_type, value);
                m_outputData.push_back(std::move(newElement));
            } else if (m_type == ElementType::DOUBLE) {
                if (number > std::numeric_limits<double>::max())
                    throw CalculationError("Overflow detected in calculation");
                double value = static_cast<double>(number);
                auto newElement = ElementsFactory<double>().createElement(m_type, value);
                m_outputData.push_back(std::move(newElement));
            }
        } catch (const ValidityError &ex) {
            throw ex;
        } catch (const std::exception &ex) {
            throw ValidityError(std::string("Invalid type of output data - ") + ex.what());
        }
    }
}

void OutputData::saveResultToFile(const std::string& filename) const 
{
    std::ofstream output(filename);
    if (!output.is_open()) {
        throw std::runtime_error("Unable to create output file.");
    }

        for (const auto &element : m_outputData) {
        if (m_type == ElementType::FLOAT)
            output << std::fixed << std::setprecision(10) << element->getValue() << std::endl;
        else
            output << element->getValue() << std::endl;
    }

    output.close();
}