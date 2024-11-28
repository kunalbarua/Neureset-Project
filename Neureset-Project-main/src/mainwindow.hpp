#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QRandomGenerator>
#include <QDateTime>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QIcon>
#include <QSize>
#include <QPixmap>
#include <QPlainTextEdit>
#include <QProgressBar>
#include<QLineEdit>
#include <QMenuBar>

class Neureset;

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        void hideMenuList();
        void showMenuList();
        void updateMenu();
        void updateBatteryIcon(int);
        void updateDateTime(QString, QString);

        QWidget neuresetWidget;
        QPushButton powerButton;
        QPushButton startButton;
        QPushButton pauseButton;
        QPushButton stopButton;
        QPushButton uploadButton;
        QLabel batteryIndicator;
        QLabel blueLight;
        QLabel greenLight;
        QLabel redLight;
        QWidget menuWidget;
        QListWidget menuList;
        QListWidget selectedMenuList;
        QPushButton menuButton;
        QPlainTextEdit textDisp;
        QProgressBar progressBar;
        QPlainTextEdit timerDisp;
        QLineEdit date;
        QLineEdit time;
        QPushButton saveDateTimeBtn;
        QLabel screenOff;
        QMenuBar menu;
        QMenu waveformMenu;
        QMenu deviceMenu;
        QAction* alphaAction;
        QAction* betaAction;
        QAction* deltaAction;
        QAction* thetaAction;
        QAction* resetBatteryAction;
        QAction* toggleHeadsetAction;

    public slots:
        void updateProgressbar(int progress);
        void updateTimerDisp(QString);
        void updateDisp(QString);

    signals:
        void shutdown();

    private:
        void closeEvent(QCloseEvent*) override;

};

#endif
