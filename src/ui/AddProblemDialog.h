#pragma once
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include "../models/Problem.h"

class AddProblemDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddProblemDialog(QWidget* parent = nullptr);

private slots:
    void onAccept();
    void onReject();

private:
    void setupUI();
    bool validateInput();
    
    // UI Components
    QVBoxLayout* mainLayout_;
    QFormLayout* formLayout_;
    
    QLineEdit* titleEdit_;
    QLineEdit* urlEdit_;
    QComboBox* difficultyCombo_;
    QComboBox* categoryCombo_;
    
    QDialogButtonBox* buttonBox_;
};