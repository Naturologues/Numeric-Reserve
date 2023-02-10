/*
 * File: Clock.cpp
 *
 * Made by Sand
 */

#include "userosc.h"
#include "Clock.hpp"

typedef struct State
{
  //Controls
  float shape;
  float shiftShape;
} State;

static Clock clock;
static State s_state;

void OSC_INIT(uint32_t platform, uint32_t api)
{
  (void)platform;
  (void)api;
  clock.setParams(s_state.shape, s_state.shiftShape);
}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{
  clock.setParams(s_state.shape, s_state.shiftShape);
  for (int sample = 0; sample < frames; sample++)
  {
    yn[sample] = f32_to_q31(clock.process());
  }
}

void OSC_NOTEON(const user_osc_param_t * const params)
{
  clock.reset();
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
    s_state.shape = param_val_to_f32(value) * (2000.f - 60.f) + 60.f;
    break;
    
  case k_user_osc_param_shiftshape:
    // 10bit parameter
    s_state.shiftShape = param_val_to_f32(value); 
    break;
    
  default:
    break;
  }
}

