#include "bot/callback_command/CallbackListTransactionForMonthBySum.h"

#include "user/UserManager.h"

void CallbackListTransactionForMonthBySum::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        userManager.setState(userId, UserStateType::SELECTING_REPORT);
        const auto transactions = userManager.getListTransactionForMonth(userId);

        if (transactions.empty()) {
            auto sendMessage = bot.getApi().sendMessage(userId, "У вас поки що немає транзакцій.");
            return;
        }
        const auto firstTransactionDate = transactions.front().getDate();
        const auto now = std::chrono::system_clock::now();
        const auto weekAgo = now - std::chrono::days(7);

        if (firstTransactionDate > weekAgo) {
            auto sendMessage = bot.getApi().sendMessage(userId,
                                                        "Ще не пройшов місяць для того, щоб отримати звіт.");
            return;
        }
        const double totalSum = userManager.getListTransactionForMonthBySum(userId);
        std::ostringstream messageStream;
        messageStream << "Сума усіх транзакцій за тиждень становить: " << totalSum;
        auto message = bot.getApi().sendMessage(userId, messageStream.str());
    } catch (std::invalid_argument &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        auto sendMessage = bot.getApi().sendMessage(userId,
                                                    "Ще не пройшов місяць для того, щоб отримати звіт.");
    }
}
