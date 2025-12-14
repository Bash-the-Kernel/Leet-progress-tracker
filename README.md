# LeetCode Progress Tracker

A modern C++ desktop application for tracking daily LeetCode practice with timers and progress visualization.

## Features

### 🎯 Daily Practice System
- **Structured Daily Sessions**: Complete exactly 7 problems per day
  - 2 Previously Completed problems (review)
  - 2 Incomplete problems (continue working)
  - 3 New problems (fresh challenges)
- **Session Lock**: Daily problem set is locked once started
- **Automatic Reset**: Progress resets at midnight

### ⏱️ Smart Timer System
- **15-minute Problem Timer**: Countdown timer for each problem
- **Visual Progress**: Real-time countdown with color-coded urgency
- **Break Timer**: Optional 5-minute break between problems
- **Time Tracking**: Automatic logging of time spent per problem
- **Configurable Duration**: Adjust timer length as needed

### 📊 Progress Visualization
- **Daily Progress Bar**: Visual completion status (X/7 problems)
- **Streak Tracking**: Consecutive days completed
- **Difficulty Breakdown**: Statistics by Easy/Medium/Hard
- **Time Analytics**: Total time spent per problem and session

### 🗄️ Data Management
- **SQLite Database**: Local, offline data storage
- **Problem Categories**: Organize problems by completion status
- **Persistent State**: All progress saved automatically
- **CSV Export**: Export statistics for external analysis

### 🎨 Modern UI
- **Dark Theme**: Easy on the eyes for long coding sessions
- **Clean Interface**: Minimal, distraction-free design
- **Responsive Layout**: Resizable panels and components
- **Keyboard Shortcuts**: Quick access to common actions

### 🔗 Integration Features
- **LeetCode Links**: Direct links to problems
- **LearnCPP Integration**: Quick access to C++ learning resources
- **Problem Management**: Add, edit, and categorize problems

## Screenshots

*[Screenshots would go here in a real project]*

## Quick Start

1. **Install Prerequisites**: Qt6, CMake, C++20 compiler
2. **Build the Application**: See [BUILD.md](BUILD.md) for detailed instructions
3. **Add Problems**: Use "Add Problem" to populate your problem database
4. **Start Daily Session**: Click "Start Daily Session" to begin
5. **Track Progress**: Use the timer for each problem and mark as completed

## Architecture

### Core Components
- **Problem Model**: Stores problem data (title, URL, difficulty, status, time)
- **Timer Component**: Handles countdown timers with pause/resume
- **Daily Session Manager**: Implements 2-2-3 problem selection algorithm
- **Database Layer**: SQLite persistence with clean API
- **UI Layer**: Qt6 widgets with modern styling

### Design Principles
- **RAII**: Automatic resource management
- **Smart Pointers**: Memory safety with std::unique_ptr
- **Separation of Concerns**: Clear boundaries between components
- **Modern C++**: C++20 features and best practices

## Usage Guide

### Adding Problems
1. Click "Add Problem" or use Ctrl+N
2. Enter problem title and LeetCode URL
3. Select difficulty (Easy/Medium/Hard)
4. Choose initial category (New/Incomplete/Completed)

### Daily Workflow
1. Start your day by clicking "Start Daily Session"
2. The app selects 7 problems based on the algorithm
3. Work through each problem using the 15-minute timer
4. Mark problems as completed when finished
5. Take breaks using the 5-minute break timer
6. View progress in the progress panel

### Timer Usage
- **Start/Pause**: Control timer during problem solving
- **Reset**: Restart timer for current problem
- **Break**: Take a 5-minute break (opens LearnCPP)
- **Duration**: Adjust timer length in settings

### Statistics
- View detailed statistics in the Statistics window
- Export progress data to CSV for analysis
- Track streaks and completion rates by difficulty

## Keyboard Shortcuts

- `Ctrl+N`: Add new problem
- `Ctrl+S`: Start daily session
- `Ctrl+L`: Open LearnCPP
- `F1`: Show statistics
- `Ctrl+Q`: Quit application

## Data Storage

The application stores data locally in:
- **Windows**: `%APPDATA%/LeetTracker/leetcode_tracker.db`
- **macOS**: `~/Library/Application Support/LeetTracker/leetcode_tracker.db`
- **Linux**: `~/.local/share/LeetTracker/leetcode_tracker.db`

## Contributing

This is a complete, production-ready application. The codebase follows modern C++ practices and is well-documented for maintenance and extension.

### Code Structure
```
src/
├── models/          # Data models and database
├── components/      # Reusable components (Timer)
├── managers/        # Business logic (DailySessionManager)
├── ui/             # User interface widgets
└── main.cpp        # Application entry point
```

## License

[Add your license here]

## Acknowledgments

- Qt6 framework for the excellent GUI toolkit
- SQLite for reliable local data storage
- LeetCode for providing the platform that inspired this tool