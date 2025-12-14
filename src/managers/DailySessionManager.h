#pragma once
#include "../models/Problem.h"
#include "../models/ProblemDatabase.h"
#include <QObject>
#include <QDate>
#include <vector>
#include <memory>

class DailySessionManager : public QObject {
    Q_OBJECT

public:
    explicit DailySessionManager(QObject* parent = nullptr);
    
    // Daily session management
    bool startDailySession();
    std::vector<std::unique_ptr<Problem>> getTodaysProblems();
    bool isDailySessionActive() const { return sessionActive_; }
    
    // Progress tracking
    int getCompletedCount() const;
    int getTotalProblemsForToday() const { return 7; }
    double getProgressPercentage() const;
    
    // Problem management
    void markProblemCompleted(int problemId);
    void updateProblemTime(int problemId, int seconds);

signals:
    void sessionStarted();
    void problemCompleted(int problemId);
    void dailyGoalReached();

private:
    bool selectDailyProblems();
    std::vector<int> getRandomProblems(Category category, int count);
    
    std::vector<int> todaysProblemIds_;
    bool sessionActive_;
    QDate currentDate_;
};