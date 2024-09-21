
#include <iostream>
#include <memory>

// Step 1: Create a common interface for the strategy
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual void pay(int amount) const = 0;
};

// Step 2: Create concrete strategies
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paying " << amount << " using Credit Card." << std::endl;
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paying " << amount << " using PayPal." << std::endl;
    }
};

class BankTransferPayment : public PaymentStrategy {
public:
    void pay(int amount) const override {
        std::cout << "Paying " << amount << " using Bank Transfer." << std::endl;
    }
};

// Step 3: Create a context class to use the strategy
class PaymentContext {
private:
    std::unique_ptr<PaymentStrategy> strategy;

public:
    // Set the strategy dynamically
    void setPaymentStrategy(std::unique_ptr<PaymentStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    // Execute the payment process
    void pay(int amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            std::cout << "No payment method selected!" << std::endl;
        }
    }
};

// Step 4: Use the strategy pattern in the client code
int main() {
    PaymentContext context;

    // User selects to pay with PayPal
    context.setPaymentStrategy(std::make_unique<PayPalPayment>());
    context.pay(100); // Output: Paying 100 using PayPal.

    // User selects to pay with Credit Card
    context.setPaymentStrategy(std::make_unique<CreditCardPayment>());
    context.pay(200); // Output: Paying 200 using Credit Card.

    // User selects to pay with Bank Transfer
    context.setPaymentStrategy(std::make_unique<BankTransferPayment>());
    context.pay(300); // Output: Paying 300 using Bank Transfer.

    return 0;
}
// Advantages:
// Flexibility: You can add new payment methods without modifying existing code.
// Open-Closed Principle: The existing classes are not modified when a new payment method is introduced.
// Separation of Concerns: The payment logic for each method is separated into its own class, making it easier to manage.
