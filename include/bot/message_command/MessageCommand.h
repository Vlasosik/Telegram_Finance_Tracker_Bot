#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H
#include <tgbot/Bot.h>

class MessageCommand {
public:
    virtual void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) = 0;
    virtual  ~MessageCommand();
};

inline MessageCommand::~MessageCommand() {
}
#endif //COMMANDMESSAGE_H
