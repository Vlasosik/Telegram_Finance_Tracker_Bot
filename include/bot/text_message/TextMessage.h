#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H
#include <tgbot/Bot.h>

class TextMessage {
public:

    [[nodiscard]] virtual bool canHandle(int64_t userId, const TgBot::Message::Ptr &message) const = 0;
    virtual void handleMessage(TgBot::Bot& bot, const TgBot::Message::Ptr& message) = 0;

    virtual ~TextMessage();
};
inline TextMessage::~TextMessage() {
}
#endif //TEXTMESSAGE_H
