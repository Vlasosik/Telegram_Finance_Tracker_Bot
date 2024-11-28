#ifndef CALLBACKCATEGORYMANAGEMENT_H
#define CALLBACKCATEGORYMANAGEMENT_H
#include "CallbackCommand.h"

class CallbackCategoryManagement : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKCATEGORYMANAGEMENT_H
