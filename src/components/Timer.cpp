#include "Timer.h"

Timer::Timer(int durationMinutes, QObject* parent)
    : QObject(parent), durationSeconds_(durationMinutes * 60), remainingSeconds_(durationMinutes * 60) {
    timer_ = new QTimer(this);
    timer_->setInterval(1000); // 1 second
    connect(timer_, &QTimer::timeout, this, &Timer::onTimeout);
}

void Timer::start() {
    if (!timer_->isActive()) {
        timer_->start();
    }
}

void Timer::pause() {
    timer_->stop();
}

void Timer::reset() {
    timer_->stop();
    remainingSeconds_ = durationSeconds_;
    emit timeChanged(remainingSeconds_);
}

void Timer::stop() {
    timer_->stop();
    remainingSeconds_ = durationSeconds_;
}

void Timer::setDuration(int minutes) {
    bool wasRunning = timer_->isActive();
    timer_->stop();
    
    durationSeconds_ = minutes * 60;
    remainingSeconds_ = durationSeconds_;
    
    emit timeChanged(remainingSeconds_);
    
    if (wasRunning) {
        timer_->start();
    }
}

void Timer::onTimeout() {
    remainingSeconds_--;
    emit timeChanged(remainingSeconds_);
    
    if (remainingSeconds_ <= 0) {
        timer_->stop();
        emit finished();
    }
}

#include "Timer.moc"