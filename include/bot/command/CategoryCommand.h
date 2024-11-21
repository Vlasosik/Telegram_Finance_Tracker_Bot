#ifndef CATEGORYCOMMAND_H
#define CATEGORYCOMMAND_H
#include "Command.h"

class CategoryCommand : public Command{
public:
    void Execute(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //CATEGORYCOMMAND_H
