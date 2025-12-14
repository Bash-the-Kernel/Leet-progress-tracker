#pragma once
#include "Problem.h"
#include <QSqlDatabase>
#include <QDate>
#include <vector>
#include <memory>
#include <map>

class ProblemDatabase {
public:
    static ProblemDatabase& instance();
    
    bool initialize();
    
    // Problem operations
    bool addProblem(const Problem& problem);
    bool updateProblem(const Problem& problem);
    bool deleteProblem(int id);
    std::unique_ptr<Problem> getProblem(int id);
    std::vector<std::unique_ptr<Problem>> getAllProblems();
    std::vector<std::unique_ptr<Problem>> getProblemsByCategory(Category category);
    
    // Daily session operations
    bool saveDailySession(const QDate& date, const std::vector<int>& problemIds);
    std::vector<int> getDailySession(const QDate& date);
    bool hasDailySession(const QDate& date);
    
    // Statistics
    int getStreak();
    int getTotalCompleted();
    std::map<Difficulty, int> getDifficultyStats();
    
private:
    ProblemDatabase() = default;
    bool createTables();
    
    QSqlDatabase db_;
};