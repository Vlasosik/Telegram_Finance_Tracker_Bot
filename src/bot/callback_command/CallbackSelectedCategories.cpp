#include "bot/callback_command/CallbackSelectedCategories.h"

#include "user/UserManager.h"

void CallbackSelectedCategories::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    int64_t userId = query->message->chat->id;
    userManager.getUser(userId);
    // userManager.setState(userId, UserStateType::SELECTING_CATEGORY);
    userManager.addCategory(userId, query->data);
    auto message = bot.getApi().sendMessage(
        userId, "Категорія " + userManager.getUserSelectedCategory(userId) + "  додана.");
}