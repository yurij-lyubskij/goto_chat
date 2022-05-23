#include "recorder.h"
#include <QUrl>
#include <QCoreApplication>

recorder::recorder(QObject *parent)
    : QObject{parent}
{

}

void recorder::stop_recording()
{
    rec.stop();
}


QString recorder::time_duration()
{
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start);
    std::ostringstream stream;
    stream << duration.count();
    QString res = QString::fromStdString(stream.str());
    return res;
}


void recorder::record_audio(QString str)
{
    start = std::chrono::system_clock::now();
    session.setAudioInput(&audioInput);
    session.setRecorder(&rec);
    rec.setQuality(QMediaRecorder::HighQuality);
    qDebug() << rec.actualLocation();
    rec.setOutputLocation(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/" + str));
    qDebug() << rec.actualLocation();
    qDebug() << str;
    rec.record();
}
