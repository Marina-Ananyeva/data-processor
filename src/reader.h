#pragma once

#include <sstream>
#include <string>
#include <utility>

#include "common.h"
#include "element.h"
#include "json.h"

using Data = std::vector<std::shared_ptr<Element>>;

class Reader
{
public:
    ElementType readElemType(const std::string &elemName) const
    {
        if (elemName == "int")
            return ElementType::INT;
        else if (elemName == "float")
            return ElementType::FLOAT;
        else
            throw ValidityError("Invalid name of " + elemName);
    }

    OperationType readOperationType(const std::string &operationName) const
    {
        if (operationName == "multiply")
            return OperationType::MULTIPLY;
        else if (operationName == "logarithm")
            return OperationType::LOG;
        else if (operationName == "power")
            return OperationType::POWER;
        else if (operationName == "average")
            return OperationType::AVERAGE;
        else
            throw ValidityError("Invalid name of " + operationName);
    }

    std::unique_ptr<Element> parseNumber(std::istream& input) const {
        std::string parsedNum;

        // Считывает в parsedNum очередной символ из input
        auto readChar = [&parsedNum, &input] {
            parsedNum += static_cast<char>(input.get());
            if (!input) {
                throw ValidityError("Failed to read number from string");
            }
        };

        // Считывает одну или более цифр в parsedNum из input
        auto readDigits = [&input, readChar] {
            if (!std::isdigit(input.peek())) {
                throw ValidityError("A digit is expected");
            }
            while (std::isdigit(input.peek())) {
                readChar();
            }
        };

        if (input.peek() == '-') {
            readChar();
        }
    
        // Парсим целую часть числа
        if (input.peek() == '0') {
            readChar();
            // После первого 0 не могут идти другие цифры
        } else {
            readDigits();
        }

        bool isInt = true;
        // Парсим дробную часть числа
        if (input.peek() == '.') {
            readChar();
            readDigits();
            isInt = false;
        }

        // Парсим экспоненциальную часть числа
        if (int ch = input.peek(); ch == 'e' || ch == 'E') {
            readChar();
            if (ch = input.peek(); ch == '+' || ch == '-') {
                readChar();
            }
            readDigits();
            isInt = false;
        }

        // если в потоке еще остались какие-то символы
        if (!input.eof()) {
            throw ValidityError("Failed to read number from string");
        }

        try {
            if (isInt) {
                // Сначала пробуем преобразовать строку в int
                try {
                    int value = std::stoi(parsedNum);
                    auto element = ElementsFactory<int>().createElement(ElementType::INT, value);
                    return std::move(element);
                } catch (...) {
                    // В случае неудачи, например, при переполнении
                    // код ниже попробует преобразовать строку в float / double
                }
            }
            try {
                float value = std::stof(parsedNum);
                auto element = ElementsFactory<float>().createElement(ElementType::FLOAT, value);
                return std::move(element);
            } catch (...) {
                // В случае неудачи, например, при переполнении
                // код ниже попробует преобразовать строку в double
            }
            try {
                double value = std::stod(parsedNum);
                auto element = ElementsFactory<double>().createElement(ElementType::DOUBLE, value);
                return std::move(element);
            } catch (const ValidityError &ex) {
                throw ex;
            } catch (const std::exception &ex) {
                throw ValidityError("Failed to convert " + parsedNum + " to number" + ex.what());
            }
        } catch (const ValidityError &ex) {
            throw ex;
        } catch (const std::exception &ex) {
            throw ValidityError("Failed to convert " + parsedNum + " to number" + ex.what());
        }
    }

    std::unique_ptr<Element> parseStringToElement(const std::string &data) const
    {
        try {
            std::stringstream ss(data);
            auto element = parseNumber(ss);
            return std::move(element);
        } catch (const ValidityError &ex) {
            throw ex;
        } catch (const std::exception &ex) {
            throw ValidityError(std::string("Invalid parsing input data ") + data + " - " + ex.what());
        }
    }

    std::vector<std::pair<OperationType, Data>> readOperations(const json::Array &operations) {
        std::vector<std::pair<OperationType, Data>> result;
        for (const auto &operation : operations) {
            json::Dict params = operation.AsDict();
            OperationType type;
            Data operandsVec;
            for (const auto &[key, val] : params) {
                if (key == "type") {
                    type = readOperationType(val.AsString());
                } else if (key == "operand") {
                    json::Array operands = val.AsArray();
                    for (const auto element : operands) {
                        auto elem = std::move(parseStringToElement(element.AsString()));
                        operandsVec.push_back(std::move(elem));
                    }
                }
            }
            result.push_back(std::make_pair(type, std::move(operandsVec)));
        }
        return std::move(result);
    }
};