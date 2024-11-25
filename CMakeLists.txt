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
        include/bot/message_command/StartMessageCommand.h
        src/bot/message_command/StartMessageCommand.cpp
        include/bot/ui_manager/UIManager.h
        src/bot/ui_manager/UIManager.cpp
        include/bot/message_command/InfoMessageCommand.h
        src/bot/message_command/InfoMessageCommand.cpp
        include/bot/message_command/MessageCommand.h
        include/bot/callback_command/CallbackCommand.h
        include/bot/callback_command/CallbackAvailableСategories.h
        src/bot/callback_command/CallbackAvailableCategories.cpp
        include/bot/callback_command/CallbackSelectedCategories.h
        src/bot/callback_command/CallbackSelectedCategories.cpp
        include/bot/callback_command/CallbackHelp.h
        src/bot/callback_command/CallbackHelp.cpp
        include/bot/callback_command/CallbackBack.h
        src/bot/callback_command/CallbackBack.cpp
        include/bot/callback_command/CallbackCategoryManagement.h
        src/bot/callback_command/CallbackCategoryManagement.cpp
        include/bot/callback_command/CallbackAddTransaction.h
        src/bot/callback_command/CallbackAddTransaction.cpp
        include/user/User.h
        src/user/User.cpp
        include/user/UserManager.h
        src/user/UserManager.cpp
        include/bot/text_message/TextMessage.h
        include/bot/text_message/EnteringAmountHandler.h
        src/bot/text_message/EnteringAmountHandler.cpp
        include/bot/callback_command/CallbackGetListTransaction.h
        src/bot/callback_command/CallbackGetListTransaction.cpp
)

target_precompile_headers(telegram_finance_tracker_bot PRIVATE include/pch.h)

target_link_libraries(telegram_finance_tracker_bot TgBot)
