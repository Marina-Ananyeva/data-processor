#include "element.h"

IntElement::IntElement(int value) : 
    Element<int>(value) 
{
}

int IntElement::getValue() const
{ 
    return m_value; 
}

FloatElement::FloatElement(float value) : 
    Element<float>(value)
{
}

float FloatElement::getValue() const
{ 
    return m_value;
}
