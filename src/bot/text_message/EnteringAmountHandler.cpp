#include "bot/text_message/EnteringAmountHandler.h"

#include "user/UserManager.h"

bool EnteringAmountHandler::canHandle(int64_t userId, const TgBot::Message::Ptr &message) const {
    auto &userManager = UserManager::getInstance();
    userManager.getUser(userId);
    return userManager.getState(message->chat->id) == UserStateType::ENTERING_AMOUNT;
}

void EnteringAmountHandler::handleMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    int64_t userId = message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        const auto amount = std::stod(message->text);
        userManager.addTransactionByUser(userId, userManager.getUserSelectedCategory(userId), amount);
        userManager.setState(userId, UserStateType::IDLE);
        auto sendMessage = bot.getApi().sendMessage(userId, "Суму успішно додано.");
    } catch (const std::invalid_argument &) {
        auto sendMessage = bot.getApi().sendMessage(userId,
                                                    "Будь ласка, введіть коректне число для суми.");
    }
}
