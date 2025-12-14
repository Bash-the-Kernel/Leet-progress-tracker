#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QSpinBox>
#include "../components/Timer.h"
#include <memory>

class TimerWidget : public QWidget {
    Q_OBJECT

public:
    explicit TimerWidget(QWidget* parent = nullptr);

signals:
    void timeElapsed(int seconds);

private slots:
    void onStartPause();
    void onReset();
    void onTimeChanged(int remainingSeconds);
    void onTimerFinished();
    void onDurationChanged();
    void startBreakTimer();

private:
    void setupUI();
    void updateDisplay();
    void updateButtons();
    QString formatTime(int seconds) const;
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QLabel* titleLabel_;
    QLabel* timeDisplay_;
    QProgressBar* progressBar_;
    
    QHBoxLayout* controlLayout_;
    QPushButton* startPauseBtn_;
    QPushButton* resetBtn_;
    QPushButton* breakBtn_;
    
    QHBoxLayout* settingsLayout_;
    QLabel* durationLabel_;
    QSpinBox* durationSpinBox_;
    
    // Timers
    std::unique_ptr<Timer> problemTimer_;
    std::unique_ptr<Timer> breakTimer_;
    
    // State
    bool isBreakMode_;
    int elapsedSeconds_;
};