#ifndef INFOCOMMAND_H
#define INFOCOMMAND_H
#include "Command.h"

class InfoCommand : public  Command{
public:
    void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //INFOCOMMAND_H
