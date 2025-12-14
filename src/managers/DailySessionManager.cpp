#include "DailySessionManager.h"
#include <QRandomGenerator>
#include <algorithm>

DailySessionManager::DailySessionManager(QObject* parent)
    : QObject(parent), sessionActive_(false), currentDate_(QDate::currentDate()) {
}

bool DailySessionManager::startDailySession() {
    currentDate_ = QDate::currentDate();
    
    // Check if session already exists for today
    if (ProblemDatabase::instance().hasDailySession(currentDate_)) {
        todaysProblemIds_ = ProblemDatabase::instance().getDailySession(currentDate_);
        sessionActive_ = true;
        emit sessionStarted();
        return true;
    }
    
    // Create new daily session
    if (selectDailyProblems()) {
        ProblemDatabase::instance().saveDailySession(currentDate_, todaysProblemIds_);
        sessionActive_ = true;
        emit sessionStarted();
        return true;
    }
    
    return false;
}

bool DailySessionManager::selectDailyProblems() {
    todaysProblemIds_.clear();
    
    // Get 2 completed problems
    auto completedIds = getRandomProblems(Category::Completed, 2);
    todaysProblemIds_.insert(todaysProblemIds_.end(), completedIds.begin(), completedIds.end());
    
    // Get 2 incomplete problems
    auto incompleteIds = getRandomProblems(Category::Incomplete, 2);
    todaysProblemIds_.insert(todaysProblemIds_.end(), incompleteIds.begin(), incompleteIds.end());
    
    // Get 3 new problems
    auto newIds = getRandomProblems(Category::New, 3);
    todaysProblemIds_.insert(todaysProblemIds_.end(), newIds.begin(), newIds.end());
    
    return todaysProblemIds_.size() == 7;
}

std::vector<int> DailySessionManager::getRandomProblems(Category category, int count) {
    auto problems = ProblemDatabase::instance().getProblemsByCategory(category);
    std::vector<int> ids;
    
    for (const auto& problem : problems) {
        ids.push_back(problem->getId());
    }
    
    // Shuffle and take first 'count' items
    std::shuffle(ids.begin(), ids.end(), *QRandomGenerator::global());
    
    if (ids.size() > static_cast<size_t>(count)) {
        ids.resize(count);
    }
    
    return ids;
}

std::vector<std::unique_ptr<Problem>> DailySessionManager::getTodaysProblems() {
    std::vector<std::unique_ptr<Problem>> problems;
    
    for (int id : todaysProblemIds_) {
        auto problem = ProblemDatabase::instance().getProblem(id);
        if (problem) {
            problems.push_back(std::move(problem));
        }
    }
    
    return problems;
}

int DailySessionManager::getCompletedCount() const {
    int completed = 0;
    
    for (int id : todaysProblemIds_) {
        auto problem = ProblemDatabase::instance().getProblem(id);
        if (problem && problem->getStatus() == CompletionStatus::Completed) {
            completed++;
        }
    }
    
    return completed;
}

double DailySessionManager::getProgressPercentage() const {
    return (static_cast<double>(getCompletedCount()) / 7.0) * 100.0;
}

void DailySessionManager::markProblemCompleted(int problemId) {
    auto problem = ProblemDatabase::instance().getProblem(problemId);
    if (problem) {
        problem->setStatus(CompletionStatus::Completed);
        problem->updateLastAttempted();
        ProblemDatabase::instance().updateProblem(*problem);
        
        emit problemCompleted(problemId);
        
        if (getCompletedCount() >= 7) {
            emit dailyGoalReached();
        }
    }
}

void DailySessionManager::updateProblemTime(int problemId, int seconds) {
    auto problem = ProblemDatabase::instance().getProblem(problemId);
    if (problem) {
        problem->addTimeSpent(seconds);
        problem->updateLastAttempted();
        ProblemDatabase::instance().updateProblem(*problem);
    }
}

#include "DailySessionManager.moc"