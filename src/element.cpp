#include "element.h"

Element::Element::Element(ElementType type) :
    m_type(type)
{
}

ElementType Element::Element::getType() const
{
    return m_type;
}


IntElement::IntElement(ElementType type, int value) :
    Element(type),
    m_value(value)
{
}

long double IntElement::getValue() const 
{
    return static_cast<long double>(m_value);
}


FloatElement::FloatElement(ElementType type, float value) :
    Element(type),
    m_value(value)
{
}

long double FloatElement::getValue() const 
{
    return static_cast<long double>(m_value);
}


DoubleElement::DoubleElement(ElementType type, float value) :
    Element(type),
    m_value(value)
{
}

long double DoubleElement::getValue() const
{
    return static_cast<long double>(m_value);
}


LongDoubleElement::LongDoubleElement(ElementType type, float value) :
    Element(type),
    m_value(value)
{
}

long double LongDoubleElement::getValue() const
{
    return static_cast<long double>(m_value);
}
