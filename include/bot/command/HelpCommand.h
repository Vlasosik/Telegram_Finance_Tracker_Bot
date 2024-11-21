#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
#include "Command.h"

class HelpCommand : public Command {
public:
    void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //HELPCOMMAND_H
