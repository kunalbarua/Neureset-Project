#ifndef WAVEFORMGENERATOR_HPP
#define WAVEFORMGENERATOR_HPP

#define ALPHA_MIN 8
#define ALPHA_MAX 13
#define BETA_MIN 12
#define BETA_MAX 31
#define DELTA_MIN 1
#define DELTA_MAX 5
#define THETA_MIN 4
#define THETA_MAX 9
#define AMPLITUDE_MIN 1
#define AMPLITUDE_MAX 11

#include <QtMath>
#include <QRandomGenerator>

/* Purpose: Provides random dominant frequiences from Alpha, Beta, Delta, and Theta bands
 * Variables:
 * Functions:
 *      static int generateAlphaWave() : Generates an Alpha Wave
 *      static int generateBetaWave() : Generates an Beta Wave
 *      static int generateDeltaWave() : Generates an Delta Wave
 *      static int generateThetaWave() : Generates an Theta Wave
 *
 */

class WaveformGenerator {

    public:
        static int generateAlphaWave();
        static int generateBetaWave();
        static int generateDeltaWave();
        static int generateThetaWave();

    private:
        static int generateWave(int min, int max);
        
};

#endif
