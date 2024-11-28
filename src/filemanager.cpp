#include "filemanager.hpp"

void FileManager::saveFile(QString filename, QVector<QVector<QString>>* data) {
    // creating file object
    QFile file(filename);

    // opens file and write mode, writes vector contents to file
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        for(auto &vector : *data){
            for(auto & element : vector){
                stream << element << ',';
            }
            stream << "\n";
        }
    }
    file.close();
}

void FileManager::loadFile(QString filename, QVector<QVector<QString>>* buffer) {
    // creating file object
    QFile file(filename);

    // checking if file exists
    if(!file.exists()){
        qInfo("File does not exist.");
        return;
    }

    // opening file in read mode, loads content from file into passed in vector
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        while(!stream.atEnd()){
            QVector<QString> data;
            QString line = stream.readLine();

            // if line is empty, skip
            if(line == "" || line == "\n" || line == "\r" || line == "\r\n")
                continue;

            QStringList list = line.split(",");
            for(int i=0; i<list.length(); i++){
                if(list[i] != "")
                    data.append(list[i]);
            }
            buffer->append(data);
        }
        file.close();
    }
}
