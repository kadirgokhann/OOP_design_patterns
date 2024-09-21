#include <iostream>
#include <string>

// Component: Defines the interface for notifications.
class Notification {
public:
    virtual void send(const std::string& message) const = 0;
    virtual ~Notification() = default;
};

// Concrete Component: Implements the basic notification behavior.
class EmailNotification : public Notification {
public:
    void send(const std::string& message) const override {
        std::cout << "Sending email: " << message << std::endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const std::string& message) const override {
        std::cout << "Sending SMS: " << message << std::endl;
    }
};

// Decorator: Base class for adding extra functionality to notifications.
class NotificationDecorator : public Notification {
protected:
    Notification* wrappedNotification;
public:
    NotificationDecorator(Notification* notification) : wrappedNotification(notification) {}
    void send(const std::string& message) const override {
        wrappedNotification->send(message);
    }

    virtual ~NotificationDecorator() {
        delete wrappedNotification;
    }
};

// Concrete Decorators: Add extra functionality.
class EncryptedNotification : public NotificationDecorator {
public:
    EncryptedNotification(Notification* notification) : NotificationDecorator(notification) {}

    void send(const std::string& message) const override {
        std::string encryptedMessage = encrypt(message);
        NotificationDecorator::send(encryptedMessage);
    }

private:
    std::string encrypt(const std::string& message) const {
        return "Encrypted(" + message + ")";
    }
};

class LoggedNotification : public NotificationDecorator {
public:
    LoggedNotification(Notification* notification) : NotificationDecorator(notification) {}

    void send(const std::string& message) const override {
        log(message);
        NotificationDecorator::send(message);
    }

private:
    void log(const std::string& message) const {
        std::cout << "[LOG]: " << message << std::endl;
    }
};

int main() {
    // Creating a simple email notification.
    Notification* email = new EmailNotification();
    email->send("Hello!");

    // Wrapping the email with encryption.
    Notification* encryptedEmail = new EncryptedNotification(email);
    encryptedEmail->send("Secret Message");

    // Wrapping the encrypted email with logging.
    Notification* loggedAndEncryptedEmail = new LoggedNotification(encryptedEmail);
    loggedAndEncryptedEmail->send("Top Secret Message");

    // Cleanup.
    delete loggedAndEncryptedEmail;

    return 0;
}
