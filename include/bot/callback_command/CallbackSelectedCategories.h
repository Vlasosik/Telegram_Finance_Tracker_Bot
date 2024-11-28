#ifndef CALLBACKSELECTEDCATEGORIES_H
#define CALLBACKSELECTEDCATEGORIES_H
#include "CallbackCommand.h"

class CallbackSelectedCategories : public CallbackCommand {
public:
    void ExecuteCallback(TgBot::Bot &bot, const TgBot::CallbackQuery::Ptr &query) override;
};
#endif //CALLBACKSELECTEDCATEGORIES_H
