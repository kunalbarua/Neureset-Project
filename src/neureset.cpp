#include "neureset.hpp"

// Neureset Constructor
Neureset::Neureset(MainWindow& mainWindow, SessionManager& sessionManager) :
    mainWindow(mainWindow),
    sessionManager(sessionManager),
    isTherapy(false),
    isPowered(false),
    isSessionReady(false),
    battery(100),
    waveType(ALPHA_WAVE)
{

    // init date time
    dateTime.setDate(QDate::currentDate());
    dateTime.setTime(QTime::currentTime());

    // Connecting signals and slots
    connect(&mainWindow.startButton, &QPushButton::clicked, this, &Neureset::startButtonHandler);
    connect(&mainWindow.pauseButton, &QPushButton::clicked, this, &Neureset::pauseButtonHandler);
    connect(&mainWindow.stopButton, &QPushButton::clicked, this, &Neureset::stopButtonHandler);
    connect(&mainWindow.saveDateTimeBtn, &QPushButton::clicked, this, &Neureset::saveDateTime);
    connect(&mainWindow.uploadButton, &QPushButton::clicked, this, &Neureset::uploadButtonHandler);
    connect(&mainWindow.menuButton, &QPushButton::clicked, this, &Neureset::menuButtonHandler);
    connect(&mainWindow.menuList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(menuListHandler()));
    connect(&mainWindow.powerButton, &QPushButton::clicked, this, &Neureset::powerButtonHandler);
    connect(this, &Neureset::updateProgressBar, &mainWindow, &MainWindow::updateProgressbar);
    connect(this, &Neureset::updateDisp, &mainWindow, &MainWindow::updateDisp);
    connect(this, &Neureset::updateTimerDisp, &mainWindow, &MainWindow::updateTimerDisp);
    connect(mainWindow.alphaAction, &QAction::triggered, this, &Neureset::changeWave);
    connect(mainWindow.betaAction, &QAction::triggered, this, &Neureset::changeWave);
    connect(mainWindow.deltaAction, &QAction::triggered, this, &Neureset::changeWave);
    connect(mainWindow.thetaAction, &QAction::triggered, this, &Neureset::changeWave);
    connect(mainWindow.resetBatteryAction, &QAction::triggered, this, &Neureset::resetBattery);
    connect(mainWindow.toggleHeadsetAction, &QAction::triggered, this, &Neureset::connectHeadsetHandler);
    connect(&mainWindow, &MainWindow::shutdown, this, &Neureset::stopButtonHandler);

    // Device needs to be off upon starting
    powerOff();
}

