#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <tgbot/Bot.h>

class UIManager {
public:
    static void sendMainBar(const TgBot::Bot &bot, int64_t userId, int32_t messageId = 0);

    static void sendCategoryBar(const TgBot::Bot &bot, int64_t userId, int32_t messageId);

    static void sendCategoryManagementBar(const TgBot::Bot &bot, int64_t userId, int32_t messageId);

    static void sendReportTransactionBar(const TgBot::Bot &bot, int64_t userId,int32_t messageId);
};
#endif //UIMANAGER_H
