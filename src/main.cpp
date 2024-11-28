#include "mainwindow.hpp"
#include "filemanager.hpp"
#include "sessionmanager.hpp"
#include "waveformgenerator.hpp"
#include "neureset.hpp"

#include <QVector>
#include <QApplication>

void waveformTest();
void fileManagerTest();
void sessionManagerTestAdd(SessionManager*);
void sessionManagerTest(SessionManager*);

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    SessionManager sessionManager;
    Neureset neureset(mainWindow, sessionManager);
    mainWindow.show();
    return a.exec();
}

void fileManagerTest() {
    QVector<QVector<QString>>* input = new QVector<QVector<QString>>;
    QVector<QVector<QString>>* data = new QVector<QVector<QString>>;
    QVector<QString>* data1 = new QVector<QString>;

    data1->append("1235423");
    data1->append("2024-04-04");
    data1->append("7:37AM");
    data1->append("2.2");
    data1->append("2.3");
    data1->append("2.4");
    data1->append("2.5");

    data->append(*data1);
    data->append(*data1);

    FileManager* fileManager = new FileManager();
    fileManager->saveFile("test.txt", data);
    fileManager->loadFile("test.txt", input);

    for(auto &vector : *input){
        for(auto &element : vector){
            qInfo() << element;
        }
    }

    delete data;
    delete input;
}

void sessionManagerTestAdd(SessionManager* sessionManager) {
    QVector<QString> data1;

    data1.append("1444422");
    data1.append("2024-04-03");
    data1.append("7:37AM");
    data1.append("5.2");
    data1.append("2.3");
    data1.append("5.4");
    data1.append("9.9");

    sessionManager->writeToBuffer(&data1);

}

void sessionManagerTest(SessionManager* sessionManager) {
    qInfo("Testing overview");
    for(auto &vector : *sessionManager->getLogOverview()){
        qInfo("Vector:");
        for(auto &element : vector){
            qInfo() << element;
        }
    }

    qInfo("Testing log details");
    QVector<QString>* logDetails = sessionManager->getLogDetails(1);
    for(auto &element : *logDetails){
        qInfo() << element;
    }

    sessionManager->saveBufferToDisk();
}
