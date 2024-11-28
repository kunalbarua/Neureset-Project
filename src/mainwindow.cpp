#include "mainwindow.hpp"

// MainWindow Constructor
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    neuresetWidget(this),
    powerButton(&neuresetWidget),
    startButton(&neuresetWidget),
    pauseButton(&neuresetWidget),
    stopButton(&neuresetWidget),
    uploadButton(&neuresetWidget),
    batteryIndicator(&neuresetWidget),
    blueLight(&neuresetWidget),
    greenLight(&neuresetWidget),
    redLight(&neuresetWidget),
    menuWidget(&neuresetWidget),
    menuList(&menuWidget),
    selectedMenuList(&menuWidget),
    menuButton(&neuresetWidget),
    textDisp(&neuresetWidget),
    progressBar(&neuresetWidget),
    timerDisp(&neuresetWidget),
    date(&neuresetWidget),
    time(&neuresetWidget),
    saveDateTimeBtn(&neuresetWidget),
    screenOff(&neuresetWidget),
    menu(&neuresetWidget),
    waveformMenu("&Waveform"),
    deviceMenu("&Device")
{

    // Neureset widget properties
    neuresetWidget.setGeometry(50, 50, 500, 500);
    neuresetWidget.setStyleSheet("QWidget#neuresetWidget { border: 3px solid black; background-color: silver; }");
    neuresetWidget.setObjectName("neuresetWidget");

    // Neureset buttons
    powerButton.setGeometry(450, 10, 40, 40);
    powerButton.setIcon(QIcon("/usr/share/icons/LoginIcons/apps/48/system-shutdown.svg"));
    powerButton.setIconSize(QSize(32, 32));
    powerButton.setStyleSheet("border: none; background-color: none;");
    pauseButton.setGeometry(165, 400, 50, 50);
    pauseButton.setIcon(QIcon("/usr/share/icons/Adwaita/32x32/actions/media-playback-pause-symbolic.symbolic.png"));
    pauseButton.setIconSize(QSize(32, 32));
    startButton.setGeometry(225, 400, 50, 50);
    startButton.setIcon(QIcon("/usr/share/icons/Adwaita/32x32/actions/media-playback-start-symbolic.symbolic.png"));
    startButton.setIconSize(QSize(32, 32));
    stopButton.setGeometry(285, 400, 50, 50);
    stopButton.setIcon(QIcon("/usr/share/icons/Adwaita/32x32/actions/media-playback-stop-symbolic.symbolic.png"));
    stopButton.setIconSize(QSize(32, 32));
    uploadButton.setGeometry(10, 450, 40, 40);
    uploadButton.setIcon(QIcon("/usr/share/icons/Adwaita/32x32/actions/document-send-symbolic.symbolic.png"));
    uploadButton.setIconSize(QSize(32, 32));

    // Battery indicator and lights
    batteryIndicator.setGeometry(467, 465, 24, 24);
    batteryIndicator.setPixmap(QPixmap("/usr/share/icons/Adwaita/24x24/legacy/battery-full-symbolic.symbolic.png"));
    blueLight.setGeometry(20, 20, 15, 20);
    this->setStyleSheet("QLabel#lightLabel { border: 1px solid black; }");
    blueLight.setStyleSheet("background-color: darkblue;");
    blueLight.setObjectName("lightLabel");
    greenLight.setGeometry(45, 20, 15, 20);
    greenLight.setStyleSheet("background-color: darkgreen;");
    greenLight.setObjectName("lightLabel");
    redLight.setGeometry(70, 20, 15, 20);
    redLight.setStyleSheet("background-color: darkred;");
    redLight.setObjectName("lightLabel");

    // Menu widget properties and components
    menuWidget.setGeometry(100, 100, 300, 250);
    menuWidget.setStyleSheet("QWidget#menuWidget { border: 2px solid black; background-color: gray; }");
    menuWidget.setObjectName("menuWidget");
    menuButton.setGeometry(110, 65, 30, 30);
    menuButton.setIcon(QIcon("/usr/share/icons/Adwaita/32x32/actions/format-justify-fill-symbolic.symbolic.png"));
    menuList.setGeometry(20, 20, 260, 210);
    menuList.addItem("NEW SESSION");
    menuList.addItem("SESSION LOG");
    menuList.addItem("TIME AND DATE");
    selectedMenuList.setGeometry(20, 20, 260, 210);
    selectedMenuList.hide();
    textDisp.hide();
    textDisp.setGeometry(120, 120, 260, 210);
    textDisp.setReadOnly(true);

    // init progress bar
    progressBar.setOrientation(Qt::Horizontal);
    progressBar.setRange(0,100);
    progressBar.setGeometry(170,275,150,25);
    progressBar.setValue(0);
    progressBar.hide();

    // init dateTime widgets
    date.hide();
    date.setGeometry(170,175,150,25);
    time.hide();
    time.setGeometry(170,200,150,25);
    saveDateTimeBtn.hide();
    saveDateTimeBtn.setGeometry(170,225,150,25);
    saveDateTimeBtn.setText("Save");

    // menubar properties
    alphaAction = waveformMenu.addAction("Alpha");
    betaAction = waveformMenu.addAction("Beta");
    deltaAction = waveformMenu.addAction("Delta");
    thetaAction = waveformMenu.addAction("Theta");

    resetBatteryAction = deviceMenu.addAction("Recharge Battery");
    toggleHeadsetAction = deviceMenu.addAction("Toggle headset connection");

    menuBar()->addMenu(&deviceMenu);
    menuBar()->addMenu(&waveformMenu);


    // init "off" screen properties
    screenOff.setGeometry(120, 120, 260, 210);
    screenOff.setStyleSheet("background-color: gray;");

    // init timer widget
    timerDisp.hide();
    timerDisp.setGeometry(170,175,150,30);
    timerDisp.setReadOnly(true);

    // Setting window's properties
    this->setFixedSize(600, 600);
    this->setWindowTitle("Neureset Simulation");
}

