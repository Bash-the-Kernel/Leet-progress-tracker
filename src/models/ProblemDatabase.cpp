#include "ProblemDatabase.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

ProblemDatabase& ProblemDatabase::instance() {
    static ProblemDatabase instance;
    return instance;
}

bool ProblemDatabase::initialize() {
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataPath);
    
    db_ = QSqlDatabase::addDatabase("QSQLITE");
    db_.setDatabaseName(dataPath + "/leetcode_tracker.db");
    
    if (!db_.open()) {
        qDebug() << "Failed to open database:" << db_.lastError().text();
        return false;
    }
    
    return createTables();
}

bool ProblemDatabase::createTables() {
    QSqlQuery query(db_);
    
    // Problems table
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS problems (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            url TEXT NOT NULL,
            difficulty INTEGER NOT NULL,
            category INTEGER NOT NULL,
            status INTEGER NOT NULL,
            time_spent INTEGER DEFAULT 0,
            last_attempted TEXT
        )
    )")) {
        qDebug() << "Failed to create problems table:" << query.lastError().text();
        return false;
    }
    
    // Daily sessions table
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS daily_sessions (
            date TEXT PRIMARY KEY,
            problem_ids TEXT NOT NULL,
            completed INTEGER DEFAULT 0
        )
    )")) {
        qDebug() << "Failed to create daily_sessions table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

bool ProblemDatabase::addProblem(const Problem& problem) {
    QSqlQuery query(db_);
    query.prepare(R"(
        INSERT INTO problems (title, url, difficulty, category, status, time_spent, last_attempted)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )");
    
    query.addBindValue(problem.getTitle());
    query.addBindValue(problem.getUrl());
    query.addBindValue(static_cast<int>(problem.getDifficulty()));
    query.addBindValue(static_cast<int>(problem.getCategory()));
    query.addBindValue(static_cast<int>(problem.getStatus()));
    query.addBindValue(problem.getTimeSpent());
    query.addBindValue(problem.getLastAttempted().toString(Qt::ISODate));
    
    return query.exec();
}

bool ProblemDatabase::updateProblem(const Problem& problem) {
    QSqlQuery query(db_);
    query.prepare(R"(
        UPDATE problems SET title=?, url=?, difficulty=?, category=?, status=?, 
               time_spent=?, last_attempted=? WHERE id=?
    )");
    
    query.addBindValue(problem.getTitle());
    query.addBindValue(problem.getUrl());
    query.addBindValue(static_cast<int>(problem.getDifficulty()));
    query.addBindValue(static_cast<int>(problem.getCategory()));
    query.addBindValue(static_cast<int>(problem.getStatus()));
    query.addBindValue(problem.getTimeSpent());
    query.addBindValue(problem.getLastAttempted().toString(Qt::ISODate));
    query.addBindValue(problem.getId());
    
    return query.exec();
}

bool ProblemDatabase::deleteProblem(int id) {
    QSqlQuery query(db_);
    query.prepare("DELETE FROM problems WHERE id = ?");
    query.addBindValue(id);
    return query.exec();
}

std::unique_ptr<Problem> ProblemDatabase::getProblem(int id) {
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM problems WHERE id = ?");
    query.addBindValue(id);
    query.exec();
    
    if (query.next()) {
        auto problem = std::make_unique<Problem>(
            query.value("id").toInt(),
            query.value("title").toString(),
            query.value("url").toString(),
            static_cast<Difficulty>(query.value("difficulty").toInt())
        );
        
        problem->setCategory(static_cast<Category>(query.value("category").toInt()));
        problem->setStatus(static_cast<CompletionStatus>(query.value("status").toInt()));
        
        return problem;
    }
    
    return nullptr;
}

