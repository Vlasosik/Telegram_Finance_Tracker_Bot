#ifndef CALLBACKHELP_H
#define CALLBACKHELP_H
#include "CallbackCommand.h"

class CallbackHelp : public CallbackCommand{
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKHELP_H
