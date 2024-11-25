#ifndef CALLBACKGETLISTTRANSACTION_H
#define CALLBACKGETLISTTRANSACTION_H
#include "CallbackCommand.h"

class CallbackGetListTransaction : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKGETLISTTRANSACTION_H
