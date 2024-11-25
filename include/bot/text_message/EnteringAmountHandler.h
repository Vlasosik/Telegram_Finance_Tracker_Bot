#ifndef ENTERINGAMOUNTHANDLER_H
#define ENTERINGAMOUNTHANDLER_H
#include "TextMessage.h"

class EnteringAmountHandler : public TextMessage {
public:
    [[nodiscard]] bool canHandle(int64_t userId, const TgBot::Message::Ptr &message) const override;

    void handleMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //ENTERINGAMOUNTHANDLER_H
