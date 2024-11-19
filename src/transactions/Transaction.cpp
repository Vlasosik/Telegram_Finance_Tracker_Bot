#include "transactions/Transaction.h"

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

void Transaction::setCategory(std::string category) {
    std::vector<std::string> validCategory{
        "Food", "Housing", "Clothing and Footwear", "Transport", "Family and children",
        "Personal expenses", "Savings", "Education and development"
    };
    if (const auto it = std::ranges::find(validCategory, category); it == validCategory.end()
                                                                    || category.empty()) {
        throw std::invalid_argument("Invalid category");
    }
    this->category = std::move(category);
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
    oss << std::put_time(std::localtime(&time_t), "%d.%m.%Y");
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
    return "User ID: " + std::to_string(userId) + ", Category: " + category +
           ", Amount: " + std::to_string(amount) + ", Date: " + convertTimeToString(date);
}
