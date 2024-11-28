#ifndef PC_HPP
#define PC_HPP

#include "SineWave.hpp"
#include "sessionmanager.hpp"
#include "neureset.hpp"

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>

class PC : public QMainWindow {
    Q_OBJECT

    public:
        PC(QWidget* parent, SessionManager& sessionManager);
        ~PC();
        QListWidget sessionListWidget;
        QLabel detailLabel;
        QPushButton exitButton;
        QVBoxLayout mainLayout;
        QHBoxLayout buttonLayout;
        QTabWidget tabWidget;
        SineWave* sineWaveWidget;

    private slots:
        void onSessionSelected();
        void displaySessionDetails(const QString &sessionId);
        void extractFrequency(QVector<int>& freq1, QVector<int>& freq2, QVector<QString>* getLogDetails);

    private:
        SessionManager& sessionManager;
        QVector<int> freq1;
        QVector<int> freq2;

};

#endif
