#include "bot/callback_command/CallbackAddTransaction.h"

#include "user/UserManager.h"

void CallbackAddTransaction::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    userManager.getUser(userId);
    userManager.setState(userId, UserStateType::ENTERING_AMOUNT);
    if (userManager.hasUserSelectedCategory(userId)) {
        auto message = bot.getApi().sendMessage(userId,
                                                "Будь ласка, введіть суму транзакції.");
    } else {
        auto message = bot.getApi().sendMessage(userId,
                                                "Будь ласка, виберіть категорію.");
    }
}
