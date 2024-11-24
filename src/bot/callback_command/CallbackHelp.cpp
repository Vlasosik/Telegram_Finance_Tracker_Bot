#include "bot/callback_command/CallbackHelp.h"

void CallbackHelp::ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) {
    bot.getApi().sendMessage(query->message->chat->id,
                             "Цей бот допомагає вам вести облік витрат і категорій, створювати фінансові звіти та"
                             " аналізувати свої фінанси для кращого планування бюджету🤓📝\n"
                             "Використовуйте цього бота для відстеження витрат, автоматичного підрахунку звітів та "
                             "управління своїми фінансами, щоб досягти фінансової стабільності💪🏻✨");
};
