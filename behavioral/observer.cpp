#include <iostream>
#include <vector>
#include <memory>

// Step 1: Define the Observer interface
class StockObserver {
public:
    virtual ~StockObserver() = default;
    virtual void update(float price) = 0;
};

// Step 2: Define the Subject (Stock) class
class Stock {
private:
    std::vector<std::shared_ptr<StockObserver>> observers;
    float price;

public:
    // Register an observer
    void attach(std::shared_ptr<StockObserver> observer) {
        observers.push_back(observer);
    }

    // Unregister an observer
    void detach(std::shared_ptr<StockObserver> observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Notify all observers about price change
    void notify() {
        for (auto& observer : observers) {
            observer->update(price);
        }
    }

    // Set the price and notify observers
    void setPrice(float newPrice) {
        price = newPrice;
        notify();
    }

    float getPrice() const {
        return price;
    }
};

// Step 3: Implement concrete observers
class TradingAlgorithm : public StockObserver {
public:
    void update(float price) override {
        std::cout << "Trading Algorithm reacting to stock price: " << price << std::endl;
        // Implement trading logic here
    }
};

class UserInterface : public StockObserver {
public:
    void update(float price) override {
        std::cout << "User Interface updating with new stock price: " << price << std::endl;
        // Update the UI with the new price
    }
};

class Logger : public StockObserver {
public:
    void update(float price) override {
        std::cout << "Logger recording new stock price: " << price << std::endl;
        // Log the price change
    }
};

// Step 4: Use the Observer pattern in client code
int main() {
    Stock stock;

    // Create observers
    std::shared_ptr<TradingAlgorithm> algo = std::make_shared<TradingAlgorithm>();
    std::shared_ptr<UserInterface> ui 	   = std::make_shared<UserInterface>();
    std::shared_ptr<Logger> logger 		   = std::make_shared<Logger>();

    // Attach observers to the stock
    stock.attach(algo);
    stock.attach(ui);
    stock.attach(logger);

    // Change stock price
    stock.setPrice(100.5f); // All observers will be notified
    stock.setPrice(105.7f); // All observers will be notified

    return 0;
}

//  How it works:
//  The Stock class represents the subject, which maintains a list of observers.
//  The StockObserver interface ensures that all observers have an update method to handle notifications.
//  Concrete observers (TradingAlgorithm, UserInterface, Logger) implement the update method with custom logic for how they should react to stock price changes.
//  When the stock price is updated, all observers are automatically notified.
//  Advantages:
//  Loose coupling: The subject does not need to know the details of its observers, and adding new observers or removing existing ones doesn’t require changing the subject.
//  Scalability: You can add as many observers as needed without modifying the core logic of the subject.
//  Real-time updates: Observers are immediately notified when the subject’s state changes.
