#ifndef BACKCOMMAND_H
#define BACKCOMMAND_H
#include "Command.h"

class BackCommand : public Command{
public:
    void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //BACKCOMMAND_H
