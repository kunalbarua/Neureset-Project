#ifndef HEADSET_HPP
#define HEADSET_HPP

#define PROBE_COUNT 21

#include "probe.hpp"

#include <QVector>

class Headset {

    public:
        Headset();
        QVector<Probe>& getProbes();
        bool isConnected();
        void connect();
        void disconnect();

    private:
        QVector<Probe> probes;
        bool connected;

};

#endif
