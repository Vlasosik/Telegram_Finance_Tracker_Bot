#ifndef CALLBACKLISTTRANSACTIONFORMONTH_H
#define CALLBACKLISTTRANSACTIONFORMONTH_H
#include "CallbackCommand.h"

class CallbackListTransactionForMonth : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKLISTTRANSACTIONFORMONTH_H
