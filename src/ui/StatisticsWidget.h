#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include "../models/Problem.h"
#include <map>

class StatisticsWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget* parent = nullptr);

private slots:
    void exportToCsv();
    void refreshStats();

private:
    void setupUI();
    void loadStatistics();
    void updateDifficultyChart();
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QLabel* titleLabel_;
    
    // Summary stats
    QHBoxLayout* summaryLayout_;
    QLabel* totalProblemsLabel_;
    QLabel* completedLabel_;
    QLabel* streakLabel_;
    
    // Difficulty breakdown
    QTableWidget* difficultyTable_;
    
    // Control buttons
    QHBoxLayout* buttonLayout_;
    QPushButton* refreshBtn_;
    QPushButton* exportBtn_;
    QPushButton* closeBtn_;
};