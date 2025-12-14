#include "MainWindow.h"
#include "ProblemWidget.h"
#include "TimerWidget.h"
#include "ProgressWidget.h"
#include "StatisticsWidget.h"
#include "AddProblemDialog.h"
#include "../models/ProblemDatabase.h"
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), sessionManager_(std::make_unique<DailySessionManager>(this)) {
    
    setWindowTitle("LeetCode Progress Tracker");
    setMinimumSize(1200, 800);
    
    // Initialize database
    if (!ProblemDatabase::instance().initialize()) {
        QMessageBox::critical(this, "Error", "Failed to initialize database!");
        QApplication::quit();
        return;
    }
    
    setupUI();
    setupMenuBar();
    setupStatusBar();
    loadStyleSheet();
    
    // Connect session manager signals
    connect(sessionManager_.get(), &DailySessionManager::sessionStarted,
            this, &MainWindow::onSessionStarted);
    connect(sessionManager_.get(), &DailySessionManager::problemCompleted,
            this, &MainWindow::onProblemCompleted);
    connect(sessionManager_.get(), &DailySessionManager::dailyGoalReached,
            this, &MainWindow::onDailyGoalReached);
}

void MainWindow::setupUI() {
    centralWidget_ = new QWidget(this);
    setCentralWidget(centralWidget_);
    
    // Create main layout
    auto* mainLayout = new QHBoxLayout(centralWidget_);
    mainSplitter_ = new QSplitter(Qt::Horizontal, this);
    mainLayout->addWidget(mainSplitter_);
    
    // Left panel with problems and progress
    leftSplitter_ = new QSplitter(Qt::Vertical, this);
    
    // Problem list
    problemWidget_ = new ProblemWidget(this);
    leftSplitter_->addWidget(problemWidget_);
    
    // Progress widget
    progressWidget_ = new ProgressWidget(sessionManager_.get(), this);
    leftSplitter_->addWidget(progressWidget_);
    
    leftSplitter_->setSizes({600, 200});
    mainSplitter_->addWidget(leftSplitter_);
    
    // Right panel with timer and controls
    auto* rightPanel = new QWidget(this);
    auto* rightLayout = new QVBoxLayout(rightPanel);
    
    // Timer widget
    timerWidget_ = new TimerWidget(this);
    rightLayout->addWidget(timerWidget_);
    
    // Control buttons
    startSessionBtn_ = new QPushButton("Start Daily Session", this);
    addProblemBtn_ = new QPushButton("Add Problem", this);
    statisticsBtn_ = new QPushButton("Statistics", this);
    learnCppBtn_ = new QPushButton("Open LearnCPP", this);
    
    rightLayout->addWidget(startSessionBtn_);
    rightLayout->addWidget(addProblemBtn_);
    rightLayout->addWidget(statisticsBtn_);
    rightLayout->addWidget(learnCppBtn_);
    rightLayout->addStretch();
    
    mainSplitter_->addWidget(rightPanel);
    mainSplitter_->setSizes({800, 400});
    
    // Connect buttons
    connect(startSessionBtn_, &QPushButton::clicked, this, &MainWindow::startDailySession);
    connect(addProblemBtn_, &QPushButton::clicked, this, &MainWindow::showAddProblemDialog);
    connect(statisticsBtn_, &QPushButton::clicked, this, &MainWindow::showStatistics);
    connect(learnCppBtn_, &QPushButton::clicked, this, &MainWindow::openLearnCpp);
}

void MainWindow::setupMenuBar() {
    auto* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&Add Problem", this, &MainWindow::showAddProblemDialog, QKeySequence::New);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close, QKeySequence::Quit);
    
    auto* sessionMenu = menuBar()->addMenu("&Session");
    sessionMenu->addAction("&Start Daily Session", this, &MainWindow::startDailySession, QKeySequence("Ctrl+S"));
    
    auto* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction("&Statistics", this, &MainWindow::showStatistics, QKeySequence("F1"));
    helpMenu->addAction("&LearnCPP", this, &MainWindow::openLearnCpp, QKeySequence("Ctrl+L"));
}

void MainWindow::setupStatusBar() {
    statusBar()->showMessage("Ready");
}

void MainWindow::loadStyleSheet() {
    QFile file(":/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        setStyleSheet(styleSheet);
    }
}

void MainWindow::startDailySession() {
    if (sessionManager_->startDailySession()) {
        startSessionBtn_->setText("Session Active");
        startSessionBtn_->setEnabled(false);
        statusBar()->showMessage("Daily session started!");
    } else {
        QMessageBox::warning(this, "Warning", "Failed to start daily session. Make sure you have enough problems in each category.");
    }
}

void MainWindow::showAddProblemDialog() {
    AddProblemDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        refreshProblemList();
    }
}

void MainWindow::showStatistics() {
    if (!statisticsWidget_) {
        statisticsWidget_ = new StatisticsWidget(this);
    }
    statisticsWidget_->show();
    statisticsWidget_->raise();
}

void MainWindow::openLearnCpp() {
    QDesktopServices::openUrl(QUrl("https://www.learncpp.com"));
}

void MainWindow::onSessionStarted() {
    refreshProblemList();
    progressWidget_->updateProgress();
}

void MainWindow::onProblemCompleted(int problemId) {
    Q_UNUSED(problemId)
    refreshProblemList();
    progressWidget_->updateProgress();
    statusBar()->showMessage("Problem completed!");
}

void MainWindow::onDailyGoalReached() {
    QMessageBox::information(this, "Congratulations!", "Daily goal reached! Great job!");
    statusBar()->showMessage("Daily goal completed!");
}

void MainWindow::refreshProblemList() {
    if (sessionManager_->isDailySessionActive()) {
        problemWidget_->loadTodaysProblems(sessionManager_->getTodaysProblems());
    } else {
        problemWidget_->loadAllProblems();
    }
}

#include "MainWindow.moc"