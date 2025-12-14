#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QPushButton>
#include <QMenuBar>
#include <QStatusBar>
#include "../managers/DailySessionManager.h"

class ProblemWidget;
class TimerWidget;
class ProgressWidget;
class StatisticsWidget;
class AddProblemDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;

private slots:
    void startDailySession();
    void showAddProblemDialog();
    void showStatistics();
    void openLearnCpp();
    void onSessionStarted();
    void onProblemCompleted(int problemId);
    void onDailyGoalReached();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();
    void loadStyleSheet();
    void refreshProblemList();
    
    // UI Components
    QWidget* centralWidget_;
    QSplitter* mainSplitter_;
    QSplitter* leftSplitter_;
    
    ProblemWidget* problemWidget_;
    TimerWidget* timerWidget_;
    ProgressWidget* progressWidget_;
    StatisticsWidget* statisticsWidget_;
    
    // Actions
    QPushButton* startSessionBtn_;
    QPushButton* addProblemBtn_;
    QPushButton* statisticsBtn_;
    QPushButton* learnCppBtn_;
    
    // Manager
    std::unique_ptr<DailySessionManager> sessionManager_;
};