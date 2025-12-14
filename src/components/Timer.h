#pragma once
#include <QObject>
#include <QTimer>

class Timer : public QObject {
    Q_OBJECT

public:
    explicit Timer(int durationMinutes = 15, QObject* parent = nullptr);
    
    void start();
    void pause();
    void reset();
    void stop();
    
    bool isRunning() const { return timer_->isActive(); }
    int getRemainingSeconds() const { return remainingSeconds_; }
    int getElapsedSeconds() const { return durationSeconds_ - remainingSeconds_; }
    int getDurationSeconds() const { return durationSeconds_; }
    
    void setDuration(int minutes);

signals:
    void timeChanged(int remainingSeconds);
    void finished();

private slots:
    void onTimeout();

private:
    QTimer* timer_;
    int durationSeconds_;
    int remainingSeconds_;
};