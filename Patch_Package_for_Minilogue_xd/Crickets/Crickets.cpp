/*
 * File: Cricket.cpp
 *
 * Filter Source Model Oscillator
 * Knob A: resonance frequency control
 * Knob B: control of the shape and speed of the pulse train
 * 
 * Made by Syr
 */

#include "userosc.h"
#include "Metro.hpp"
#include "resFilterFM.hpp"
#include "biquad.hpp"


typedef struct State
{

    //Global FM
    float alpha     ;
    float amount    ;
    float ratio     ;
    float note      ;

    //FM1
    float fc1       ;

    //FM2
    float fc2       ;

    //FM3
    float fc3       ;

    //FM4
    float fc4       ;

    //Metro
    float step      ;
    int   count     ;
    int   maxCount  ;
    int   trigger   ;
    int   maxNbTrig ;

    //Controls
    float shape     ;
    float shiftshape;

} State;

static State s_state;

// Filters
static ResFilterFM resFilt1 ;
static ResFilterFM resFilt2 ;
static ResFilterFM resFilt3 ;
static ResFilterFM resFilt4 ;

dsp::BiQuad lowpass1        ;
dsp::BiQuad lowpass2        ;
dsp::BiQuad highpass        ;


// Metro
static Metro metro          ;

void OSC_INIT(uint32_t platform, uint32_t api)
{

    //Controls
    s_state.shape       = 0.f    ;
    s_state.shiftshape  = 0.f    ;


    //Global FM
    s_state.alpha       = 20.f   ;
    s_state.amount      = 0.f    ;
    s_state.ratio       = 0.f    ;
    s_state.note        = 214.f  ;

    //FM1
    s_state.fc1         = 4500.f ;

    //FM2
    s_state.fc2         = 4550.f ;

    //FM3
    s_state.fc3         = 4600.f ;
        
    //FM4
    s_state.fc4         = 9000.f ;
    
    //Metro
    s_state.step        = 17.f   ;
    s_state.count       = 0      ;
    s_state.maxCount    = 41     ;
    s_state.trigger     = 0      ;
    s_state.maxNbTrig   = 7      ;

    //lowpass
    lowpass1.mCoeffs.setFOLP( tanf( M_PI*lowpass1.mCoeffs.wc( 5000.f , 1.f/48000.f )))        ;

    //highpass
    highpass.mCoeffs.setFOHP( tanf( M_PI*highpass.mCoeffs.wc( 4000.f , 1.f/48000.f )))        ;

    //Metro
    metro.setIntervalMs(s_state.step)                                                         ;

}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{

    //controls
    float shape         =   s_state.shape                                         ;
    float shiftshape    =   s_state.shiftshape                                    ;

    //Global FM
    float alpha         =   s_state.alpha                                         ;
    float amount        =   s_state.amount                                        ;
    float ratio         =   s_state.ratio                                         ;
    float note          =   s_state.note = osc_notehzf((params->pitch)>>8)        ;

    //FM1
    float fc1           =   s_state.fc1                                           ;
    resFilt1.setParam(fc1*(1.f-shape)+shape*note,alpha,amount,ratio)              ;
    
    //FM2
    float fc2           =   s_state.fc2                                           ;
    resFilt2.setParam(fc2*(1.f-shape)+shape*4.f*note,alpha,amount,ratio)          ;

    //FM3
    float fc3           =   s_state.fc3                                           ;
    resFilt3.setParam(fc3*(1.f-shape)+shape*9.f*note,alpha,amount,ratio)          ;


    //FM4
    float fc4           =   s_state.fc4                                            ;
    resFilt4.setParam(fc4*(1.f-shape)+shape*16.f*note,alpha,amount,ratio)          ;


    highpass.mCoeffs.setFOHP( tanf( M_PI*highpass.mCoeffs.wc(clipminf(20.f, 4000.f*(1.f-shape)+shape*note), 1.f/48000.f )))        ;

    //Metro
    float step          = s_state.step                                              ;
    int count           = s_state.count                                             ;
    int maxCount        = s_state.maxCount                                          ;
    int trigger         = s_state.trigger                                           ;
    int maxNbTrig       = s_state.maxNbTrig + si_floorf(7 + step*(40 - 7))          ;
    metro.setIntervalMs(17.f + 83.f*step)                                           ;
    
    

    //Variable transport
    float s             = 0.f                                                       ;
    float e             = 0.f                                                       ;


    for (int sample = 0; sample < frames; sample++)
    {

        //Le Pull
        if (metro.getTimeMs()==0)
        {
            ++count %= maxCount ;

            if (count <= maxNbTrig)
            {
                trigger = 1 ;
            }
        
            else
            {
                trigger = 0 ;
            }
            
        }
        else
        {
            trigger = 0         ;
        }
        s_state.count = count;
        e = lowpass1.process_fo(trigger);
        s = resFilt1.process(e) + resFilt2.process(e) + resFilt3.process(e) + resFilt4.process(e) ;
        yn[sample] = f32_to_q31(highpass.process_fo(s));

        
    }
}

void OSC_NOTEON(const user_osc_param_t * const params)
{
    s_state.count=0.f;
    metro.restart();
}

void OSC_NOTEOFF(const user_osc_param_t * const params)
{
  (void)params;
}

void OSC_PARAM(uint16_t index, uint16_t value)
{ 
    const float p = param_val_to_f32(value);

    switch (index) 
    {
        case k_user_osc_param_shape:
        s_state.shape = p;
            break;
        
        case k_user_osc_param_shiftshape:
        s_state.step = p;
            break;
        
        default:
            break;
    }
}