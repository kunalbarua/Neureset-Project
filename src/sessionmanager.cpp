#include "sessionmanager.hpp"

// Constructor
SessionManager::SessionManager() {
    fileManager = new FileManager();
    buffer = new QVector<QVector<QString>>;
    this->loadBufferFromDisk();
}

// Deconstructor
SessionManager::~SessionManager() {
    delete fileManager;
    delete buffer;
}

QVector<QVector<QString>>* SessionManager::getLogOverview() {
    return buffer;
}

QVector<QString>* SessionManager::getLogDetails(int index) {
    // checking bounds
    if(index >= buffer->length()){
        qInfo("Out of bounds");
        return nullptr;
    }

    return &(*buffer)[index];
}

QString* SessionManager::getDate(int vectorIndex) {
    // checking bounds
    if(vectorIndex >= buffer->length()){
        qInfo("%d is out of bounds, buffer vector length is %d", vectorIndex, buffer->length());
        return nullptr;
    }
    // index 0 is the date value
    return &(*buffer)[vectorIndex][0];
}

QString* SessionManager::getTime(int vectorIndex) {
    // checking bounds
    if(vectorIndex >= buffer->length()){
        qInfo("%d is out of bounds, buffer vector length is %d", vectorIndex, buffer->length());
        return nullptr;
    }
    // index 1 is the time value
    return &(*buffer)[vectorIndex][1];
}

QString* SessionManager::getElement(int vectorIndex, int elementIndex) {
    //checking bounds
    if(vectorIndex >= buffer->length()){
        qInfo("%d is out of bounds, buffer vector length is %d", vectorIndex, buffer->length());
        return nullptr;
    }
    if(elementIndex >= (*buffer)[vectorIndex].length()){
        qInfo("%d is out of bounds, session vector length is %d", elementIndex, (*buffer)[vectorIndex].length());
        return nullptr;
    }

    // returning element
    return &(*buffer)[vectorIndex][elementIndex];
}

void SessionManager::getEEGSiteReadings(int vectorIndex, int siteNumber, QVector<QString>* vector)
{
    // reading values from buffer
    QString reading1 = *getElement(vectorIndex, siteNumber+1);
    QString reading2 = *getElement(vectorIndex, siteNumber+22);

    //checking values
    if(reading1 == nullptr || reading2 == nullptr){
        qInfo("Failed to get EEG site data for site %d", siteNumber);
        return;
    }

    // adding values to passed in vector
    vector->append(reading1);
    vector->append(reading2);
}

void SessionManager::writeToBuffer(QVector<QString>* sessionData) {
    buffer->append(*sessionData);
}

void SessionManager::saveBufferToDisk() {
    fileManager->saveFile(FILENAME, buffer);
}

void SessionManager::loadBufferFromDisk() {
    fileManager->loadFile(FILENAME, buffer);
}
