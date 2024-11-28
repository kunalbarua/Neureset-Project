#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>

/* Purpose: Writes vector data to files, loads vectors with data read from files
 * Variables:
 *
 * Functions:
 *      void saveFile(QString, QVector<QVector<QString>>*) : saves data from vector into file
 *      void loadFile(QString, QVector<QVector<QString>>*) : reads file and loads data into given vector
 *
 */

class FileManager {

    public:
        void saveFile(QString, QVector<QVector<QString>>*);
        void loadFile(QString, QVector<QVector<QString>>*);

};

#endif
