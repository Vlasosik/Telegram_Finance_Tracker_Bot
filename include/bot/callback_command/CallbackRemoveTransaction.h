#ifndef CALLBACKREMOVETRANSACTION_H
#define CALLBACKREMOVETRANSACTION_H
#include "CallbackCommand.h"

class CallbackRemoveTransaction : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKREMOVETRANSACTION_H