void MainWindow::updateDisp(QString msg) {
    textDisp.show();
    textDisp.clear();
    textDisp.appendPlainText(msg);
}

void MainWindow::updateDateTime(QString dateString, QString timeString){
    menuList.hide();
    date.show();
    date.setText(dateString);
    time.show();
    time.setText(timeString);
    saveDateTimeBtn.show();
}

void MainWindow::updateTimerDisp(QString str) {
    timerDisp.clear();
    timerDisp.appendPlainText(str);
}

void MainWindow::updateProgressbar(int progress)
{
    if (progress < 0 || progress > 100){
        qInfo("Progress value is out of bounds");
        return;
    }
    progressBar.setValue(progress);
}

void MainWindow::updateBatteryIcon(int batteryLevel)
{
    // determine battery state
    int status = batteryLevel / 33;

    // set battery icon
    if(status == 0)
        batteryIndicator.setPixmap(QPixmap("/usr/share/icons/Adwaita/24x24/legacy/battery-empty-symbolic.symbolic.png"));
    else if(status == 1)
        batteryIndicator.setPixmap(QPixmap("/usr/share/icons/Adwaita/24x24/legacy/battery-good-symbolic.symbolic.png"));
    else
        batteryIndicator.setPixmap(QPixmap("/usr/share/icons/Adwaita/24x24/legacy/battery-full-symbolic.symbolic.png"));
}

void MainWindow::hideMenuList(){
    selectedMenuList.show();
}

void MainWindow::showMenuList(){
    menuList.show();
    date.hide();
    time.hide();
    progressBar.hide();
    saveDateTimeBtn.hide();
    selectedMenuList.clear();
    selectedMenuList.hide();
    timerDisp.hide();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    emit shutdown();
    event->accept();
}
