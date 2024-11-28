#ifndef NEURESET_HPP
#define NEURESET_HPP

#define ANALYSIS_TIME 5
#define ROUND_TIME 1

#include "headset.hpp"
#include "sessionmanager.hpp"
#include "mainwindow.hpp"
#include "PC.hpp"

#include <QtConcurrent/QtConcurrentRun>
#include <QThread>
#include <QMutex>
#include <QObject>
#include <QDateTime>
#include <QDebug>
#include <QVector>
#include <QString>

#define BATTERY_DRAIN 30

class MainWindow;

class Neureset : public QObject {
    Q_OBJECT

    public:
        Neureset(MainWindow&, SessionManager&);
        void startTherapy();
        bool startRound(double);
        void connectionLost();
        void powerOff();
        void powerOn();
        void disableButtons();
        void enableButtons();

    private slots:
        void powerButtonHandler();
        void startButtonHandler();
        void pauseButtonHandler();
        void stopButtonHandler();
        void uploadButtonHandler();
        void menuButtonHandler();
        void connectHeadsetHandler();
        void updateDateTime();
        void saveDateTime();
        void menuListHandler();
        void changeWave();
        void resetBattery();

    private:
        bool batteryDrain(int);
        bool needToExit();
        void hangIfPaused();
        Headset headset;
        MainWindow& mainWindow;
        SessionManager& sessionManager;
        QDateTime dateTime;
        QMutex pauseMutex;
        QMutex isTherapyMutex;
        bool isTherapy;
        bool isPowered;
        bool isSessionReady;
        int battery;
        int waveType;

    signals:
        void updateProgressBar(int);
        void updateTimerDisp(QString);
        void updateDisp(QString);

};

#endif
