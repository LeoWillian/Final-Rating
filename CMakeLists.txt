cmake_minimum_required(VERSION 3.13)

# Ваш компилятор может не поддерживать C++17 и в таком случае можно прописать 14 или 11.
set(CMAKE_CXX_STANDARD 17)
# Отображать все предупреждения в процессе компиляции.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# Искать инклуды также и в текущей директории.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(students-rating)

# Для macOS добавляем путь до папки с установленным Qt 5.
set(QTPATH /usr/local/opt/qt)
if (APPLE AND EXISTS ${QTPATH})
    list(APPEND CMAKE_PREFIX_PATH ${QTPATH})
endif()

set(SOURCES
    main.cpp
    correct.h
    correct.cpp
    report.h
    report.cpp
    argparser.h
    argparser.cpp  
    errors.h   
    strategy.cpp
    strategy.h
)

find_package(Qt5Core CONFIG REQUIRED)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(students-rating Qt5::Core)