// Method to start therapy sequence
void Neureset::startTherapy() {

    mainWindow.startButton.setEnabled(false);

    // Int to keep track of therapy's progress
    int progress = 0;

    // Starting timer loop on new thread
    QtConcurrent::run([this]() {
        // Calculating session's estimate time
        int estTime = (4 * (ANALYSIS_TIME + ROUND_TIME)) + ANALYSIS_TIME - 3;

        // Updating timer one second at a time
        while (estTime >= 0) {
            emit updateTimerDisp(QString::number(estTime));
            QThread::sleep(1);
            estTime -= 1;
            hangIfPaused();
            if (needToExit()) {
                emit updateTimerDisp(QString::number(0));
                break;
            }
        }
    });

    qInfo() << "LOG:  Starting Therapy";

    // QVector holding the current session's log information
    QVector<QString> currSession;

    // Get the current date and time
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Convert date and time to strings
    QString currentDate = currentDateTime.toString("yyyy-MM-dd");
    QString currentTime = currentDateTime.toString("hh:mmAP");

    // Append date and time strings to the session's log
    currSession.append(currentDate);
    currSession.append(currentTime);

    qInfo() << "LOG:  Getting baseline frequencies of probes";
    QString analysis = "";

    // Updating progress bar
    progress += 5;
    emit updateProgressBar(progress);

    // Measuring the pre-treatment waveforms
    for (Probe& probe : headset.getProbes()) {
        probe.measureWaveform(waveType);
        currSession.append(QString::number(probe.getWaveform()));
        analysis.append(QString::number(probe.getWaveform()) + ",");
    } 

    // Pausing thread to simulate baselines before analysis
    hangIfPaused();
    if (needToExit()) return;
    QThread::sleep(ANALYSIS_TIME);
    hangIfPaused();
    if (needToExit()) return;

    // Updating progress bar
    progress += 10;
    emit updateProgressBar(progress);

    // Printing the baseline frequencies of all probes
    qInfo() << "LOG:  Pre-treatment baseline frequencies: " << analysis;

    // Start first round of treatment with offset 5hz
    if (startRound(5)) return;

    // Updating progress bar
    progress += 5;
    emit updateProgressBar(progress);

    // Loop for treatment rounds, starts with doing analysis of frequencies
    // Initating five rounds of treatment using offsets 10, 15, 20
    for (int offset = 10; offset <= 20; offset += 5) {

        QString analysis = "";

        for (Probe& probe : headset.getProbes()) {
             analysis.append(QString::number(probe.getWaveform()) + ",");
        }

        qInfo() << "LOG:  Starting round with " << offset << "Hz offset";
        qInfo() << "LOG:  Analysis for current round: " << analysis;

        // Pausing thread to simulate pre-round analysis
        hangIfPaused();
        if (needToExit()) return;
        QThread::sleep(ANALYSIS_TIME/2);
        if (needToExit()) return;
        hangIfPaused();

        // Updating progress bar
        progress += 10;
        emit updateProgressBar(progress);

        // Pausing thread to simulate pre-round analysis
        hangIfPaused();
        if (needToExit()) return;
        QThread::sleep(ANALYSIS_TIME/2);
        hangIfPaused();
        if (needToExit()) return;

        if (startRound(offset)) return;

        // Updating progress bar
        progress += 10;
        emit updateProgressBar(progress);
    }

    // Measuring the post-treatment waveforms
    for (Probe& probe : headset.getProbes()) {
        currSession.append(QString::number(qRound(probe.getWaveform())));
    }
    
    // Updating progress bar
    progress += 10;
    emit updateProgressBar(progress);

    // Pausing thread to simulate baseline after analysis
    hangIfPaused();
    if (needToExit()) return;
    QThread::sleep(ANALYSIS_TIME);
    hangIfPaused();
    if (needToExit()) return;

    // Updating progress bar
    progress += 10;
    emit updateProgressBar(progress);

    // Saving session to session log on disk
    sessionManager.writeToBuffer(&currSession);
    sessionManager.saveBufferToDisk();

    // Locking isTherapy's mutex
    isTherapyMutex.lock();

    // Setting isTherapy to false
    isTherapy = false;
    isSessionReady = false;

    // Unlocking isTherapy's mutex
    isTherapyMutex.unlock();

    qInfo() << "LOG:  Finished Therapy";

    mainWindow.startButton.setEnabled(true);
}

// Method to start a round of treatment
bool Neureset::startRound(double offset) {
    // Make light flash green
    mainWindow.greenLight.setStyleSheet("background-color: lime;");
    qInfo() << "LOG:  Administering treatment";

    // Sending feedback offset 16 times in one second
    for (int i = 0; i < 16; i++) {

        // Applying feedback to all probes
        for (Probe& probe : headset.getProbes()) {
            probe.applyFeedBack(offset);
        }
    }

    // Pausing thread to simulate running round
    hangIfPaused();
    if (needToExit()) return true;
    QThread::sleep(ROUND_TIME);
    hangIfPaused();
    if (needToExit()) return true;

    // light goes back to "off" mode
    mainWindow.greenLight.setStyleSheet("background-color: darkgreen;");

    return false;
}

// Method to handle the loss of connection with headset
void Neureset::connectionLost() {
    mainWindow.redLight.setStyleSheet("background-color: red;");
    mainWindow.updateDisp("Connection lost with headset! Please reconnect before proceeding.");

    isTherapyMutex.lock();
    if (isTherapy) pauseMutex.tryLock();
    isTherapyMutex.unlock();
}

// Method to turn off the device
void Neureset::powerOff() {
    mainWindow.screenOff.show();
    stopButtonHandler();
    disableButtons();
    mainWindow.blueLight.setStyleSheet("background-color: darkblue;");
    mainWindow.redLight.setStyleSheet("background-color: darkred;");
}

// Method to turn on the device
void Neureset::powerOn() {
    mainWindow.screenOff.hide();
    enableButtons();
}

// Method to disable all buttons
void Neureset::disableButtons() {
    mainWindow.startButton.setEnabled(false);
    mainWindow.pauseButton.setEnabled(false);
    mainWindow.stopButton.setEnabled(false);
    mainWindow.uploadButton.setEnabled(false);
    mainWindow.menuButton.setEnabled(false);
}

// Method to enable all buttons
void Neureset::enableButtons() {
    mainWindow.startButton.setEnabled(true);
    mainWindow.pauseButton.setEnabled(true);
    mainWindow.stopButton.setEnabled(true);
    mainWindow.uploadButton.setEnabled(true);
    mainWindow.menuButton.setEnabled(true);
}

// Power Button Handler
void Neureset::powerButtonHandler() {
    if (isPowered) {
        isPowered = false;
        powerOff();
        qInfo() << "LOG:  Device powered off";
    } else {
        isPowered = true;
        powerOn();
        qInfo() << "LOG:  Device powered on";
    }
}

// Start Button Handler
void Neureset::startButtonHandler() {
    if (!headset.isConnected() || !isSessionReady) return;

    // Locking isTherapy's mutex
    isTherapyMutex.lock();

    // Making sure there isn't already a therapy running
    if (!isTherapy) {

        // Checking if we have enough battery to start therapy
        if(!batteryDrain(BATTERY_DRAIN)) {
            qInfo("LOG:  Battery low, unable to start therapy");
            emit updateDisp("Battery low, unable to start therapy");
            isTherapyMutex.unlock();
            return;
        }

        // Set isTherapy to true
        isTherapy = true;
      
        // Hiding base menu
        mainWindow.hideMenuList();

        // Making sure pause therapy mutex is unlocked
        pauseMutex.unlock();

        // Running startTherapy in its own thread
        QtConcurrent::run(this, &Neureset::startTherapy);

    } else {

        // Unpausing thread if it is currently locked
        if (!pauseMutex.tryLock()) {
            qInfo() << "LOG:  Therapy resumed";
            mainWindow.textDisp.hide();
            mainWindow.timerDisp.setStyleSheet("color: black");
            mainWindow.pauseButton.setEnabled(true);
            mainWindow.startButton.setEnabled(false);
        }
        pauseMutex.unlock();
    }

    // Unlocking isTherapy's mutex
    isTherapyMutex.unlock();
}

// Pause Button Handler
void Neureset::pauseButtonHandler() {
    // Locking isTherapy's mutex
    isTherapyMutex.lock();

    // Checking if there is a therapy and if its not paused
    if (isTherapy && pauseMutex.tryLock()) {
        qInfo() << "LOG:  Therapy paused";
        mainWindow.textDisp.show();
        mainWindow.timerDisp.setStyleSheet("color: red");
        mainWindow.updateDisp("The session is currently paused.");
        mainWindow.pauseButton.setEnabled(false);
        mainWindow.startButton.setEnabled(true);
    } 

    // Unlocking isTherapy's mutex
    isTherapyMutex.unlock();
}

// Stop Button Handler
void Neureset::stopButtonHandler() {

    // Locking isTherapy's mutex
    isTherapyMutex.lock();

    // Checking if  there is a therapy to stop
    if (isTherapy) {

        // Stopping therapy
        isTherapy = false;
        isTherapyMutex.unlock();
        qInfo() << "LOG:  Ending therapy";

        // Resetting menu
        menuButtonHandler();
        mainWindow.startButton.setEnabled(true);
        mainWindow.greenLight.setStyleSheet("background-color: darkgreen;");
    
    } else {
        isTherapyMutex.unlock();
    }
}

// Upload Button Handler
void Neureset::uploadButtonHandler() {
    PC* pc = new PC(&mainWindow, sessionManager);
    pc->setAttribute(Qt::WA_DeleteOnClose);
    pc->show();
}

