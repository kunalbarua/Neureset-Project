#ifndef SINEWAVE_HPP
#define SINEWAVE_HPP

#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPointF>

class SineWave: public QWidget {
    Q_OBJECT

    public:
        SineWave(double freq1, double freq2, QWidget* parent);

    protected:
        void paintEvent(QPaintEvent *event) override;
        QVector<QPointF> generateSineWaveData(double frequency, int samples, double amplitude = 1.0);
        void drawSineWave(QPainter &painter, const QVector<QPointF> &sineWave, double amplitude, double wavelength);

    private:
        double frequency1;
        double frequency2;
};

#endif