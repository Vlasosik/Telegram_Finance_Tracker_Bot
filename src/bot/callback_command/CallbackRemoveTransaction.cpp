#include "bot/callback_command/CallbackRemoveTransaction.h"

void CallbackRemoveTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    auto &userManager = UserManager::getInstance();
    userManager.getUser(userId);
    userManager.setState(userId, UserStateType::REMOVED_TRANSACTION);
    auto message = bot.getApi().sendMessage(userId, "Для того щоб видалити транзакцію, потрібно ввести:\n"
                                   "1. Категорію\n"
                                   "2. Суму\n"
                                   "3. Дату транзакції 'День, місяць, рік' 'Година, хвилина, секунда'\n"
                                   "Якщо ви не памʼятаєте точно дати, ви завжди можете переглянути список транзакцій.");
}
