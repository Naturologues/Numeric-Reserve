// Random generator of values in a given range, modifiable

// Made by Sand

#include "userosc.h"
#include "LineNew.hpp"

struct genAlea 
{
private:
    // Minimum and maximum value for random
    float m_minValue, m_maxValue;
    // Minumum ans maximum current value of travel time between the first and the second value
    float m_currentMaxValue, m_currentMinValue;
    // Maximum and minimum initial duration 
    float m_minDuration, m_maxDuration;
    // Saving the last generated value
    float m_lastValue = 0.f;
    // Ramp allows to go from one value to another in a given time
    LineNew m_line;
    // Temporal distance coefficient [1 -> maxCurrent=max, minCurrent=min] [0 -> maxCurrent = minCurrent = (max-min)/2)]
    float m_coefficient = 1.f;

public:
    //Constructor
    genAlea(float mV, float MV, float mD, float MD)
    {
        m_minValue = m_currentMinValue = mV;
        m_maxValue = m_currentMaxValue = MV;
        m_minDuration = mD;
        m_maxDuration = MD;
        m_lastValue = m_minValue;
    }

    // When ramp end, get and set new random values
    // Register actual value in last value after put it on the ramp
    void resetValue(void)
    {
        float deltaF = (m_maxValue - m_minValue) / 2.f;
        m_currentMinValue = m_minValue + deltaF * m_coefficient;
        m_currentMaxValue = m_maxValue - deltaF * m_coefficient;

        float duration = m_minDuration + (osc_white()+1.f)/2.f * (m_maxDuration-m_minDuration);
        float value = m_currentMinValue + (osc_white()+1.f)/2.f * (m_currentMaxValue-m_currentMinValue);
        m_line.setAllValues(m_lastValue, value, duration);
        m_lastValue = value;
    }

    // Return value of the ramp at curent time
    // If the ramp is end, call resetValue() to set another value
    float getValue(float knobA)
    {
        // Set coefficient for next call of resetValue()
        m_coefficient = knobA;
        if (m_line.m_isEnd)
            resetValue();
        return m_line.getValue();
    }
};