#ifndef PROBE_H
#define PROBE_H

#include "waveformgenerator.hpp"

#include <QVector>
#include <QDebug>
#include <QRandomGenerator>
#include <QDateTime>

#define ALPHA_WAVE 1
#define BETA_WAVE 2
#define DELTA_WAVE 3
#define THETA_WAVE 4


class Probe {

    public:
        Probe(int id);
        void applyFeedBack(double frequency);
        void measureWaveform(int);
        double getWaveform();

    private:
        int probeId;
        double waveform;

};

#endif
