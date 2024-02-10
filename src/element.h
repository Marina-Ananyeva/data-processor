#pragma once

#include <memory>

#include "common.h"

class Element
{
public:
    Element() = default;

    Element(ElementType type) :
        m_type(type)
    {
    }

    virtual long double getValue() const = 0;
    ElementType getType() const
    {
        return m_type;
    }

    ~Element() = default;

private:
    ElementType m_type;
};

class IntElement final : public Element
{
public:
    IntElement() = default;

    IntElement(ElementType type, int value) :
        Element(type),
        m_value(value)
    {
    }

    long double getValue() const override
    {
        return static_cast<long double>(m_value);
    }

private:
    int m_value = 0;
};

class FloatElement final : public Element
{
public:
    FloatElement() = default;

    FloatElement(ElementType type, float value) :
    Element(type),
    m_value(value)
    {
    }

    long double getValue() const override
    {
        return static_cast<long double>(m_value);
    }

private:
    float m_value = 0;
};

class DoubleElement final : public Element
{
public:
    DoubleElement() = default;

    DoubleElement(ElementType type, float value) :
    Element(type),
    m_value(value)
    {
    }

    long double getValue() const override
    {
        return static_cast<long double>(m_value);
    }

private:
    double m_value = 0;
};

class LongDoubleElement final : public Element
{
public:
    LongDoubleElement() = default;

    LongDoubleElement(ElementType type, float value) :
    Element(type),
    m_value(value)
    {
    }

    long double getValue() const override
    {
        return static_cast<long double>(m_value);
    }

private:
    long double m_value = 0;
};

// Фабрика для создания элементов
template<typename T>
class ElementsFactory {
public:
    ElementsFactory() = default;
    std::unique_ptr<Element> createElement(const ElementType type, T value) {
        switch (type) {
        case ElementType::INT:
            return std::make_unique<IntElement>(type, value);
        case ElementType::FLOAT:
            return std::make_unique<FloatElement>(type, value);
        case ElementType::DOUBLE:
            return std::make_unique<DoubleElement>(type, value);
        case ElementType::LONG_DOUBLE:
            return std::make_unique<LongDoubleElement>(type, value);
        default:
            return nullptr;
        }
    }
};