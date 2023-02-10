/*
 * FM resonnant filter
 *
 * Made by Lil Transiant
 * 
 */

#include "userosc.h"

struct ResFilterFM 
{
public:
    float m_omega0     = 1000.f ;
    float m_alpha      = 0.5f   ;
    float m_sampleRate = 48000.f;

    float m_phi   = 0.f;
    float m_inc   = 0.f;
    float m_R     = 0.f;
    float m_x1    = 0.f;
    float m_y1    = 0.f;
    float m_xPres = 0.f;
    float m_yPres = 0.f;
    float m_xPass = 0.f;
    float m_yPass = 0.f;

    float m_amountMod = 0.f ;
    float m_ratioMod  = 0.f ;
    float m_phiMod    = 0.f ;
    

    float process(float source)
    {
        m_inc = M_TWOPI * m_omega0 * m_ratioMod / m_sampleRate;
        m_phi = (M_TWOPI * m_omega0 + m_amountMod * (sinf(m_phiMod)) )/ m_sampleRate;
        m_x1 = m_R * cosf(m_phi);
        m_y1 = m_R * sinf(m_phi);

        m_xPass  = m_xPres;
        m_yPass  = m_yPres;
        m_xPres  = m_x1 * m_xPass - m_y1 * m_yPass + source;
        m_yPres  = m_x1 * m_yPass + m_y1 * m_xPass;

        m_phiMod += m_inc;
        m_phiMod -= si_floorf(m_phiMod / M_TWOPI) * M_TWOPI;

        return m_yPres*expf(m_alpha*M_PI/(2.f*m_omega0));
    }

    void setParam(float om, float a, float amount, float ratio)
    {
      m_alpha = a;
      m_omega0 = om;
      m_amountMod = amount;
      m_ratioMod = ratio;
      m_R=powf(M_E,(-m_alpha / m_sampleRate));

    }
};