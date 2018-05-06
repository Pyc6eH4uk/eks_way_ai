set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.8.2)
project(eks_way_ai)

set(CMAKE_CXX_STANDARD 11)

add_executable(eks_way_ai
        source/abstract_simplex_task_t.cpp
        source/abstract_simplex_task_t.h
        source/linear_cut_task_t.cpp
        source/linear_cut_task_t.h
        source/simplex_definitions.h
        source/simplex_method_equality_t.cpp
        source/simplex_method_equality_t.h
        source/simplex_method_t.cpp
        source/simplex_method_t.h
        source/simplex_method_unequality_t.cpp
        source/simplex_method_unequality_t.h
        source/simplex_task_t.cpp
        source/simplex_task_t.h
        main.cpp source/abstract_debuger_t.cpp source/abstract_debuger_t.h source/linear_cut_debuger_t.cpp source/linear_cut_debuger_t.h source/intefrace/window_cut.cpp source/intefrace/window_cut.h source/intefrace/table_widget.h source/intefrace/table_widget.cpp)

# qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH /home/pyc6eh4uk/Qt/5.9.1/gcc_64/lib/cmake)
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5OpenGL REQUIRED )
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL )