#ifndef CALLBACKREPORTTRANSACTION_H
#define CALLBACKREPORTTRANSACTION_H
#include "CallbackCommand.h"

class CallbackReportTransaction : public CallbackCommand{
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKREPORTTRANSACTION_H
