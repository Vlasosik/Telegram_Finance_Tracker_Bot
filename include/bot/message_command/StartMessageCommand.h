#ifndef STARTCOMMAND_H
#define STARTCOMMAND_H
#include "MessageCommand.h"

class StartMessageCommand : public MessageCommand{
public:
    void ExecuteMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;

};
#endif //STARTCOMMAND_H
