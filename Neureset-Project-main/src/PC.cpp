#include "PC.hpp"

// Constructor definition for the PC class, which inherits from QMainWindow
PC::PC(QWidget* parent, SessionManager& sessionManager) :
    QMainWindow(parent), // Call the QMainWindow constructor with the parent widget
    sessionListWidget(this), // Initialize the session list widget as a child of this window
    detailLabel(this), // Initialize a label for displaying session details as a child of this window
    exitButton("Exit", this), // Initialize an exit button with the label "Exit" as a child of this window
    tabWidget(this), // Initialize a tab widget as a child of this window for displaying tabs
    sessionManager(sessionManager) // Initialize the session manager reference
{
    // Populate the session list widget with data from the session manager
    int a = 0; // Counter variable for sessions
    for(auto &element : *sessionManager.getLogOverview()){ // Iterate over the log overview from the session manager
            QString date_time = *sessionManager.getDate(a) + *sessionManager.getTime(a); // Concatenate date and time for each session
            ++a; // Increment session counter
            QListWidgetItem* item = new QListWidgetItem("Session " + QString::number(a), &sessionListWidget); // Create a new list item for the session
            item->setData(Qt::UserRole, QString::number(a)); // Store session ID as user data with the list item
            item->setData(Qt::UserRole + 1, QDateTime::fromString(date_time, "yyyy-MM-dd hh:mm:ss")); // Store date and time as user data with the list item
    }

    // Set up the layout for widgets within this window
    buttonLayout.addWidget(&exitButton); // Add the exit button to the button layout
    mainLayout.addWidget(&sessionListWidget); // Add the session list widget to the main layout
    mainLayout.addWidget(&detailLabel); // Add the detail label to the main layout
    mainLayout.addWidget(&tabWidget); // Add the tab widget to the main layout. This displays the Waveform
    mainLayout.addLayout(&buttonLayout); // Add the button layout to the main layout

    // Configure the central widget of the main window
    QWidget* centralWidget = new QWidget(this); // Create a new central widget
    centralWidget->setLayout(&mainLayout); // Set the main layout to the central widget
    this->setCentralWidget(centralWidget); // Assign the central widget to this main window

    // Connect signals to their respective slots for interaction
    this->connect(&sessionListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSessionSelected())); // Connect the itemClicked signal of sessionListWidget to the onSessionSelected slot
    this->connect(&exitButton, &QPushButton::clicked, this, &MainWindow::close); // Connect the clicked signal of the exit button to the close slot of the main window

    // Further configure the main window's properties
    this->setWindowTitle("PC Window"); // Set the title of the main window
    this->resize(1200, 600); // Set the size of the main window
}

// Destructor for the PC class
PC::~PC(){
    // Clean up the items in the session list widget and any widgets in the tab widget
    for(int i = 0; i < sessionListWidget.count(); ++i) // Loop over the items in the session list widget
    {
        QListWidgetItem* item = sessionListWidget.item(i); // Get each item from the session list widget

        while(tabWidget.count()) // While there are tabs in the tab widget
            {
                delete tabWidget.widget(tabWidget.currentIndex()); // Delete the current tab widget
            }

        delete item; // Delete the list item
    }
}

// Slot for when a session is selected in the session list widget
void PC::onSessionSelected(){
    tabWidget.clear(); // Clear all tabs from the tab widget
    QListWidgetItem* selectedItem = sessionListWidget.currentItem(); // Get the currently selected item in the session list widget

    if(selectedItem) { // If an item is selected

        QString sessionId = selectedItem->data(Qt::UserRole).toString(); // Retrieve the session ID stored in the user data of the list item
        int id = sessionId.toInt() - 1; // Convert the session ID to an integer and adjust for indexing

        extractFrequency(freq1, freq2, sessionManager.getLogDetails(id)); // Call extractFrequency to fill freq1 and freq2 based on session log details

        // Create and add sine wave tabs to the tab widget
        int probe=0; // Counter for the probe number
        for(int i=0; i<21; i++){ // Loop to create tabs for each of the 21 probes

            probe = i+1; // Determine the probe number
            sineWaveWidget = new SineWave(freq1.at(i),freq2.at(i),this); // Create a new SineWaveWidget with frequencies for the probe
            sineWaveWidget->setFixedSize(1200, 200); // Set a fixed size for the SineWaveWidget

            tabWidget.addTab(sineWaveWidget, "Probe: " + QString::number(probe)); // Add the SineWaveWidget as a tab in the tab widget
            tabWidget.setCurrentIndex(i); // Set the added tab as the current tab
        }

        freq1.clear(); // Clear the frequency data for the next selection
        freq2.clear();

        displaySessionDetails(sessionId); // Display details for the selected session
    }
}

// Helper function to display session details in the detail label
void PC::displaySessionDetails(const QString &sessionId) {
    // Concatenate the date and time for the selected session
    QString date_time = *sessionManager.getDate(sessionId.toInt()-1) + " " + *sessionManager.getTime(sessionId.toInt()-1);
    detailLabel.setText(QString("Session ID: %1\nDate and Time: %2").arg(sessionId).arg(date_time)); // Set the text of the detail label with the session ID and date/time
}

// Helper function to extract frequency data from a session log detail
void PC::extractFrequency(QVector<int>& freq1, QVector<int>& freq2, QVector<QString>* LogDetails){
    QStringList fields; // List to store the individual data fields

    for(auto &element : *LogDetails){ // Loop over each detail element in the log details
        fields.append(element); // Append the element to the fields list
    }

    // Ensure there are enough data fields to extract frequencies
    if (fields.size() >= 44) {
        for (int i = 2; i < 23; ++i) { // Extract the first 21 frequency values
            freq1.append(fields[i].toInt()); // Convert to integer and append to freq1
        }
        for (int i = 23; i < 44; ++i) { // Extract the next 21 frequency values
            freq2.push_back(fields[i].toInt()); // Convert to integer and append to freq2
        }
    }
}
