#include "bot/ui_manager/UIManager.h"

void UIManager::sendMainBar(const TgBot::Bot &bot, int64_t userId, const int32_t messageId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    for (const std::vector<std::string> buttons{"Доступні категорії", "Управління категоріями", "Допомога"};
         const auto &button: buttons) {
        auto createInlineButton = std::make_shared<TgBot::InlineKeyboardButton>();
        createInlineButton->text = button;
        createInlineButton->callbackData = button;
        keyboard->inlineKeyboard.push_back({createInlineButton});
    }
    if (messageId != 0) {
        auto editMessage = bot.getApi().editMessageText(
            "Оберіть що вас цікавить 👇🏻", userId, messageId, "", "", nullptr,
            std::make_shared<TgBot::InlineKeyboardMarkup>(*keyboard)
        );
    } else {
        auto sendMessage = bot.getApi().sendMessage(
            userId, "Оберіть що вас цікавить 👇🏻", nullptr, nullptr, keyboard
        );
    }
}

void UIManager::sendCategoryBar(const TgBot::Bot &bot, int64_t userId, const int32_t messageId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();

    auto createButton = [&](const std::string &text) {
        auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = text;
        button->callbackData = text;
        return button;
    };

    keyboard->inlineKeyboard.push_back({createButton("Їжа"), createButton("Житло")});
    keyboard->inlineKeyboard.push_back({createButton("Одяг"), createButton("Транспорт")});
    keyboard->inlineKeyboard.push_back({createButton("Сімʼя"), createButton("Накопичення")});
    keyboard->inlineKeyboard.push_back({createButton("Освіта"), createButton("Інше")});

    auto buttonBack = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonBack->text = "Назад";
    buttonBack->callbackData = "Назад";
    keyboard->inlineKeyboard.push_back({buttonBack});

    bot.getApi().editMessageText(
        "Оберіть категорії які вас цікавлять ✅",
        userId,
        messageId,
        "",
        "",
        nullptr,
        std::make_shared<TgBot::InlineKeyboardMarkup>(*keyboard)
    );
}

void UIManager::sendCategoryManagementBar(const TgBot::Bot &bot, int64_t userId, int32_t messageId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    for (const std::vector<std::string> buttons{
             "Додати транзакцію", "Видалити транзакцію", "Оновити транзакцію",
             "Список транзакцій", "Звіт транзакцій", "Назад"
         };
         const auto &button: buttons) {
        auto createInlineButton = std::make_shared<TgBot::InlineKeyboardButton>();
        createInlineButton->text = button;
        createInlineButton->callbackData = button;
        keyboard->inlineKeyboard.push_back({createInlineButton});
    }
    auto editMessage = bot.getApi().editMessageText(
        "Оберіть що вас цікавить 👇🏻", userId, messageId, "", "",
        nullptr, std::make_shared<TgBot::InlineKeyboardMarkup>(*keyboard));
}

void UIManager::sendReportTransactionBar(const TgBot::Bot &bot, int64_t userId, const int32_t messageId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    for (const std::vector<std::string> buttons{
             "Список транзакцій за тиждень", "Сума транзакцій за тиждень",
             "Список транзакцій за місяць", "Сума транзакцій за місяць", "Назад"
         };
         const auto &button: buttons) {
        auto createInlineButton = std::make_shared<TgBot::InlineKeyboardButton>();
        createInlineButton->text = button;
        createInlineButton->callbackData = button;
        keyboard->inlineKeyboard.push_back({createInlineButton});
    }
    auto editMessage = bot.getApi().editMessageText(
        "Оберіть який звіт вас цікавить 👇🏻", userId, messageId, "", "",
        nullptr, std::make_shared<TgBot::InlineKeyboardMarkup>(*keyboard));
}
