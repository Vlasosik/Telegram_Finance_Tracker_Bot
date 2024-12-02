#include "bot/callback_command/CallbackListTransactionForMonth.h"

#include "user/UserManager.h"

void CallbackListTransactionForMonth::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        userManager.setState(userId, UserStateType::SELECTING_REPORT);
        const auto transactions = userManager.getListTransactionForMonth(userId);

        const auto firstTransactionDate = transactions.front().getDate();
        const auto now = std::chrono::system_clock::now();
        const auto weekAgo = now - std::chrono::days(7);

        if (firstTransactionDate > weekAgo) {
            auto sendMessage = bot.getApi().sendMessage(userId,
                                                        "Ще не пройшов місяць для того, щоб отримати звіт.");
            return;
        }
        std::ostringstream messageStream;
        if (transactions.empty()) {
            messageStream << "У вас поки що немає транзакцій.";
        } else {
            messageStream << "Ваші транзакції за останній тиждень:\n\n";
            int index = 1;

            for (const auto &transaction: transactions) {
                messageStream << "№" << index++ << "\n";
                messageStream << "Категорія: " << transaction.getCategory() << "\n";
                messageStream << "Сума: " << std::fixed << std::setprecision(2) << transaction.getAmount() << "\n";
                auto date = transaction.getDate();
                std::time_t time_t_date = std::chrono::system_clock::to_time_t(date);
                std::tm tm_date = *std::localtime(&time_t_date);
                messageStream << "Дата: " << std::put_time(&tm_date, "%Y-%m-%d %H:%M:%S") << "\n";
                messageStream << "----------------------\n";
            }
        }
        auto message = bot.getApi().sendMessage(userId, messageStream.str());
    } catch (std::invalid_argument &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;

        auto sendMessage = bot.getApi().sendMessage(userId,
                                                    "Ще не пройшов місяць для того, щоб отримати звіт.");
    }
}
