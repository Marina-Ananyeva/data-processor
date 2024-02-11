#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

const int MULTIPLY_BY_OPERAND = 10;
const int LOGARITHM_BASE_OPERAND = 10;
const int POWER_OPERAND = 2;
const int AVERAGE_COUNT = 10;

/**
 * @brief Структура - тип данных
 * 
 */
enum class ElementType
{
    INT,
    FLOAT,
    DOUBLE,
    LONG_DOUBLE
};

/**
 * @brief Структура - тип операции
 * 
 */
enum OperationType {
    MULTIPLY,
    LOG,
    POWER,
    AVERAGE
};

/**
 * @brief Структура для хранения названий файлов с данными
 * 
 */
struct DataFiles
{
    std::string m_configFileName{""};               // название файла с настройками
    std::string m_inputFileName{""};                // название файла с входными данными
    std::string m_outputFileName{""};               // название файла с выходными данными

    DataFiles(const std::string &configFileName, const std::string &inputFileName
                                              , const std::string &outputFileName) :
    m_configFileName(configFileName),
    m_inputFileName(inputFileName),
    m_outputFileName(outputFileName)
    {
    }
};

/**
 * @brief Класс - родитель для ошибок валидации
 * 
 */
class ValidityError : public std::logic_error 
{
public:
    ValidityError(const std::string &error_text) : std::logic_error(error_text) 
    {
    }
};

/**
 * @brief Класс - родитель для ошибок в вычислениях
 * 
 */
class CalculationError : public std::logic_error 
{
public:
    CalculationError(const std::string &error_text) : std::logic_error(error_text) 
    {
    }
};