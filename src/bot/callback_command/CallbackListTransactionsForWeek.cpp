#include "bot/callback_command/CallbackListTransactionsForWeek.h"

#include "user/UserManager.h"

void CallbackListTransactionsForWeek::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        userManager.setState(userId, UserStateType::SELECTING_REPORT);
        const auto transactions = userManager.getListTransactionForWeek(userId);
        std::ostringstream messageStream;
        if (transactions.empty()) {
            messageStream << "У вас поки що немає транзакцій.";
        } else {
            int index = 1;
            for (const auto &[fst, snd]: transactions) {
                messageStream << index++ << ". " << "Категорія: " << fst << ", " << "Сума: " << snd << "\n";
            }
        }
        auto message = bot.getApi().sendMessage(userId, messageStream.str());
    } catch (std::invalid_argument &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;

        auto sendMessage = bot.getApi().sendMessage(userId,
                                                    "Ще не пройшов тиждень для того, щоб отримати звіт.");
    }
}
