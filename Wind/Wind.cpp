/*
 * File: Wind.cpp
 *
 * Made by Sand
 */

#include "userosc.h"
#include "Wind.hpp"
#include "LineNew.hpp"

typedef struct State
{
  float shape = 0.f;
  float shiftshape = 0.f;
} State;

static State s_state;
static Wind myWind;

void OSC_INIT(uint32_t platform, uint32_t api)
{
  (void)platform;
  (void)api;
  myWind.start();
  myWind.setParam(1.f, 220.f, s_state.shape, s_state.shiftshape);
}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{

  float frequency = osc_notehzf(params->pitch >> 8);
  myWind.setParam(100.f, frequency, s_state.shape, s_state.shiftshape);
  
  for (int sample = 0; sample < frames; sample++)
  {
    float sortie = myWind.process();
    yn[sample] = f32_to_q31(sortie);
  }

}

void OSC_NOTEON(const user_osc_param_t * const params)
{

}

void OSC_NOTEOFF(const user_osc_param_t * const params)
{
  (void)params;
}

void OSC_PARAM(uint16_t index, uint16_t value)
{  
  switch (index) {
  case k_user_osc_param_shape:
    // 10bit parameter
    s_state.shape = param_val_to_f32(value);
    break;
    
  case k_user_osc_param_shiftshape:
    // 10bit parameter
    s_state.shiftshape = param_val_to_f32(value); 
    break;
    
  default:
    break;
  }
}

