#ifndef CALLBACKLISTTRANSACTIONFORMONTHBYSUM_H
#define CALLBACKLISTTRANSACTIONFORMONTHBYSUM_H
#include "CallbackCommand.h"

class CallbackListTransactionForMonthBySum : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKLISTTRANSACTIONFORMONTHBYSUM_H
