#include "transactions/Transaction.h"

#include <utility>


Transaction::Transaction(const int64_t userId, std::string category, const double amount, const time_point date)
    : userId(userId), category(std::move(category)), amount(amount), date(date) {
}

bool Transaction::operator==(const Transaction &other) const {
    return userId == other.userId &&
           category == other.category &&
           amount == other.amount &&
           date == other.date;
}

int64_t Transaction::getUserId() const {
    return this->userId;
}

std::string Transaction::getCategory() const {
    return this->category;
}

double Transaction::getAmount() const {
    return this->amount;
}

time_point Transaction::getDate() const {
    return this->date;
}

void Transaction::setUserId(const int64_t userId) {
    this->userId = userId;
}

void Transaction::setCategory(const std::string &category) {
    this->category = category;
}

void Transaction::setAmount(const double amount) {
    if (amount < 0) {
        throw std::invalid_argument("Amount cannot be negative");
    }
    this->amount = amount;
}

void Transaction::setTimePoint(const time_point date) {
    this->date = date;
}

void Transaction::setTimePoint(const std::string &date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%d.%m.%Y");
    if (ss.fail() || tm.tm_year < 0 || tm.tm_mon < 0 || tm.tm_mday < 1) {
        throw std::invalid_argument("Invalid date format");
    }
    this->date = std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string Transaction::convertTimeToString(const time_point time) {
    const time_t time_t = std::chrono::system_clock::to_time_t(time);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%d.%m.%Y %H:%M:%S");
    return oss.str();
}

std::chrono::system_clock::time_point Transaction::convertStringToTimePoint(const std::string &timeString,
                                                                            const std::string &format) {
    std::tm tm = {};
    std::istringstream ss(timeString);
    ss >> std::get_time(&tm, format.c_str());
    if (ss.fail()) {
        throw std::invalid_argument("Invalid date format: " + timeString);
    }
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "Категорія: " << category
            << " Сума: " << std::fixed << std::setprecision(2) << amount
            << " Дата: " << convertTimeToString(date) << "\n";
    oss << "----------------------\n";
    return oss.str();
}