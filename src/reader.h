#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "common.h"
#include "element.h"
#include "json.h"

using Data = std::vector<std::shared_ptr<Element>>;

class Reader
{
public:
    Reader() = default;

    ElementType readElemType(const std::string &elemName) const;

    OperationType readOperationType(const std::string &operationName) const;

    std::unique_ptr<Element> parseNumber(std::istream &input) const;

    std::unique_ptr<Element> parseStringToElement(const std::string &data) const;

    std::vector<std::pair<OperationType, Data>> readOperations(const json::Array &operations);

    ~Reader() = default;
};