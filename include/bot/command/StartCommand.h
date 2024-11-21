#ifndef STARTCOMMAND_H
#define STARTCOMMAND_H
#include "Command.h"

class StartCommand : public Command{
public:
    void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;

};
#endif //STARTCOMMAND_H
