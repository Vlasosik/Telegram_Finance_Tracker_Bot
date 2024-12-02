#include "bot/text_message/EnteringRemoveHandler.h"

#include "user/UserManager.h"

bool EnteringRemoveHandler::canHandle(const int64_t userId, const TgBot::Message::Ptr &message) const {
    auto &userManager = UserManager::getInstance();
    userManager.getUser(userId);
    return userManager.getState(userId) == UserStateType::REMOVED_TRANSACTION;
}

void EnteringRemoveHandler::handleMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) {
    const int64_t userId = message->chat->id;
    auto &userManager = UserManager::getInstance();
    try {
        const std::string &text = message->text;
        std::istringstream iss(text);
        std::string category;
        double amount;
        std::string datePart, timePart;
        if (!(iss >> category >> amount >> datePart >> timePart)) {
            throw std::invalid_argument("Помилка при розділенні введених даних");
        }
        std::tm tm{};
        std::istringstream dateStream(datePart + " " + timePart);
        dateStream >> std::get_time(&tm, "%d.%m.%Y %H:%M:%S");
        if (dateStream.fail()) {
            throw std::invalid_argument("Неправильний формат дати чи часу");
        }
        auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        Transaction transaction(userId, category, amount, timePoint);

        if (!userManager.transactionExists(userId, transaction)) {
            auto sendMessage = bot.getApi().sendMessage(userId, "Транзакція не знайдена.");
            return;
        }
        userManager.removeTransaction(userId, transaction);
        userManager.setState(userId, UserStateType::IDLE);

        auto sendMessage = bot.getApi().sendMessage(userId, "Транзакція успішно видалена.");
    } catch (const std::exception &ex) {
        bot.getApi().sendMessage(userId, std::string("Помилка: ") + ex.what());
    }
}
