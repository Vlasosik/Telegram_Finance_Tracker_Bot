#include "bot/callback_command/CallbackRemoveTransaction.h"

#include "user/UserManager.h"

void CallbackRemoveTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    userManager.getUser(userId);
    userManager.setState(userId, UserStateType::REMOVED_TRANSACTION);
    auto message = bot.getApi().sendMessage(userId, "Для того щоб видалити транзакцію, потрібно ввести:\n"
                                            "1. Категорію\n"
                                            "2. Суму\n"
                                            "3. Дату транзакції\n"
                                            "Приклад: Їжа 150 24.08.2001 13:15:25 \n"
                                            "Якщо ви не памʼятаєте точної дати, ви завжди можете переглянути список транзакцій.");
}
