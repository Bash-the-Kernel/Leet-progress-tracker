#include "ProblemWidget.h"
#include "../models/ProblemDatabase.h"
#include <QDesktopServices>
#include <QUrl>
#include <QListWidgetItem>

ProblemWidget::ProblemWidget(QWidget* parent)
    : QWidget(parent), selectedProblemId_(-1) {
    setupUI();
    loadAllProblems();
}

void ProblemWidget::setupUI() {
    mainLayout_ = new QVBoxLayout(this);
    
    // Filter section
    filterLayout_ = new QHBoxLayout();
    filterLayout_->addWidget(new QLabel("Filter:", this));
    
    categoryFilter_ = new QComboBox(this);
    categoryFilter_->addItem("All", -1);
    categoryFilter_->addItem("New", static_cast<int>(Category::New));
    categoryFilter_->addItem("Incomplete", static_cast<int>(Category::Incomplete));
    categoryFilter_->addItem("Completed", static_cast<int>(Category::Completed));
    
    filterLayout_->addWidget(categoryFilter_);
    filterLayout_->addStretch();
    mainLayout_->addLayout(filterLayout_);
    
    // Problem list
    problemList_ = new QListWidget(this);
    mainLayout_->addWidget(problemList_);
    
    // Problem details panel
    detailsPanel_ = new QWidget(this);
    auto* detailsLayout = new QVBoxLayout(detailsPanel_);
    
    titleLabel_ = new QLabel("Select a problem", this);
    titleLabel_->setWordWrap(true);
    titleLabel_->setStyleSheet("font-weight: bold; font-size: 14px;");
    
    difficultyLabel_ = new QLabel(this);
    categoryLabel_ = new QLabel(this);
    statusLabel_ = new QLabel(this);
    timeLabel_ = new QLabel(this);
    
    auto* buttonLayout = new QHBoxLayout();
    markCompletedBtn_ = new QPushButton("Mark Completed", this);
    openUrlBtn_ = new QPushButton("Open LeetCode", this);
    
    buttonLayout->addWidget(markCompletedBtn_);
    buttonLayout->addWidget(openUrlBtn_);
    
    detailsLayout->addWidget(titleLabel_);
    detailsLayout->addWidget(difficultyLabel_);
    detailsLayout->addWidget(categoryLabel_);
    detailsLayout->addWidget(statusLabel_);
    detailsLayout->addWidget(timeLabel_);
    detailsLayout->addLayout(buttonLayout);
    detailsLayout->addStretch();
    
    mainLayout_->addWidget(detailsPanel_);
    
    // Connect signals
    connect(problemList_, &QListWidget::currentRowChanged, this, &ProblemWidget::onProblemSelectionChanged);
    connect(markCompletedBtn_, &QPushButton::clicked, this, &ProblemWidget::onMarkCompleted);
    connect(openUrlBtn_, &QPushButton::clicked, this, &ProblemWidget::onOpenUrl);
    connect(categoryFilter_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ProblemWidget::onCategoryFilterChanged);
    
    clearProblemDetails();
}

void ProblemWidget::loadAllProblems() {
    currentProblems_ = ProblemDatabase::instance().getAllProblems();
    
    problemList_->clear();
    for (const auto& problem : currentProblems_) {
        addProblemToList(*problem);
    }
}

void ProblemWidget::loadTodaysProblems(std::vector<std::unique_ptr<Problem>> problems) {
    currentProblems_ = std::move(problems);
    
    problemList_->clear();
    for (const auto& problem : currentProblems_) {
        addProblemToList(*problem);
    }
}

void ProblemWidget::addProblemToList(const Problem& problem) {
    QString itemText = QString("[%1] %2 - %3")
                      .arg(problem.getDifficultyString())
                      .arg(problem.getTitle())
                      .arg(problem.getStatusString());
    
    auto* item = new QListWidgetItem(itemText);
    item->setData(Qt::UserRole, problem.getId());
    
    // Color coding based on status
    if (problem.getStatus() == CompletionStatus::Completed) {
        item->setBackground(QColor(46, 125, 50, 50)); // Green
    } else if (problem.getStatus() == CompletionStatus::InProgress) {
        item->setBackground(QColor(255, 152, 0, 50)); // Orange
    }
    
    problemList_->addItem(item);
}

