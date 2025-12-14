#include "StatisticsWidget.h"
#include "../models/ProblemDatabase.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>

StatisticsWidget::StatisticsWidget(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("Statistics");
    setWindowFlags(Qt::Window);
    resize(600, 400);
    
    setupUI();
    loadStatistics();
}

void StatisticsWidget::setupUI() {
    mainLayout_ = new QVBoxLayout(this);
    
    // Title
    titleLabel_ = new QLabel("LeetCode Progress Statistics", this);
    titleLabel_->setAlignment(Qt::AlignCenter);
    titleLabel_->setStyleSheet("font-size: 20px; font-weight: bold; margin: 15px;");
    mainLayout_->addWidget(titleLabel_);
    
    // Summary statistics
    summaryLayout_ = new QHBoxLayout();
    
    totalProblemsLabel_ = new QLabel("Total Problems: 0", this);
    totalProblemsLabel_->setStyleSheet("font-size: 14px; padding: 10px; border: 1px solid #ccc; border-radius: 5px;");
    
    completedLabel_ = new QLabel("Completed: 0", this);
    completedLabel_->setStyleSheet("font-size: 14px; padding: 10px; border: 1px solid #ccc; border-radius: 5px; background-color: #e8f5e8;");
    
    streakLabel_ = new QLabel("Current Streak: 0 days", this);
    streakLabel_->setStyleSheet("font-size: 14px; padding: 10px; border: 1px solid #ccc; border-radius: 5px; background-color: #fff3e0;");
    
    summaryLayout_->addWidget(totalProblemsLabel_);
    summaryLayout_->addWidget(completedLabel_);
    summaryLayout_->addWidget(streakLabel_);
    
    mainLayout_->addLayout(summaryLayout_);
    
    // Difficulty breakdown table
    auto* tableLabel = new QLabel("Difficulty Breakdown:", this);
    tableLabel->setStyleSheet("font-size: 16px; font-weight: bold; margin-top: 20px;");
    mainLayout_->addWidget(tableLabel);
    
    difficultyTable_ = new QTableWidget(3, 3, this);
    difficultyTable_->setHorizontalHeaderLabels({"Difficulty", "Completed", "Percentage"});
    difficultyTable_->verticalHeader()->setVisible(false);
    difficultyTable_->horizontalHeader()->setStretchLastSection(true);
    difficultyTable_->setAlternatingRowColors(true);
    difficultyTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
    difficultyTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    mainLayout_->addWidget(difficultyTable_);
    
    // Control buttons
    buttonLayout_ = new QHBoxLayout();
    
    refreshBtn_ = new QPushButton("Refresh", this);
    exportBtn_ = new QPushButton("Export to CSV", this);
    closeBtn_ = new QPushButton("Close", this);
    
    buttonLayout_->addWidget(refreshBtn_);
    buttonLayout_->addWidget(exportBtn_);
    buttonLayout_->addStretch();
    buttonLayout_->addWidget(closeBtn_);
    
    mainLayout_->addLayout(buttonLayout_);
    
    // Connect signals
    connect(refreshBtn_, &QPushButton::clicked, this, &StatisticsWidget::refreshStats);
    connect(exportBtn_, &QPushButton::clicked, this, &StatisticsWidget::exportToCsv);
    connect(closeBtn_, &QPushButton::clicked, this, &QWidget::close);
}

void StatisticsWidget::loadStatistics() {
    auto allProblems = ProblemDatabase::instance().getAllProblems();
    int totalProblems = static_cast<int>(allProblems.size());
    int totalCompleted = ProblemDatabase::instance().getTotalCompleted();
    int streak = ProblemDatabase::instance().getStreak();
    
    // Update summary labels
    totalProblemsLabel_->setText(QString("Total Problems: %1").arg(totalProblems));
    completedLabel_->setText(QString("Completed: %1").arg(totalCompleted));
    streakLabel_->setText(QString("Current Streak: %1 days").arg(streak));
    
    updateDifficultyChart();
}

void StatisticsWidget::updateDifficultyChart() {
    auto difficultyStats = ProblemDatabase::instance().getDifficultyStats();
    auto allProblems = ProblemDatabase::instance().getAllProblems();
    
    // Count total problems by difficulty
    std::map<Difficulty, int> totalByDifficulty;
    for (const auto& problem : allProblems) {
        totalByDifficulty[problem->getDifficulty()]++;
    }
    
    // Populate table
    QStringList difficulties = {"Easy", "Medium", "Hard"};
    std::vector<Difficulty> diffEnums = {Difficulty::Easy, Difficulty::Medium, Difficulty::Hard};
    
    for (int i = 0; i < 3; ++i) {
        Difficulty diff = diffEnums[i];
        int completed = difficultyStats.count(diff) ? difficultyStats[diff] : 0;
        int total = totalByDifficulty.count(diff) ? totalByDifficulty[diff] : 0;
        double percentage = total > 0 ? (static_cast<double>(completed) / total * 100.0) : 0.0;
        
        difficultyTable_->setItem(i, 0, new QTableWidgetItem(difficulties[i]));
        difficultyTable_->setItem(i, 1, new QTableWidgetItem(QString("%1 / %2").arg(completed).arg(total)));
        difficultyTable_->setItem(i, 2, new QTableWidgetItem(QString("%1%").arg(percentage, 0, 'f', 1)));
        
        // Color coding
        QColor bgColor;
        if (percentage >= 80) bgColor = QColor(200, 255, 200);
        else if (percentage >= 50) bgColor = QColor(255, 255, 200);
        else bgColor = QColor(255, 200, 200);
        
        for (int col = 0; col < 3; ++col) {
            difficultyTable_->item(i, col)->setBackground(bgColor);
        }
    }
    
    difficultyTable_->resizeColumnsToContents();
}

void StatisticsWidget::refreshStats() {
    loadStatistics();
}

void StatisticsWidget::exportToCsv() {
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Statistics to CSV",
        defaultPath + "/leetcode_stats.csv",
        "CSV Files (*.csv)"
    );
    
    if (fileName.isEmpty()) {
        return;
    }
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Export Error", "Failed to create CSV file!");
        return;
    }
    
    QTextStream out(&file);
    
    // Write header
    out << "Problem Title,Difficulty,Category,Status,Time Spent (minutes),Last Attempted\n";
    
    // Write problem data
    auto allProblems = ProblemDatabase::instance().getAllProblems();
    for (const auto& problem : allProblems) {
        out << QString("\"%1\",\"%2\",\"%3\",\"%4\",%5,\"%6\"\n")
               .arg(problem->getTitle())
               .arg(problem->getDifficultyString())
               .arg(problem->getCategoryString())
               .arg(problem->getStatusString())
               .arg(problem->getTimeSpent() / 60.0, 0, 'f', 1)
               .arg(problem->getLastAttempted().toString("yyyy-MM-dd hh:mm:ss"));
    }
    
    file.close();
    QMessageBox::information(this, "Export Complete", QString("Statistics exported to:\n%1").arg(fileName));
}

#include "StatisticsWidget.moc"