#ifndef CALLBACKAVAILABLEСATEGORIES_H
#define CALLBACKAVAILABLEСATEGORIES_H
#include "CallbackCommand.h"

class CallbackAvailableCategories : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};

#endif //CALLBACKAVAILABLEСATEGORIES_H
