#ifndef ENTERINGREMOVEHANDLER_H
#define ENTERINGREMOVEHANDLER_H
#include "TextMessage.h"

class EnteringRemoveHandler : public TextMessage{
public:
    [[nodiscard]] bool canHandle(int64_t userId, const TgBot::Message::Ptr &message) const override;

    void handleMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //ENTERINGREMOVEHANDLER_H
