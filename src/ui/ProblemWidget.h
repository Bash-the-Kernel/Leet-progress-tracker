#pragma once
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "../models/Problem.h"
#include <memory>
#include <vector>

class ProblemWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProblemWidget(QWidget* parent = nullptr);
    
    void loadAllProblems();
    void loadTodaysProblems(std::vector<std::unique_ptr<Problem>> problems);

signals:
    void problemSelected(int problemId);
    void problemCompleted(int problemId);

private slots:
    void onProblemSelectionChanged();
    void onMarkCompleted();
    void onOpenUrl();
    void onCategoryFilterChanged();

private:
    void setupUI();
    void addProblemToList(const Problem& problem);
    void updateProblemDetails(const Problem* problem);
    void clearProblemDetails();
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QHBoxLayout* filterLayout_;
    QComboBox* categoryFilter_;
    QListWidget* problemList_;
    
    // Problem details panel
    QWidget* detailsPanel_;
    QLabel* titleLabel_;
    QLabel* difficultyLabel_;
    QLabel* categoryLabel_;
    QLabel* statusLabel_;
    QLabel* timeLabel_;
    QPushButton* markCompletedBtn_;
    QPushButton* openUrlBtn_;
    
    // Current selection
    int selectedProblemId_;
    std::vector<std::unique_ptr<Problem>> currentProblems_;
};