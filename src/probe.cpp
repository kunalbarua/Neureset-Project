#include "probe.hpp"

// Constructor
Probe::Probe(int id) : 
    probeId(id),
    waveform(0) {
}

// Method to apply the given offset to the current waveform
void Probe::applyFeedBack(double offset) {
    waveform += offset * QRandomGenerator::global()->bounded(1, 6) / 100;
}

// Method to generate a random waveform
void Probe::measureWaveform(int waveType) {
    if(waveType == ALPHA_WAVE)
        waveform = WaveformGenerator::generateAlphaWave();
    else if (waveType == BETA_WAVE)
        waveform = WaveformGenerator::generateBetaWave();
    else if (waveType == DELTA_WAVE)
        waveform = WaveformGenerator::generateDeltaWave();
    else if (waveType == THETA_WAVE)
        waveform = WaveformGenerator::generateThetaWave();
}

// Waveform getter
double Probe::getWaveform() {
    return waveform;
}
