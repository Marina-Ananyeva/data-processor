#include "input_data.h"

#include <exception>
#include <fstream>
#include <iostream>

#include "common.h"

InputData::InputData(const std::string& filename, ElementType type) :
    m_type(type)
{
        std::ifstream input(filename);
        if (!input.is_open()) {
            throw std::runtime_error("Unable to open input file.");
        }

        std::string line;
        Reader reader;
        while (std::getline(input, line)) {
            try {
                auto element = reader.parseStringToElement(line);
                if (element->getType() == type)
                    m_data.push_back(std::move(element));
                else
                    throw ValidityError("Not match input data type");
            } catch (const ValidityError &ex) {
                throw ex;
            } catch (const std::exception &ex) {
                throw ValidityError(std::string("Invalid parsing input data - ") + ex.what());
            }
        }

        input.close();
    }

const Data &InputData::getData() const {
    return m_data;
}