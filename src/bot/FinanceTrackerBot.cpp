#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
    setUp();
}

[[noreturn]] void FinanceTrackerBot::run() const {
    TgBot::TgLongPoll long_poll(bot);
    std::cout << bot.getApi().getMyName()->name << ": started.\n";
    while (true) {
        long_poll.start();
    }
}

void FinanceTrackerBot::setUp() {
    bot.getEvents().onCommand("start", [this](const TgBot::Message::Ptr &message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Вас вітає телеграм який допоможе краще керувати вашими фінанасами.");
        sendMainBar(message->chat->id);
    });
    bot.getEvents().onCallbackQuery([this](const TgBot::CallbackQuery::Ptr &query) {
        auto dataFromUser = query->data;
        if (dataFromUser == "Категорії") {
            sendCategoryBar(query->message->chat->id);
        } else if (dataFromUser == "Назад") {
            sendMainBar(query->message->chat->id);
        }else {
            addCategory(query->message->chat->id, dataFromUser);
        }
    });
}

void FinanceTrackerBot::addCategory(int64_t userId, const std::string &category) {
    auto range = chosenCategories.equal_range(userId);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second == category) {
            bot.getApi().sendMessage(userId, "Категорія \"" + category + "\" вже була додана.");
            return;
        }
    }
    chosenCategories.emplace(userId, category);
    bot.getApi().sendMessage(userId, "Категорія \"" + category + "\" додана до вибраних.");
}


void FinanceTrackerBot::sendMainBar(int64_t userId) const {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
    std::vector<std::string> buttonCategory{"Категорії", "Управління витратами", "Допомога"};
    for (const auto &nameButton: buttonCategory) {
        const auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = nameButton;
        button->callbackData = nameButton;
        keyboard->inlineKeyboard.push_back({button});
    }
    auto message = bot.getApi().sendMessage(
        userId, "Виберіть що вас цікавить:",
        nullptr, nullptr, keyboard);
}

void FinanceTrackerBot::sendCategoryBar(int64_t userId) const {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();

    auto buttonFood = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonFood->text = "Їжа";
    buttonFood->callbackData = "Food";
    auto buttonHousing = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonHousing->text = "Житло";
    buttonHousing->callbackData = "Housing";

    keyboard->inlineKeyboard.push_back({buttonFood, buttonHousing});

    auto buttonClothingAndFootwear = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonClothingAndFootwear->text = "Одяг та взуття";
    buttonClothingAndFootwear->callbackData = "Clothing and Footwear";

    const auto buttonTransport = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonTransport->text = "Транспорт";
    buttonTransport->callbackData = "Transport";
    keyboard->inlineKeyboard.push_back({buttonClothingAndFootwear, buttonTransport});


    auto buttonFamilyAndChildren = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonFamilyAndChildren->text = "Сімʼя та діти";
    buttonFamilyAndChildren->callbackData = "Family and children";

    auto buttonPersonalExpenses = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonPersonalExpenses->text = "Особисті витрати";
    buttonPersonalExpenses->callbackData = "Personal expenses";
    keyboard->inlineKeyboard.push_back({buttonFamilyAndChildren, buttonPersonalExpenses});

    const auto buttonSavings = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonSavings->text = "Накопичення";
    buttonSavings->callbackData = "Savings";

    auto buttonEducationAndSelfDevelopment = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonEducationAndSelfDevelopment->text = "Освіта та розвиток";
    buttonEducationAndSelfDevelopment->callbackData = "Education and development";
    keyboard->inlineKeyboard.push_back({buttonPersonalExpenses, buttonEducationAndSelfDevelopment});

    auto buttonBack = std::make_shared<TgBot::InlineKeyboardButton>();
    buttonBack->text = "Назад";
    buttonBack->callbackData = "Назад";
    keyboard->inlineKeyboard.push_back({buttonBack});

    auto message = bot.getApi().sendMessage(
        userId, "Виберіть позицію або декілька позицій для відслідковування ваших фінансів😊",
        nullptr, nullptr, keyboard);
}