// Menu Button Handler
void Neureset::menuButtonHandler() {

    // Getting the isTherapy's mutex lock
    isTherapyMutex.lock();

    // Making sure we aren't in a therapy session
    if (isTherapy) {
        isTherapyMutex.unlock();
        return;
    }

    // Unlocking the isTherapy's mutex lock
    isTherapyMutex.unlock();

    mainWindow.showMenuList();
    emit updateProgressBar(0);
    isSessionReady = false;
}

// Connect Headset Button Handler
void Neureset::connectHeadsetHandler() {
    if (headset.isConnected()) {
        headset.disconnect();
        mainWindow.blueLight.setStyleSheet("background-color: darkblue;");
        connectionLost();
    } else {
        headset.connect();
        mainWindow.blueLight.setStyleSheet("background-color: deepskyblue;");
        mainWindow.redLight.setStyleSheet("background-color: darkred;");
        mainWindow.textDisp.hide();

        isTherapyMutex.lock();
        if (isTherapy) {
            pauseMutex.unlock();
        }
        isTherapyMutex.unlock();
    }
}

//Connect menu list handler
void Neureset::menuListHandler(){
    QListWidgetItem *selectedItem = mainWindow.menuList.currentItem();

       if(selectedItem == mainWindow.menuList.item(0)){
           mainWindow.hideMenuList();
           mainWindow.timerDisp.show();
           mainWindow.updateTimerDisp(QString("ETA Unavailable"));
           mainWindow.progressBar.show();
           isSessionReady = true;
       }
       else if (selectedItem == mainWindow.menuList.item(1)){
           mainWindow.hideMenuList();
           mainWindow.selectedMenuList.clear();

           // Populate the list widget with data
           int a = 0;
           for(auto &element : *sessionManager.getLogOverview()){

               QString date_time = *sessionManager.getDate(a) + " " + *sessionManager.getTime(a);
               ++a;
               mainWindow.selectedMenuList.addItem(QString("Session %1   %2").arg(a).arg(date_time));

           }
       }
       else if (selectedItem == mainWindow.menuList.item(2)){
           updateDateTime();
       }
}

bool Neureset::batteryDrain(int drainAmount) {
    if (drainAmount > battery) {
        return false;
    }
    battery -= drainAmount;
    mainWindow.updateBatteryIcon(battery);
    return true;
}

void Neureset::resetBattery(){
    battery = 100;
    mainWindow.updateBatteryIcon(battery);
    mainWindow.textDisp.hide();
}

void Neureset::updateDateTime() {
    mainWindow.updateDateTime(dateTime.date().toString("dd.MM.yyyy"), dateTime.time().toString("hh:mm"));

}

void Neureset::saveDateTime(){
    dateTime.setDate(QDate::fromString(mainWindow.date.text(), "dd.MM.yyyy"));
    dateTime.setTime(QTime::fromString(mainWindow.time.text(), "hh:mm"));
    menuButtonHandler();
}

void Neureset::changeWave(){
    if(mainWindow.alphaAction == sender()){
        qInfo("LOG:  Wave type set to ALPHA");
        waveType = ALPHA_WAVE;
    }
    else if(mainWindow.betaAction == sender()){
        qInfo("LOG:  Wave type set to BETA");
        waveType = BETA_WAVE;
    }
    else if(mainWindow.deltaAction == sender()){
        qInfo("LOG:  Wave type set to DELTA");
        waveType = DELTA_WAVE;
    }
    else if(mainWindow.thetaAction == sender()){
        qInfo("LOG:  Wave type set to THETA");
        waveType = THETA_WAVE;
    }
}

void Neureset::hangIfPaused() {
    if (!pauseMutex.tryLock()) {
        pauseMutex.lock();
        pauseMutex.unlock();
    } else {
        pauseMutex.unlock();
    }
}

bool Neureset::needToExit() {

    // Getting the isTherapy's mutex lock
    isTherapyMutex.lock();

    // Making copy of isTherapy
    bool isTherapyCopy = isTherapy;

    // Unlocking the isTherapy's mutex lock
    isTherapyMutex.unlock();

    // Returning whether isTherapy is false or not
    return isTherapyCopy == false;
}
