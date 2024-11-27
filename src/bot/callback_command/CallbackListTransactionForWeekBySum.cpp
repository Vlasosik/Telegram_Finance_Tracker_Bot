#include "bot/callback_command/CallbackListTransactionForWeekBySum.h"

void CallbackListTransactionForWeekBySum::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        userManager.setState(userId, UserStateType::SELECTING_REPORT);
        const auto transactions = userManager.getListTransactionForWeekBySum(userId);
        std::ostringstream messageStream;
        messageStream << transactions;
        int index = 1;
        messageStream << index++ << ". " << ", Сума усіх транзакцій за тиждень становить: " << transactions;
        auto message = bot.getApi().sendMessage(userId, messageStream.str());
    } catch (std::invalid_argument &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        auto sendMessage = bot.getApi().sendMessage(userId,
                                                    "Ще не пройшов тиждень для того, щоб отримати звіт.");
    }
}
