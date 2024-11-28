#include "headset.hpp"

// Constructor
Headset::Headset() : connected(false) {
    for (int i = 0; i < PROBE_COUNT; i++) {
        probes.append(Probe(i));
    }
}

// Probes Getter
QVector<Probe>& Headset::getProbes() {
    return probes;
}

bool Headset::isConnected() {
    return connected;
}

void Headset::connect() {
    connected = true;
}

void Headset::disconnect() {
    connected = false;
}
