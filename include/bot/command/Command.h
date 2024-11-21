#ifndef COMMAND_H
#define COMMAND_H
#include <tgbot/Bot.h>

class Command {
public:
    virtual void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) = 0;

    virtual ~Command();
};

inline Command::~Command() {
}
#endif //COMMAND_H
