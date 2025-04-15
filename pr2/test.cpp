#include <gtest/gtest.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "pch.h"

// ==================== Logger (Singleton) Implementation ====================
class Logger {
private:
    static Logger* instance;

    // Private constructor
    Logger() {}

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger* getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void logInfo(const std::string& msg) {
        std::cout << "[INFO] " << msg << std::endl;
    }

    void logWarning(const std::string& msg) {
        std::cout << "[WARNING] " << msg << std::endl;
    }

    void logError(const std::string& msg) {
        std::cout << "[ERROR] " << msg << std::endl;
    }
};

// Initialize static member
Logger* Logger::instance = nullptr;

// ==================== BankAccount Implementation ====================
class BankAccount {
private:
    double balance;

public:
    BankAccount() : balance(0.0) {}

    void deposit(double amount) {
        if (amount < 0) throw std::invalid_argument("Cannot deposit negative amount");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount < 0) throw std::invalid_argument("Cannot withdraw negative amount");
        if (amount > balance) throw std::runtime_error("Insufficient balance");
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }
};

// ==================== Test Cases ====================

// Logger Tests
TEST(LoggerTest, SingletonInstanceShouldBeSame) {
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();
    EXPECT_EQ(logger1, logger2);
}

TEST(LoggerTest, LogInfoMessage) {
    Logger* logger = Logger::getInstance();
    testing::internal::CaptureStdout();
    logger->logInfo("Logging info");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("[INFO] Logging info"), std::string::npos);
}

// BankAccount Tests
TEST(BankAccountTest, InitialBalanceShouldBeZero) {
    BankAccount account;
    EXPECT_EQ(account.getBalance(), 0.0);
}

TEST(BankAccountTest, DepositIncreasesBalance) {
    BankAccount account;
    account.deposit(100.0);
    EXPECT_EQ(account.getBalance(), 100.0);
}

TEST(BankAccountTest, WithdrawDecreasesBalance) {
    BankAccount account;
    account.deposit(200.0);
    account.withdraw(50.0);
    EXPECT_EQ(account.getBalance(), 150.0);
}

// ==================== Main Function ====================
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}