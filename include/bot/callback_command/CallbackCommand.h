#ifndef CALLBACKCOMMAND_H
#define CALLBACKCOMMAND_H
#include <tgbot/Bot.h>
#include "user/UserManager.h"


class CallbackCommand {
public:
    UserManager userManager;

    virtual void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) = 0;

    virtual ~CallbackCommand() = 0;
};

inline CallbackCommand::~CallbackCommand() {
}
#endif //CALLBACKCOMMAND_H
