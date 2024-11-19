cmake_minimum_required(VERSION 3.10)
project(telegram_finance_tracker_bot)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_subdirectory(tgbot-cpp)

add_executable(telegram_finance_tracker_bot ${SRC_FILES} main.cpp
        include/PCH.h
        src/bot/FinanceTrackerBot.cpp
        include/bot/FinanceTrackerBot.h
        src/transactions/Transaction.cpp
        include/transactions/Transaction.h
        include/finance_manager/FinanceManager.h
        src/finance_manager/FinanceManager.cpp
)

target_precompile_headers(telegram_finance_tracker_bot PRIVATE include/pch.h)

target_link_libraries(telegram_finance_tracker_bot TgBot)
