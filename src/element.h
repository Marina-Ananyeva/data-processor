#pragma once

template<typename T>
class Element {
public:
    Element() = default;
    Element(T value);
    virtual T getValue() const = 0;
    virtual ~Element() = default;

protected:
    T m_value;
};

class IntElement final : public Element<int> {
public:
    IntElement(int value);
    int getValue() const override;
};

class FloatElement final : public Element<float> {
public:
    FloatElement(float value);
    float getValue() const override;
};

template<typename T>
Element<T>::Element(T value) : 
m_value(value) 
{
}
