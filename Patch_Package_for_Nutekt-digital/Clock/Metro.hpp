#pragma once
// Loop in x miliseconds
// When get back to 0, this is a tic of metronome 

struct Metro
{
  float m_intervalMs = 50.f;
  float m_currentTimeMs = 0.f;
  float m_samplingRate = 48000.f;

  void restart()
  {
    m_currentTimeMs = 0.f;
  }
  float getTimeMs()
  {
    float t = m_currentTimeMs;
    m_currentTimeMs += 1000.0f / m_samplingRate;
    if (m_currentTimeMs > m_intervalMs)
      m_currentTimeMs = 0.f;
    return t;
  }
  void setIntervalMs(float intervalMs)
  {
    m_intervalMs = intervalMs;
  }
};