std::vector<std::unique_ptr<Problem>> ProblemDatabase::getAllProblems() {
    std::vector<std::unique_ptr<Problem>> problems;
    QSqlQuery query("SELECT * FROM problems", db_);
    
    while (query.next()) {
        auto problem = std::make_unique<Problem>(
            query.value("id").toInt(),
            query.value("title").toString(),
            query.value("url").toString(),
            static_cast<Difficulty>(query.value("difficulty").toInt())
        );
        
        problem->setCategory(static_cast<Category>(query.value("category").toInt()));
        problem->setStatus(static_cast<CompletionStatus>(query.value("status").toInt()));
        
        problems.push_back(std::move(problem));
    }
    
    return problems;
}

std::vector<std::unique_ptr<Problem>> ProblemDatabase::getProblemsByCategory(Category category) {
    std::vector<std::unique_ptr<Problem>> problems;
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM problems WHERE category = ?");
    query.addBindValue(static_cast<int>(category));
    query.exec();
    
    while (query.next()) {
        auto problem = std::make_unique<Problem>(
            query.value("id").toInt(),
            query.value("title").toString(),
            query.value("url").toString(),
            static_cast<Difficulty>(query.value("difficulty").toInt())
        );
        
        problem->setCategory(static_cast<Category>(query.value("category").toInt()));
        problem->setStatus(static_cast<CompletionStatus>(query.value("status").toInt()));
        
        problems.push_back(std::move(problem));
    }
    
    return problems;
}

bool ProblemDatabase::saveDailySession(const QDate& date, const std::vector<int>& problemIds) {
    QSqlQuery query(db_);
    query.prepare("INSERT OR REPLACE INTO daily_sessions (date, problem_ids) VALUES (?, ?)");
    
    QString idsString;
    for (size_t i = 0; i < problemIds.size(); ++i) {
        if (i > 0) idsString += ",";
        idsString += QString::number(problemIds[i]);
    }
    
    query.addBindValue(date.toString(Qt::ISODate));
    query.addBindValue(idsString);
    
    return query.exec();
}

std::vector<int> ProblemDatabase::getDailySession(const QDate& date) {
    std::vector<int> problemIds;
    QSqlQuery query(db_);
    query.prepare("SELECT problem_ids FROM daily_sessions WHERE date = ?");
    query.addBindValue(date.toString(Qt::ISODate));
    query.exec();
    
    if (query.next()) {
        QString idsString = query.value("problem_ids").toString();
        QStringList idsList = idsString.split(",", Qt::SkipEmptyParts);
        for (const QString& id : idsList) {
            problemIds.push_back(id.toInt());
        }
    }
    
    return problemIds;
}

bool ProblemDatabase::hasDailySession(const QDate& date) {
    QSqlQuery query(db_);
    query.prepare("SELECT COUNT(*) FROM daily_sessions WHERE date = ?");
    query.addBindValue(date.toString(Qt::ISODate));
    query.exec();
    
    return query.next() && query.value(0).toInt() > 0;
}

int ProblemDatabase::getStreak() {
    QSqlQuery query(db_);
    query.prepare(R"(
        SELECT COUNT(*) FROM daily_sessions 
        WHERE date >= date('now', '-30 days') 
        ORDER BY date DESC
    )");
    query.exec();
    
    return query.next() ? query.value(0).toInt() : 0;
}

int ProblemDatabase::getTotalCompleted() {
    QSqlQuery query("SELECT COUNT(*) FROM problems WHERE status = 2", db_);
    return query.next() ? query.value(0).toInt() : 0;
}

std::map<Difficulty, int> ProblemDatabase::getDifficultyStats() {
    std::map<Difficulty, int> stats;
    QSqlQuery query("SELECT difficulty, COUNT(*) FROM problems WHERE status = 2 GROUP BY difficulty", db_);
    
    while (query.next()) {
        Difficulty diff = static_cast<Difficulty>(query.value(0).toInt());
        int count = query.value(1).toInt();
        stats[diff] = count;
    }
    
    return stats;
}

#include "ProblemDatabase.moc"