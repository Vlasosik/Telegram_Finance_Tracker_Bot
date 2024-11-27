#ifndef CALLBACKUPDATETRANSACTION_H
#define CALLBACKUPDATETRANSACTION_H
#include "CallbackCommand.h"

class CallbackUpdateTransaction : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKUPDATETRANSACTION_H
