#include "waveformgenerator.hpp"

// Function to generate random alpha dominant frequency
int WaveformGenerator::generateAlphaWave() {
    return generateWave(ALPHA_MIN, ALPHA_MAX);
}

// Function to generate random beta dominant frequency
int WaveformGenerator::generateBetaWave() {
    return generateWave(BETA_MIN, BETA_MAX);
}

// Function to generate random delta dominant frequency
int WaveformGenerator::generateDeltaWave() {
    return generateWave(DELTA_MIN, DELTA_MAX);
}

// Function to generate random theta dominant frequency
int WaveformGenerator::generateThetaWave() {
    return generateWave(THETA_MIN, THETA_MAX);
}

// Function to generate a random dominant frequency within the given min-max
int WaveformGenerator::generateWave(int min, int max) {
    QRandomGenerator* generator = QRandomGenerator::global();

    // Generating frequencies
    int f1 = generator->bounded(min, max);
    int f2 = generator->bounded(min, max);
    int f3 = generator->bounded(min, max);

    // Generating amplitudes
    int a1 = generator->bounded(AMPLITUDE_MIN, AMPLITUDE_MAX);
    int a2 = generator->bounded(AMPLITUDE_MIN, AMPLITUDE_MAX);
    int a3 = generator->bounded(AMPLITUDE_MIN, AMPLITUDE_MAX);

    // Calculating dominant frequency
    float df = ((f1*qPow(a1, 2))+(f2*qPow(a2, 2))+(f3*qPow(a3, 2))) /(qPow(a1, 2)+qPow(a2, 2)+qPow(a3, 2));

    return df;
}
