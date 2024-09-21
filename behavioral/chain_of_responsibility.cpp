#include <iostream>
#include <memory>
#include <string>

// Step 1: Define the Handler interface
class SupportHandler {
protected:
    std::shared_ptr<SupportHandler> nextHandler;

public:
    virtual ~SupportHandler() = default;

    // Set the next handler in the chain
    void setNextHandler(std::shared_ptr<SupportHandler> handler) {
        nextHandler = handler;
    }

    // Handle request or pass it to the next handler
    virtual void handleRequest(const std::string& issue, int severity) {
        if (nextHandler) {
            nextHandler->handleRequest(issue, severity);
        }
    }
};

// Step 2: Create concrete handlers
class BasicSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue, int severity) override {
        if (severity <= 1) {
            std::cout << "Basic Support: Handling issue \"" << issue << "\"." << std::endl;
        } else {
            std::cout << "Basic Support: Escalating issue \"" << issue << "\"." << std::endl;
            SupportHandler::handleRequest(issue, severity);
        }
    }
};

class AdvancedSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue, int severity) override {
        if (severity == 2) {
            std::cout << "Advanced Support: Handling issue \"" << issue << "\"." << std::endl;
        } else {
            std::cout << "Advanced Support: Escalating issue \"" << issue << "\"." << std::endl;
            SupportHandler::handleRequest(issue, severity);
        }
    }
};

class ManagerSupport : public SupportHandler {
public:
    void handleRequest(const std::string& issue, int severity) override {
        if (severity >= 3) {
            std::cout << "Manager Support: Handling critical issue \"" << issue << "\"." << std::endl;
        } else {
            SupportHandler::handleRequest(issue, severity);
        }
    }
};

// Step 3: Set up the chain of responsibility
int main() {
    // Create the support handlers
    auto basicSupport = std::make_shared<BasicSupport>();
    auto advancedSupport = std::make_shared<AdvancedSupport>();
    auto managerSupport = std::make_shared<ManagerSupport>();

    // Link the handlers
    basicSupport->setNextHandler(advancedSupport);
    advancedSupport->setNextHandler(managerSupport);

    // Step 4: Test the chain with different requests
    std::cout << "Request 1: Minor issue (severity 1)" << std::endl;
    basicSupport->handleRequest("Minor issue", 1);

    std::cout << "\nRequest 2: Advanced issue (severity 2)" << std::endl;
    basicSupport->handleRequest("Advanced issue", 2);

    std::cout << "\nRequest 3: Critical issue (severity 3)" << std::endl;
    basicSupport->handleRequest("Critical issue", 3);

    return 0;
}
