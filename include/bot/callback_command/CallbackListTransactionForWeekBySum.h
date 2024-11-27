#ifndef CALLBACKLISTTRANSACTIONFORWEEKBYSUM_H
#define CALLBACKLISTTRANSACTIONFORWEEKBYSUM_H
#include "CallbackCommand.h"

class CallbackListTransactionForWeekBySum : public CallbackCommand{
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKLISTTRANSACTIONFORWEEKBYSUM_H
