#pragma once
// Generate ramps and line segments from one value to another within a specified amount of time.

struct RampLine {

    
public :
	float m_sampleRate		= 48000.f	;
	float m_startValue		= 1.0f		;
	float m_endValue		= 0.0f		;
	float m_durationMs		= 1000.f	;
	float m_currentTimeMs	= 0.f		;
	bool m_isEnd			= false		;

	// Return current value and increment temporally
	float getValue(void)
	{
		float value = 0.f;

		if (m_currentTimeMs <= m_durationMs) {
			value = m_currentTimeMs * (m_endValue - m_startValue) / m_durationMs + m_startValue;
			m_currentTimeMs += 1000.0f / m_sampleRate;
		}
		else {
			value = m_endValue;
			m_isEnd = true;
		}
		return value;
	}

	// Set duration of ramp and set it to start
    void setDuration(float durationMs)
	{
		m_durationMs = durationMs;
		m_currentTimeMs = 0.f;
		m_isEnd = false;
	}
	// Set all values of ramp and set it to start
	void setAllValues(float sV, float eV, float dur)
	{
		m_startValue = sV;
		m_endValue = eV;
		m_durationMs = dur;
		m_currentTimeMs = 0.f;
		m_isEnd = false;
	}
};
