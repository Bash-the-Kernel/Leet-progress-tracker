#include "ProgressWidget.h"
#include "../models/ProblemDatabase.h"

ProgressWidget::ProgressWidget(DailySessionManager* sessionManager, QWidget* parent)
    : QWidget(parent), sessionManager_(sessionManager) {
    setupUI();
    updateProgress();
}

void ProgressWidget::setupUI() {
    mainLayout_ = new QVBoxLayout(this);
    
    // Title
    titleLabel_ = new QLabel("Daily Progress", this);
    titleLabel_->setAlignment(Qt::AlignCenter);
    titleLabel_->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
    mainLayout_->addWidget(titleLabel_);
    
    // Progress label
    progressLabel_ = new QLabel("0 / 7 problems completed", this);
    progressLabel_->setAlignment(Qt::AlignCenter);
    mainLayout_->addWidget(progressLabel_);
    
    // Progress bar
    progressBar_ = new QProgressBar(this);
    progressBar_->setRange(0, 7);
    progressBar_->setValue(0);
    progressBar_->setStyleSheet(R"(
        QProgressBar {
            height: 25px;
            border: 2px solid #3f51b5;
            border-radius: 12px;
            text-align: center;
            font-weight: bold;
        }
        QProgressBar::chunk {
            background-color: #4caf50;
            border-radius: 10px;
        }
    )");
    mainLayout_->addWidget(progressBar_);
    
    // Statistics section
    auto* statsLayout = new QVBoxLayout();
    
    streakLabel_ = new QLabel("Streak: 0 days", this);
    streakLabel_->setAlignment(Qt::AlignCenter);
    streakLabel_->setStyleSheet("font-size: 14px; margin: 5px;");
    
    totalCompletedLabel_ = new QLabel("Total Completed: 0", this);
    totalCompletedLabel_->setAlignment(Qt::AlignCenter);
    totalCompletedLabel_->setStyleSheet("font-size: 14px; margin: 5px;");
    
    statsLayout->addWidget(streakLabel_);
    statsLayout->addWidget(totalCompletedLabel_);
    
    mainLayout_->addLayout(statsLayout);
    mainLayout_->addStretch();
}

void ProgressWidget::updateProgress() {
    if (!sessionManager_->isDailySessionActive()) {
        progressLabel_->setText("Start daily session");
        progressBar_->setValue(0);
        updateStreakInfo();
        return;
    }
    
    int completed = sessionManager_->getCompletedCount();
    int total = sessionManager_->getTotalProblemsForToday();
    
    progressLabel_->setText(QString("%1 / %2 problems completed").arg(completed).arg(total));
    progressBar_->setValue(completed);
    
    // Update progress bar color based on completion
    if (completed == total) {
        progressBar_->setStyleSheet(R"(
            QProgressBar {
                height: 25px;
                border: 2px solid #4caf50;
                border-radius: 12px;
                text-align: center;
                font-weight: bold;
            }
            QProgressBar::chunk {
                background-color: #4caf50;
                border-radius: 10px;
            }
        )");
    } else if (completed >= total * 0.7) { // 70% or more
        progressBar_->setStyleSheet(R"(
            QProgressBar {
                height: 25px;
                border: 2px solid #ff9800;
                border-radius: 12px;
                text-align: center;
                font-weight: bold;
            }
            QProgressBar::chunk {
                background-color: #ff9800;
                border-radius: 10px;
            }
        )");
    } else {
        progressBar_->setStyleSheet(R"(
            QProgressBar {
                height: 25px;
                border: 2px solid #3f51b5;
                border-radius: 12px;
                text-align: center;
                font-weight: bold;
            }
            QProgressBar::chunk {
                background-color: #2196f3;
                border-radius: 10px;
            }
        )");
    }
    
    updateStreakInfo();
}

void ProgressWidget::updateStreakInfo() {
    int streak = ProblemDatabase::instance().getStreak();
    int totalCompleted = ProblemDatabase::instance().getTotalCompleted();
    
    streakLabel_->setText(QString("Streak: %1 days").arg(streak));
    totalCompletedLabel_->setText(QString("Total Completed: %1").arg(totalCompleted));
}

#include "ProgressWidget.moc"