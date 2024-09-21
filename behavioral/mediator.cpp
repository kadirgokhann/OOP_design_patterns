
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Step 1: Define the Mediator interface
class ChatMediator {
public:
    virtual ~ChatMediator() = default;
    virtual void sendMessage(const std::string& message, class User* user) = 0;
};

// Step 2: Define the User (Colleague) class
class User {
protected:
    ChatMediator& mediator;
    std::string name;

public:
    User(ChatMediator& mediator, std::string name) : mediator(mediator), name(std::move(name)) {}

    virtual ~User() = default;

    virtual void receiveMessage(const std::string& message) const {
        std::cout << name << " received: " << message << std::endl;
    }

    virtual void sendMessage(const std::string& message) {
        std::cout << name << " is sending message: " << message << std::endl;
        mediator.sendMessage(message, this);
    }

    std::string getName() const {
        return name;
    }
};

// Step 3: Create the Concrete Mediator (ChatRoom)
class ChatRoom : public ChatMediator {
private:
    std::vector<User*> users;

public:
    void addUser(User* user) {
        users.push_back(user);
    }

    void sendMessage(const std::string& message, User* sender) override {
        for (auto* user : users) {
            if (user != sender) {  // Don't send the message to the sender
                user->receiveMessage(sender->getName() + ": " + message);
            }
        }
    }
};

// Step 4: Use the Mediator pattern in the client code
int main() {
    // Create the chatroom (mediator)
    ChatRoom chatRoom;

    // Create users (colleagues)
    User user1(chatRoom, "Alice");
    User user2(chatRoom, "Bob");
    User user3(chatRoom, "Charlie");

    // Add users to the chatroom
    chatRoom.addUser(&user1);
    chatRoom.addUser(&user2);
    chatRoom.addUser(&user3);

    // Users send messages via the chatroom (mediator)
    user1.sendMessage("Hello everyone!");
    user2.sendMessage("Hi Alice!");
    user3.sendMessage("Hey folks!");

    return 0;
}
