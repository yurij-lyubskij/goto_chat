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

void recorder::record_audio(QString str)
{

    session.setAudioInput(&audioInput);
    session.setRecorder(&rec);
    rec.setQuality(QMediaRecorder::HighQuality);

    rec.setOutputLocation(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/" + str));


    rec.record();
}
