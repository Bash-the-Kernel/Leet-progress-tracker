#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include "../managers/DailySessionManager.h"

class ProgressWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProgressWidget(DailySessionManager* sessionManager, QWidget* parent = nullptr);
    
    void updateProgress();

private:
    void setupUI();
    void updateStreakInfo();
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QLabel* titleLabel_;
    QLabel* progressLabel_;
    QProgressBar* progressBar_;
    QLabel* streakLabel_;
    QLabel* totalCompletedLabel_;
    
    // Manager reference
    DailySessionManager* sessionManager_;
};