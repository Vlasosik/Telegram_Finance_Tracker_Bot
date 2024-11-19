#include "bot/FinanceTrackerBot.h"

#include <tgbot/net/TgLongPoll.h>

FinanceTrackerBot::FinanceTrackerBot(const std::string &token) : bot(token) {
    setUp();
}

[[noreturn]] void FinanceTrackerBot::run() const {
    TgBot::TgLongPoll long_poll(bot);
    std::cout << bot.getApi().getMyName() << ": started.\n";
    while (true) {
        long_poll.start();
    }
}

void FinanceTrackerBot::setUp() {
    bot.getEvents().onCommand("start", [this](const TgBot::Message::Ptr &message) {
        bot.getApi().sendMessage(message->chat->id,
                                 "Вас вітає телеграм який допоможе краще керувати вашими фінанасами.");
        sendInlineKeyboard(message->chat->id);
    });
    bot.getEvents().onCallbackQuery([this](const TgBot::CallbackQuery::Ptr &query) {
        const std::string response = "ok :~)";
        bot.getApi().sendMessage(query->message->chat->id, response, nullptr, nullptr);
    });
}

void FinanceTrackerBot::sendInlineKeyboard(int64_t id) const {
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

    auto message = bot.getApi().sendMessage(
        id, "Виберіть позицію або декілька позицій для відслідковування ваших фінансів😊",
        nullptr, nullptr, keyboard);
}
