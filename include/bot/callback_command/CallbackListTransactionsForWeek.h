#ifndef CALLBACKLISTTRANSACTIONSFORWEEK_H
#define CALLBACKLISTTRANSACTIONSFORWEEK_H
#include "CallbackCommand.h"

class CallbackListTransactionsForWeek : public CallbackCommand{
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKLISTTRANSACTIONSFORWEEK_H
