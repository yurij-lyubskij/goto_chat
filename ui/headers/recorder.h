#ifndef RECORDER_H
#define RECORDER_H
#include <QMediaRecorder>
#include <QAudioInput>
#include <QMediaCaptureSession>

class recorder : public QObject
{
    Q_OBJECT
public:
    explicit recorder(QObject *parent = nullptr);
    void stop_recording();

public slots:

    void record_audio(QString str);


signals:

private:
    QMediaRecorder rec;
    QMediaCaptureSession session;
    QAudioInput audioInput;
};

#endif // RECORDER_H
