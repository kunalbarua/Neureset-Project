#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

#include "filemanager.hpp"

#include <QString>
#include <QHash>
#include <QVector>

#define FILENAME "data.txt"

/* Purpose: Handles session log data for the Neureset, handles other session log related tasks
 * Variables:
 *       FileManager* fileManager : Pointer to FileManager instance that handles loading buffer data from disk and writing the buffer data to disk
 *       QVector<QVector<QString>>* buffer : Vector of Vectors, used to store session data
 *
 * Functions:
 *      QVector<QVector<QString>>* getLogOverview() : returns a pointer to the buffer vector
 *      QVector<QString>* getLogDetails(int) : returns pointer to session vector for a given index
 *      QString* getDate(int) : returns the date value from a session for a given index
 *      QString* getTime(int) : returns the time value from a session for a given index
 *      QString* getElement(int, int) : returns a value from a session pointer for a given session index and element index
 *      void getEEGSiteReadings(int, int, QVector<QString>*) : populates a QVector<QString> vector with data from a given session and EEG site number
 *      void writeToBuffer(QVector<QString>*) : adds a session vector to the buffer
 *      void saveBufferToDisk() : saves the buffer contents to disk
 *
 */

class SessionManager {

    public:
        SessionManager();
        ~SessionManager();
        QVector<QVector<QString>>* getLogOverview();
        QVector<QString>* getLogDetails(int);
        QString* getDate(int);
        QString* getTime(int);
        QString* getElement(int, int);
        void getEEGSiteReadings(int, int, QVector<QString>*);
        void writeToBuffer(QVector<QString>*);
        void saveBufferToDisk();

    private:
        FileManager* fileManager;
        QVector<QVector<QString>>* buffer;

        void loadBufferFromDisk();

};

#endif
