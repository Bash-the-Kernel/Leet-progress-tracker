#include "TimerWidget.h"
#include <QMessageBox>

TimerWidget::TimerWidget(QWidget* parent)
    : QWidget(parent), isBreakMode_(false), elapsedSeconds_(0) {
    
    problemTimer_ = std::make_unique<Timer>(15, this);
    breakTimer_ = std::make_unique<Timer>(5, this);
    
    setupUI();
    
    // Connect timer signals
    connect(problemTimer_.get(), &Timer::timeChanged, this, &TimerWidget::onTimeChanged);
    connect(problemTimer_.get(), &Timer::finished, this, &TimerWidget::onTimerFinished);
    connect(breakTimer_.get(), &Timer::timeChanged, this, &TimerWidget::onTimeChanged);
    connect(breakTimer_.get(), &Timer::finished, this, &TimerWidget::onTimerFinished);
}

void TimerWidget::setupUI() {
    mainLayout_ = new QVBoxLayout(this);
    
    // Title
    titleLabel_ = new QLabel("Problem Timer", this);
    titleLabel_->setAlignment(Qt::AlignCenter);
    titleLabel_->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    mainLayout_->addWidget(titleLabel_);
    
    // Time display
    timeDisplay_ = new QLabel("15:00", this);
    timeDisplay_->setAlignment(Qt::AlignCenter);
    timeDisplay_->setStyleSheet("font-size: 48px; font-weight: bold; color: #2196F3; margin: 20px;");
    mainLayout_->addWidget(timeDisplay_);
    
    // Progress bar
    progressBar_ = new QProgressBar(this);
    progressBar_->setRange(0, 100);
    progressBar_->setValue(100);
    progressBar_->setStyleSheet("QProgressBar { height: 20px; }");
    mainLayout_->addWidget(progressBar_);
    
    // Control buttons
    controlLayout_ = new QHBoxLayout();
    
    startPauseBtn_ = new QPushButton("Start", this);
    resetBtn_ = new QPushButton("Reset", this);
    breakBtn_ = new QPushButton("Break (5min)", this);
    
    controlLayout_->addWidget(startPauseBtn_);
    controlLayout_->addWidget(resetBtn_);
    controlLayout_->addWidget(breakBtn_);
    
    mainLayout_->addLayout(controlLayout_);
    
    // Duration settings
    settingsLayout_ = new QHBoxLayout();
    durationLabel_ = new QLabel("Duration (min):", this);
    durationSpinBox_ = new QSpinBox(this);
    durationSpinBox_->setRange(1, 60);
    durationSpinBox_->setValue(15);
    
    settingsLayout_->addWidget(durationLabel_);
    settingsLayout_->addWidget(durationSpinBox_);
    settingsLayout_->addStretch();
    
    mainLayout_->addLayout(settingsLayout_);
    mainLayout_->addStretch();
    
    // Connect button signals
    connect(startPauseBtn_, &QPushButton::clicked, this, &TimerWidget::onStartPause);
    connect(resetBtn_, &QPushButton::clicked, this, &TimerWidget::onReset);
    connect(breakBtn_, &QPushButton::clicked, this, &TimerWidget::startBreakTimer);
    connect(durationSpinBox_, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &TimerWidget::onDurationChanged);
}

void TimerWidget::onStartPause() {
    Timer* currentTimer = isBreakMode_ ? breakTimer_.get() : problemTimer_.get();
    
    if (currentTimer->isRunning()) {
        currentTimer->pause();
        startPauseBtn_->setText("Start");
        
        // Emit elapsed time for problem timer
        if (!isBreakMode_) {
            int elapsed = currentTimer->getElapsedSeconds() - elapsedSeconds_;
            elapsedSeconds_ = currentTimer->getElapsedSeconds();
            emit timeElapsed(elapsed);
        }
    } else {
        currentTimer->start();
        startPauseBtn_->setText("Pause");
    }
}

void TimerWidget::onReset() {
    Timer* currentTimer = isBreakMode_ ? breakTimer_.get() : problemTimer_.get();
    
    // Emit remaining elapsed time before reset
    if (!isBreakMode_ && elapsedSeconds_ < currentTimer->getElapsedSeconds()) {
        int elapsed = currentTimer->getElapsedSeconds() - elapsedSeconds_;
        emit timeElapsed(elapsed);
    }
    
    currentTimer->reset();
    elapsedSeconds_ = 0;
    updateDisplay();
    updateButtons();
}

void TimerWidget::onTimeChanged(int remainingSeconds) {
    Q_UNUSED(remainingSeconds)
    updateDisplay();
}

void TimerWidget::onTimerFinished() {
    if (isBreakMode_) {
        QMessageBox::information(this, "Break Over", "Break time is over! Ready to continue?");
        isBreakMode_ = false;
        titleLabel_->setText("Problem Timer");
        breakBtn_->setEnabled(true);
        durationSpinBox_->setEnabled(true);
    } else {
        // Emit final elapsed time
        int elapsed = problemTimer_->getElapsedSeconds() - elapsedSeconds_;
        elapsedSeconds_ = 0;
        emit timeElapsed(elapsed);
        
        QMessageBox::information(this, "Time's Up!", "15 minutes are up! Take a break or continue to the next problem.");
    }
    
    updateButtons();
}

void TimerWidget::onDurationChanged() {
    if (!isBreakMode_) {
        problemTimer_->setDuration(durationSpinBox_->value());
        updateDisplay();
    }
}

void TimerWidget::startBreakTimer() {
    // Save elapsed time from problem timer
    if (!isBreakMode_ && problemTimer_->isRunning()) {
        int elapsed = problemTimer_->getElapsedSeconds() - elapsedSeconds_;
        elapsedSeconds_ = problemTimer_->getElapsedSeconds();
        emit timeElapsed(elapsed);
        problemTimer_->pause();
    }
    
    isBreakMode_ = true;
    titleLabel_->setText("Break Timer");
    breakTimer_->reset();
    breakTimer_->start();
    
    startPauseBtn_->setText("Pause");
    breakBtn_->setEnabled(false);
    durationSpinBox_->setEnabled(false);
    
    updateDisplay();
}

void TimerWidget::updateDisplay() {
    Timer* currentTimer = isBreakMode_ ? breakTimer_.get() : problemTimer_.get();
    
    int remainingSeconds = currentTimer->getRemainingSeconds();
    timeDisplay_->setText(formatTime(remainingSeconds));
    
    // Update progress bar
    double progress = static_cast<double>(remainingSeconds) / currentTimer->getDurationSeconds() * 100.0;
    progressBar_->setValue(static_cast<int>(progress));
    
    // Color coding for urgency
    if (remainingSeconds <= 60) { // Last minute
        timeDisplay_->setStyleSheet("font-size: 48px; font-weight: bold; color: #F44336; margin: 20px;");
    } else if (remainingSeconds <= 300) { // Last 5 minutes
        timeDisplay_->setStyleSheet("font-size: 48px; font-weight: bold; color: #FF9800; margin: 20px;");
    } else {
        timeDisplay_->setStyleSheet("font-size: 48px; font-weight: bold; color: #2196F3; margin: 20px;");
    }
}

void TimerWidget::updateButtons() {
    Timer* currentTimer = isBreakMode_ ? breakTimer_.get() : problemTimer_.get();
    
    if (currentTimer->isRunning()) {
        startPauseBtn_->setText("Pause");
    } else {
        startPauseBtn_->setText("Start");
    }
}

QString TimerWidget::formatTime(int seconds) const {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    return QString("%1:%2").arg(minutes).arg(secs, 2, 10, QChar('0'));
}

#include "TimerWidget.moc"