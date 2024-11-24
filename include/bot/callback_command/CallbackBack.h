#ifndef CALLBACKBACK_H
#define CALLBACKBACK_H
#include "CallbackCommand.h"

class CallbackBack : public CallbackCommand{
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKBACK_H
