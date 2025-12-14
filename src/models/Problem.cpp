#include "Problem.h"

Problem::Problem(int id, const QString& title, const QString& url, Difficulty difficulty)
    : id_(id), title_(title), url_(url), difficulty_(difficulty),
      category_(Category::New), status_(CompletionStatus::NotStarted),
      timeSpent_(0), sessionTime_(0) {
}

void Problem::addTimeSpent(int seconds) {
    timeSpent_ += seconds;
    sessionTime_ += seconds;
}

QString Problem::getDifficultyString() const {
    switch (difficulty_) {
        case Difficulty::Easy: return "Easy";
        case Difficulty::Medium: return "Medium";
        case Difficulty::Hard: return "Hard";
    }
    return "Unknown";
}

QString Problem::getCategoryString() const {
    switch (category_) {
        case Category::New: return "New";
        case Category::Incomplete: return "Incomplete";
        case Category::Completed: return "Completed";
    }
    return "Unknown";
}

QString Problem::getStatusString() const {
    switch (status_) {
        case CompletionStatus::NotStarted: return "Not Started";
        case CompletionStatus::InProgress: return "In Progress";
        case CompletionStatus::Completed: return "Completed";
    }
    return "Unknown";
}