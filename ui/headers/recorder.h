#ifndef RECORDER_H
#define RECORDER_H
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaCaptureSession>
#include <sstream>
#include <chrono>

class recorder : public QObject
{
    Q_OBJECT
public:
    explicit recorder(QObject *parent = nullptr);
    void stop_recording();

    QString time_duration();

public slots:

    void record_audio(QString str);


signals:

private:
    QMediaRecorder rec;
    QMediaCaptureSession session;
    QAudioInput audioInput;
    std::chrono::time_point<std::chrono::system_clock> start;
};

#endif // RECORDER_H
