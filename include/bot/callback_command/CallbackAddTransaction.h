#ifndef CALLBACKADDTRANSACTION_H
#define CALLBACKADDTRANSACTION_H
#include "CallbackCommand.h"

class CallbackAddTransaction : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKADDTRANSACTION_H
