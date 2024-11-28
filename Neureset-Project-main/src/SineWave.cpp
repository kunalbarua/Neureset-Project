#include "SineWave.hpp"

#include <cmath>
#include <QWidget>
#include <QPainter> // Include QPainter for painting operations in the widget.
#include <QPainterPath> // Include QPainterPath for creating complex shapes.
#include <QVector> // Include QVector for using dynamic arrays.
#include <QPointF> // Include QPointF for points in the 2D space.

// Constructor for the SineWave widget that takes two frequencies and a parent widget.
SineWave::SineWave(double freq1, double freq2, QWidget *parent) :
    QWidget(parent), // Initialize the base QWidget class with the provided parent.
    frequency1(freq1), // Set the first frequency to the provided freq1.
    frequency2(freq2) // Set the second frequency to the provided freq2.
{
}

// Function to generate sine wave data points.
QVector<QPointF> SineWave::generateSineWaveData(double frequency, int samples, double amplitude) {
    QVector<QPointF> data; // Create a QVector to store data points of the sine wave.
    double sampleRate = 4410.0; // Define the sample rate for the wave.
    double angularFrequency = 2 * M_PI * frequency; // Calculate the angular frequency.

    for (int i = 0; i < samples; ++i) { // Loop through each sample.
        double t = i / sampleRate; // Calculate the time for the current sample.
        double y = amplitude * std::sin(angularFrequency * t); // Calculate the sine value for the current sample.
        data.append(QPointF(t, y)); // Add the calculated point to the data vector.
    }

    return data; // Return the generated data points.
}

// Paint event to draw the sine wave when the widget needs to be painted.
void SineWave::paintEvent(QPaintEvent* event) {
    QPainter painter(this); // Create a QPainter that will paint on this widget.
    painter.setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smoother lines.

    // Common amplitude and sample size for both sine waves.
    double amplitude = 1.0; // Set the amplitude for the wave.
    int samples = 10000; // Set the number of samples to generate for the wave.

    double wavelength = 3; // Define the wavelength for the sine waves.

    // Set up the pen for drawing the first sine wave and draw it.
    painter.setPen(Qt::blue); // Set the pen color to blue for drawing the first sine wave.
    QVector<QPointF> sineWave1 = generateSineWaveData(frequency1, samples, amplitude); // Generate the sine wave data for frequency1.
    drawSineWave(painter, sineWave1, amplitude, wavelength); // Call the drawSineWave function to draw the first sine wave.

    // Set up the pen for drawing the second sine wave and draw it.
    painter.setPen(Qt::red); // Set the pen color to red for drawing the second sine wave.
    QVector<QPointF> sineWave2 = generateSineWaveData(frequency2, samples, amplitude); // Generate the sine wave data for frequency2.
    drawSineWave(painter, sineWave2, amplitude, wavelength); // Call the drawSineWave function to draw the second sine wave.
}

// Helper function to draw a sine wave given the painter, wave data, amplitude, and wavelength.
void SineWave::drawSineWave(QPainter &painter, const QVector<QPointF> &sineWave, double amplitude, double wavelength) {
    QPainterPath path; // Create a QPainterPath object to describe the shape of the sine wave.

    if (!sineWave.isEmpty()) { // Check if the sine wave data is not empty.
        // Start the path at the first point of the sine wave, scaling it to fit the widget.
        path.moveTo(sineWave.first().x() * wavelength * width(), sineWave.first().y() * amplitude * 50 + height() / 2);

        for (const QPointF &point : sineWave) { // Iterate over each point in the sine wave data.
            // Calculate the scaled position of each point.
            double x = point.x() * wavelength * width(); // Scale the x-coordinate to the widget's width.
            double y = point.y() * amplitude * 50 + height() / 2; // Scale the y-coordinate based on amplitude and center it vertically.
            path.lineTo(x, y); // Add a line to the path to the next point.
        }
    }

    painter.drawPath(path); // Draw the path on the widget using the QPainter object.

    // Draw axis labels.
    QFont font = painter.font(); // Get the current font from the painter.
    font.setPointSize(10); // Set the font size to 10 points.
    painter.setFont(font); // Set the modified font back to the painter.

    // Draw the label for the x-axis with the second frequency.
    painter.drawText(rect().adjusted(5, 0, -5, -5), Qt::AlignRight | Qt::AlignBottom, tr("After frequency: %2       → Time (s)").arg(frequency2));

    // Draw the label for the y-axis with the first frequency.
    painter.setPen(Qt::blue); // Set the pen color to blue.
    painter.drawText(rect().adjusted(5, 5, -5, -5), Qt::AlignLeft | Qt::AlignTop, tr("Before frequency: %1    ↑ Amplitude").arg(frequency1));
}
