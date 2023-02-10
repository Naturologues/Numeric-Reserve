/*
 * File: bells.cpp
 *
 * Morphing wavetable oscillator
 * 
 * Knob A : modulation depth
 * Knob B : modulation speed
 *
 * Made by Syr
 */

#include "userosc.h"
#include "biquad.hpp"

typedef struct State
{
  float inc;
  float phase1;
  float phase2;
  float phase3;
  float depth;
  float speedinc1;
  float speedinc2;
  float speedinc3;
  float speed1;
  float speed2;
  float speed3;
  float note;
} State;

static State s_state  ;
dsp::BiQuad highpass1 ;
dsp::BiQuad highpass2 ;
dsp::BiQuad highpass3 ;


void OSC_INIT(uint32_t platform, uint32_t api)
{
  s_state.note        = 0.f ;
  s_state.inc         = 0.f ;
  s_state.phase1      = 0.f ;
  s_state.phase2      = 0.f ;  
  s_state.phase3      = 0.f ;
  s_state.depth       = 0.f ;
  s_state.speed1      = 0.f ;
  s_state.speed2      = 0.f ;
  s_state.speed3      = 0.f ;
  }

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{
  // Definition grandeurs
  float Q = 10.f;
  s_state.note       = osc_notehzf((params->pitch)>>8);
  highpass1.mCoeffs.setSOHP( tanf( M_PI*highpass1.mCoeffs.wc( s_state.note, 1.f/48000.f )), Q)  ;
  highpass2.mCoeffs.setSOHP( tanf( M_PI*highpass2.mCoeffs.wc( 4.0041*s_state.note, 1.f/48000.f )), Q)  ;
  highpass3.mCoeffs.setSOHP( tanf( M_PI*highpass3.mCoeffs.wc( 7.037*s_state.note, 1.f/48000.f )), Q)  ;
  const float inc    = s_state.inc = osc_w0f_for_note((params->pitch)>>8, params->pitch & 0xFF);
  float phase1       = s_state.phase1       ;
  float phase2       = s_state.phase2       ;
  float phase3       = s_state.phase3       ;


  // Battements
  const float speedinc1 = M_TWOPI * s_state.speedinc1/48000;
  const float speedinc2 = M_TWOPI * s_state.speedinc2/48000;
  const float speedinc3 = M_TWOPI * s_state.speedinc3/48000;
  float depth        = s_state.depth      ;
  float speed1       = s_state.speed1     ;
  float speed2       = s_state.speed2     ;
  float speed3       = s_state.speed3     ;
  
  
  
  // Process
  float s1           = 0.f                ;
  float s2           = 0.f                ;
  float s3           = 0.f                ;
  float s            = 0.f                ;

  for(int sample = 0; sample < frames; sample++)
  {
    s1 = ((1.f - depth) + depth*cosf(speed1)) * osc_sinf(phase1)       ;
    s1=highpass1.process_so(s1);
    s2 = ((1.f - depth) + depth*cosf(speed2)) * 0.4f*osc_sinf(phase2)  ;
    s2=highpass1.process_so(s2);
    s3 = ((1.f - depth) + depth*cosf(speed3)) * 0.3f*osc_sinf(phase3)  ;
    s3=highpass1.process_so(s3);
    s=(s1+s2+s3)/(1.f+0.4f+0.3f);
    yn[sample] = f32_to_q31(s);



    phase1 += inc; 
    phase1 -= si_floorf(phase1);

    phase2 += 4.0041f*inc;
    phase2 -= si_floorf(phase2);

    phase3 += 7.037f*inc;
    phase3 -= si_floorf(phase3);

    speed1 += speedinc1;
    speed1 -= si_floorf(speed1 / M_TWOPI) * M_TWOPI ;

    speed2 += speedinc2;
    speed2 -= si_floorf(speed2 / M_TWOPI) * M_TWOPI ;

    speed3 += speedinc3;
    speed3 -= si_floorf(speed3 / M_TWOPI) * M_TWOPI ;

  }
  //


  s_state.phase1 = phase1 ;
  s_state.phase2 = phase2 ;
  s_state.phase3 = phase3 ;


  s_state.speed1 = speed1 ;
  s_state.speed2 = speed2 ;
  s_state.speed3 = speed3 ;

}

void OSC_NOTEON(const user_osc_param_t * const params)
{
  (void)params;
}

void OSC_NOTEOFF(const user_osc_param_t * const params)
{
  (void)params;
}

void OSC_PARAM(uint16_t index, uint16_t value) {
  const float p = param_val_to_f32(value) ;
	
  switch (index) {
	
		case k_user_osc_param_shape: // A knob
      s_state.depth = p ;
      break;
    case k_user_osc_param_shiftshape: // B knob
      s_state.speedinc1 = s_state.note * p*p ;
      s_state.speedinc2 = s_state.note *4.0041f * p*p ;
      s_state.speedinc3 = s_state.note *7.037f * p*p ;
      break;

		default: 
      break;
	}
}

