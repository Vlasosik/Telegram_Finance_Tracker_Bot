#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <tgbot/Bot.h>

class UIManager {
public:
    static void sendMainBar(const TgBot::Bot &bot, int64_t userId);

    static void sendCategoryBar(const TgBot::Bot &bot, int64_t userId);

    static void sendCategoryManagementBar(const TgBot::Bot &bot, int64_t userId);

    static void sendReportTransactionBar(const TgBot::Bot &bot, int64_t userId);
};
#endif //UIMANAGER_H
