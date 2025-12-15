cmake_minimum_required(VERSION 3.20)
project(LeetProgressTracker VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt6_standard_project_setup()

set(SOURCES
    src/main.cpp
    src/models/Problem.cpp
    src/models/ProblemDatabase.cpp
    src/components/Timer.cpp
    src/managers/DailySessionManager.cpp
    src/ui/MainWindow.cpp
    src/ui/ProblemWidget.cpp
    src/ui/TimerWidget.cpp
    src/ui/ProgressWidget.cpp
    src/ui/AddProblemDialog.cpp
    src/ui/StatisticsWidget.cpp
)

set(HEADERS
    src/models/Problem.h
    src/models/ProblemDatabase.h
    src/components/Timer.h
    src/managers/DailySessionManager.h
    src/ui/MainWindow.h
    src/ui/ProblemWidget.h
    src/ui/TimerWidget.h
    src/ui/ProgressWidget.h
    src/ui/AddProblemDialog.h
    src/ui/StatisticsWidget.h
)

qt6_add_executable(LeetProgressTracker ${SOURCES} ${HEADERS})

qt6_add_resources(LeetProgressTracker "resources"
    PREFIX "/"
    FILES
        resources/styles.qss
)

target_link_libraries(LeetProgressTracker PRIVATE Qt6::Core Qt6::Widgets Qt6::Sql)

# Platform-specific settings
if(WIN32)
    set_target_properties(LeetProgressTracker PROPERTIES WIN32_EXECUTABLE TRUE)
endif()