void ProblemWidget::onProblemSelectionChanged() {
    int currentRow = problemList_->currentRow();
    if (currentRow >= 0 && currentRow < static_cast<int>(currentProblems_.size())) {
        const Problem* problem = currentProblems_[currentRow].get();
        selectedProblemId_ = problem->getId();
        updateProblemDetails(problem);
        emit problemSelected(selectedProblemId_);
    } else {
        clearProblemDetails();
    }
}

void ProblemWidget::updateProblemDetails(const Problem* problem) {
    if (!problem) {
        clearProblemDetails();
        return;
    }
    
    titleLabel_->setText(problem->getTitle());
    difficultyLabel_->setText("Difficulty: " + problem->getDifficultyString());
    categoryLabel_->setText("Category: " + problem->getCategoryString());
    statusLabel_->setText("Status: " + problem->getStatusString());
    
    int minutes = problem->getTimeSpent() / 60;
    int seconds = problem->getTimeSpent() % 60;
    timeLabel_->setText(QString("Time Spent: %1:%2").arg(minutes).arg(seconds, 2, 10, QChar('0')));
    
    markCompletedBtn_->setEnabled(problem->getStatus() != CompletionStatus::Completed);
    openUrlBtn_->setEnabled(!problem->getUrl().isEmpty());
}

void ProblemWidget::clearProblemDetails() {
    titleLabel_->setText("Select a problem");
    difficultyLabel_->clear();
    categoryLabel_->clear();
    statusLabel_->clear();
    timeLabel_->clear();
    markCompletedBtn_->setEnabled(false);
    openUrlBtn_->setEnabled(false);
    selectedProblemId_ = -1;
}

void ProblemWidget::onMarkCompleted() {
    if (selectedProblemId_ > 0) {
        emit problemCompleted(selectedProblemId_);
        
        // Refresh the current problem details
        int currentRow = problemList_->currentRow();
        if (currentRow >= 0 && currentRow < static_cast<int>(currentProblems_.size())) {
            // Reload the problem from database to get updated status
            auto updatedProblem = ProblemDatabase::instance().getProblem(selectedProblemId_);
            if (updatedProblem) {
                currentProblems_[currentRow] = std::move(updatedProblem);
                updateProblemDetails(currentProblems_[currentRow].get());
                
                // Update list item
                auto* item = problemList_->item(currentRow);
                const Problem& problem = *currentProblems_[currentRow];
                QString itemText = QString("[%1] %2 - %3")
                                  .arg(problem.getDifficultyString())
                                  .arg(problem.getTitle())
                                  .arg(problem.getStatusString());
                item->setText(itemText);
                item->setBackground(QColor(46, 125, 50, 50)); // Green for completed
            }
        }
    }
}

void ProblemWidget::onOpenUrl() {
    int currentRow = problemList_->currentRow();
    if (currentRow >= 0 && currentRow < static_cast<int>(currentProblems_.size())) {
        const Problem& problem = *currentProblems_[currentRow];
        if (!problem.getUrl().isEmpty()) {
            QDesktopServices::openUrl(QUrl(problem.getUrl()));
        }
    }
}

void ProblemWidget::onCategoryFilterChanged() {
    int categoryValue = categoryFilter_->currentData().toInt();
    
    if (categoryValue == -1) {
        loadAllProblems();
    } else {
        Category category = static_cast<Category>(categoryValue);
        currentProblems_ = ProblemDatabase::instance().getProblemsByCategory(category);
        
        problemList_->clear();
        for (const auto& problem : currentProblems_) {
            addProblemToList(*problem);
        }
    }
}