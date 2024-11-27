#ifndef ENTERINGUPDATEHANDLER_H
#define ENTERINGUPDATEHANDLER_H
#include "TextMessage.h"

class EnteringUpdateHandler : public TextMessage{
public:
    [[nodiscard]] bool canHandle(int64_t userId, const TgBot::Message::Ptr &message) const override;

    void handleMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //ENTERINGUPDATEHANDLER_H
