
#include <iostream>
#include <vector>
#include <memory>

// Step 1: Define the Iterator interface
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

// Step 2: Create a concrete iterator for a vector
template <typename T>
class VectorIterator : public Iterator<T> {
private:
    const std::vector<T>& collection;
    size_t currentIndex = 0;

public:
    explicit VectorIterator(const std::vector<T>& collection) : collection(collection) {}

    bool hasNext() const override {
        return currentIndex < collection.size();
    }

    T next() override {
        return collection[currentIndex++];
    }
};

// Step 3: Define the Aggregate interface (collection interface)
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() const = 0;
};

// Step 4: Implement a concrete aggregate (vector-based collection)
template <typename T>
class VectorCollection : public Aggregate<T> {
private:
    std::vector<T> items;

public:
    void add(const T& item) {
        items.push_back(item);
    }

    std::unique_ptr<Iterator<T>> createIterator() const override {
        return std::make_unique<VectorIterator<T>>(items);
    }
};

// Step 5: Use the Iterator pattern in client code
int main() {
    VectorCollection<int> numbers;
    numbers.add(10);
    numbers.add(20);
    numbers.add(30);

    // Get an iterator for the collection
    auto iterator = numbers.createIterator();

    // Iterate over the collection
    while (iterator->hasNext()) {
        std::cout << "Next item: " << iterator->next() << std::endl;
    }

    return 0;
}
