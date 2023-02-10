/* Modifiable clock generator using two controls
* Knob A : Set time between 2 tic
* Knob B : Set randomly pitch 
* 
* Made by Sand 
*/

#pragma once

#include "userosc.h"
#include "Metro.hpp"

struct Clock
{
private:
    float m_sampleRate  = 48000.f                           ;
    //Control
    float m_shape       = 50.f                              ;
    float m_shiftShape  = 0.f                               ;

    float m_rand        = 0.f                               ;
    float m_timeRelease = 60.f                              ;
    int m_counter       = 0                                 ;
    float m_phase       = 0.f                               ;
    float m_inc         = M_TWOPI * 1000.f / m_sampleRate   ;
    Metro m_myMetro;

public:
    // Set parameter at each buffer loop
    // If knob B value change, we choose randomly a new value and set the increment phase
    void setParams(float ka, float kb)
    {
        m_shape = ka;
        if(m_shiftShape != kb)
        {
            m_shiftShape = kb;
            m_rand = (osc_white()+1.f)/2.f * 10000.f;
            m_inc = M_TWOPI * m_rand / m_sampleRate;
        }
    }
    void reset()
    {
        m_phase = 0.f;
        m_myMetro.restart();
    }
    float process()
    {
        float output = 0.f;
        float met = m_myMetro.getTimeMs();
        if(met == 0.f) // Each ticks of metro
        {
            m_myMetro.setIntervalMs(m_shape);
            ++m_counter %= 4; //We have 4 ticks
            output = sinf(m_phase)* sqrt(m_timeRelease - met);
        }
        else if(met <= m_timeRelease)
        {
            output = sinf(m_phase) * sqrt(m_timeRelease - met);
        }
        else
        {
            output = 0.f;
        }

        // Change pitch to the third tic (each 3/4 ticks)
        if(m_counter == 3)
        { 
            float inc2 = M_TWOPI * (m_rand * 1.5f) / m_sampleRate;
            m_phase += inc2;
            if(m_phase >= M_TWOPI) m_phase -= M_TWOPI;
        }
        else
        {
            m_phase += m_inc;
            if(m_phase >= M_TWOPI) m_phase -= M_TWOPI;
        }
        return output;
    }
};
