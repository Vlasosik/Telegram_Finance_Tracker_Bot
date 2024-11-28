#ifndef INFOCOMMAND_H
#define INFOCOMMAND_H
#include "MessageCommand.h"

class InfoMessageCommand : public MessageCommand {
public:
    void ExecuteMessage(TgBot::Bot &bot, const TgBot::Message::Ptr &message) override;
};
#endif //INFOCOMMAND_H
