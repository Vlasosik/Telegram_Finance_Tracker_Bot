#include "bot/ui_manager/UIManager.h"

void UIManager::sendMainBar(const TgBot::Bot &bot, int64_t userId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    for (const std::vector<std::string> buttons{"Доступні категорії", "Управління категоріями", "Допомога"};
         const auto &button: buttons) {
        auto createInlineButton = std::make_shared<TgBot::InlineKeyboardButton>();
        createInlineButton->text = button;
        createInlineButton->callbackData = button;
        keyboard->inlineKeyboard.push_back({createInlineButton});
    }
    auto message = bot.getApi().sendMessage(
        userId, "Оберіть що вас цікавить 👇🏻", nullptr, nullptr, keyboard
    );
}

void UIManager::sendCategoryBar(const TgBot::Bot &bot, int64_t userId) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();

    auto buttonFood = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonFood->text = "Їжа";
    buttonFood->callbackData = "Їжа";
    auto buttonHousing = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonHousing->text = "Житло";
    buttonHousing->callbackData = "Житло";

    keyboard->inlineKeyboard.push_back({buttonFood, buttonHousing});

    auto buttonClothingAndFootwear = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonClothingAndFootwear->text = "Одяг та взуття";
    buttonClothingAndFootwear->callbackData = "Одяг та взуття";

    const auto buttonTransport = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonTransport->text = "Транспорт";
    buttonTransport->callbackData = "Транспорт";
    keyboard->inlineKeyboard.push_back({buttonClothingAndFootwear, buttonTransport});


    auto buttonFamilyAndChildren = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonFamilyAndChildren->text = "Сімʼя та діти";
    buttonFamilyAndChildren->callbackData = "Сімʼя та діти";

    auto buttonPersonalExpenses = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonPersonalExpenses->text = "Особисті витрати";
    buttonPersonalExpenses->callbackData = "Особисті витрати";
    keyboard->inlineKeyboard.push_back({buttonFamilyAndChildren, buttonPersonalExpenses});

    const auto buttonSavings = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonSavings->text = "Накопичення";
    buttonSavings->callbackData = "Накопичення";

    auto buttonEducationAndSelfDevelopment = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonEducationAndSelfDevelopment->text = "Освіта та розвиток";
    buttonEducationAndSelfDevelopment->callbackData = "Освіта та розвиток";
    keyboard->inlineKeyboard.push_back({buttonSavings, buttonEducationAndSelfDevelopment});

    auto buttonBack = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonBack->text = "Назад";
    buttonBack->callbackData = "Назад";
    keyboard->inlineKeyboard.push_back({buttonBack});

    auto message = bot.getApi().sendMessage(
        userId, "Оберіть категорії які вас цікавлять ✅",
        nullptr, nullptr, keyboard);
}

void UIManager::sendCategoryManagementBar(const TgBot::Bot &bot, int64_t userId) {
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
    auto message = bot.getApi().sendMessage(userId, "Оберіть що вас цікавить👇🏻",
                                            nullptr, nullptr, keyboard);
}

void UIManager::sendReportTransactionBar(const TgBot::Bot &bot, int64_t userId) {
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
    auto message = bot.getApi().sendMessage(userId, "Оберіть звіт який вас цікавить👇🏻",
                                            nullptr, nullptr, keyboard);
}
