#pragma once
#include <QString>
#include <QDateTime>
#include <memory>

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

enum class Category {
    New,
    Incomplete,
    Completed
};

enum class CompletionStatus {
    NotStarted,
    InProgress,
    Completed
};

class Problem {
public:
    Problem(int id, const QString& title, const QString& url, Difficulty difficulty);
    
    // Getters
    int getId() const { return id_; }
    QString getTitle() const { return title_; }
    QString getUrl() const { return url_; }
    Difficulty getDifficulty() const { return difficulty_; }
    Category getCategory() const { return category_; }
    CompletionStatus getStatus() const { return status_; }
    int getTimeSpent() const { return timeSpent_; }
    int getSessionTime() const { return sessionTime_; }
    QDateTime getLastAttempted() const { return lastAttempted_; }
    
    // Setters
    void setCategory(Category category) { category_ = category; }
    void setStatus(CompletionStatus status) { status_ = status; }
    void addTimeSpent(int seconds);
    void setSessionTime(int seconds) { sessionTime_ = seconds; }
    void updateLastAttempted() { lastAttempted_ = QDateTime::currentDateTime(); }
    
    // Utility
    QString getDifficultyString() const;
    QString getCategoryString() const;
    QString getStatusString() const;
    
private:
    int id_;
    QString title_;
    QString url_;
    Difficulty difficulty_;
    Category category_;
    CompletionStatus status_;
    int timeSpent_;      // Total time in seconds
    int sessionTime_;    // Current session time
    QDateTime lastAttempted_;
};