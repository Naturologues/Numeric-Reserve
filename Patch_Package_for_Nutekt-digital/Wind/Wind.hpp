/* Modifiable wind generator using two controls
* Knob A : Wind displacement control. 1 value stop the movement
* Knob B : We combine with the wind a resonnant filter at the same pitch of note played
* 
* Made by Sand 
*/

#pragma once

#include "userosc.h"
#include "biquad.hpp"
#include "GenAlea.hpp"

struct Wind
{
private:
    float m_sampleRate = 48000.f                ;

    dsp::BiQuad m_biqLp                         ;
    dsp::BiQuad m_biqF1                         ;
    dsp::BiQuad m_biqF2                         ;
    dsp::BiQuad m_biqF3                         ;
    dsp::BiQuad m_resFilter                     ;
    dsp::BiQuad m_notchFilter                   ;
    
    float m_Q = 10.f;
    genAlea m_fcF1{ 20.f,550.f,500.f,5500.f}    ;
    genAlea m_fcF2{ 380.f,1400.f,500.f,5500.f}  ;
    genAlea m_fcF3{ 858.f,2086.f,500.f,5500.f}  ;

    // resFilter param
    float m_resQ            = 50.f              ;
    float m_resFrequency    = 440.f             ;

    //Controls
    float m_shape           = 0.f               ;
    float m_shiftshape      = 0.f               ;

    // End Gains
    float m_kbGW            = 0.8f              ;
    float m_kbGNotch        = 0.f               ;
    float m_kbGFM           = 0.f               ;

public:
    void start(void)
    {
        // Set one low-pass, 3 band pass for wind, and 1 band pass with 1 band reject filter for the resonnance
        m_biqLp.mCoeffs.setFOLP(tanf(M_PI*m_biqLp.mCoeffs.wc(200.0f, 1.f/m_sampleRate)));
        m_biqF1.mCoeffs.setSOBP(tanf(M_PI*m_biqF1.mCoeffs.wc(m_fcF1.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        m_biqF2.mCoeffs.setSOBP(tanf(M_PI*m_biqF2.mCoeffs.wc(m_fcF2.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        m_biqF3.mCoeffs.setSOBP(tanf(M_PI*m_biqF3.mCoeffs.wc(m_fcF3.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        m_resFilter.mCoeffs.setSOBP(tanf(M_PI*m_resFilter.mCoeffs.wc(m_resFrequency, 1.f/m_sampleRate)), m_resQ);
        m_notchFilter.mCoeffs.setSOBR(tanf(M_PI*m_notchFilter.mCoeffs.wc(m_resFrequency, 1.f/m_sampleRate)), m_resQ);
        m_fcF1.resetValue();
        m_fcF2.resetValue();
        m_fcF3.resetValue();
    }

    void setParam(float vel, float pitch, float ka, float kb)
    {
        //m_resFilter param
        m_resQ = vel;
        m_resFrequency = pitch;

        //Controls
        m_shape = ka;
        m_shiftshape = kb;
    }

    // Resonnant filter function
    // buffer value is current sample
    float knobB(float buffer)
    {
        float clip = 0.3f;
        buffer = clipmaxf(buffer, clip);
        buffer = clipminf(-clip, buffer);
        buffer /= clip;

        float fcFilter = m_resFrequency;
        m_resFilter.mCoeffs.setSOBP(tanf(M_PI*m_resFilter.mCoeffs.wc(fcFilter, 1.f/m_sampleRate)), m_resQ);

        return m_resFilter.process_so(buffer);
    }

    float process()
    {
        float noise = osc_white();
        float lowPass = m_biqLp.process_fo(noise);

        m_biqF1.mCoeffs.setSOBP(tanf(M_PI*m_biqF1.mCoeffs.wc(m_fcF1.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        float firstB = m_biqF1.process_so(noise);

        m_biqF2.mCoeffs.setSOBP(tanf(M_PI*m_biqF2.mCoeffs.wc(m_fcF2.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        float secondB = m_biqF2.process_so(noise);

        m_biqF3.mCoeffs.setSOBP(tanf(M_PI*m_biqF3.mCoeffs.wc(m_fcF3.getValue(m_shape), 1.f/m_sampleRate)), m_Q);
        float thirdB = m_biqF3.process_so(noise);

        m_kbGFM = 30.f*m_shiftshape;
        m_kbGNotch = 0.2f*m_shiftshape;
        m_kbGW = 0.6f*(1.f-m_shiftshape);

        float windd = (lowPass + firstB + secondB + 0.8f * thirdB);

        m_notchFilter.mCoeffs.setSOBR(tanf(M_PI*m_notchFilter.mCoeffs.wc(m_resFrequency, 1.f/m_sampleRate)), m_resQ);
        float notch = m_notchFilter.process_so(windd);

        return m_kbGW * windd + m_kbGNotch * notch + m_kbGFM * knobB(noise);
    }
};
