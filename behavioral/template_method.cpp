
#include <iostream>
#include <fstream>
#include <string>

// Step 1: Define the abstract base class with the template method
class DataProcessor {
public:
    virtual ~DataProcessor() = default;

    // The template method defines the skeleton of the algorithm
    void process() {
        loadFile();
        parseData();
        outputResults();
    }

protected:
    // These steps may vary for each subclass
    virtual void loadFile() = 0;
    virtual void parseData() = 0;
    virtual void outputResults() = 0;
};

// Step 2: Create concrete classes for different file types
class TextFileProcessor : public DataProcessor {
protected:
    std::string data;

    void loadFile() override {
        std::cout << "Loading text file..." << std::endl;
        data = "Sample text data";  // Simulating file loading
    }

    void parseData() override {
        std::cout << "Parsing text data..." << std::endl;
        // Simulate parsing text (this could be more complex in a real scenario)
    }

    void outputResults() override {
        std::cout << "Outputting text results: " << data << std::endl;
    }
};

class CSVFileProcessor : public DataProcessor {
protected:
    std::string data;

    void loadFile() override {
        std::cout << "Loading CSV file..." << std::endl;
        data = "Name, Age\nAlice, 30\nBob, 25";  // Simulating file loading
    }

    void parseData() override {
        std::cout << "Parsing CSV data..." << std::endl;
        // Simulate parsing CSV (this could be more complex in a real scenario)
    }

    void outputResults() override {
        std::cout << "Outputting CSV results: " << data << std::endl;
    }
};

class JSONFileProcessor : public DataProcessor {
protected:
    std::string data;

    void loadFile() override {
        std::cout << "Loading JSON file..." << std::endl;
        data = R"({"name": "Alice", "age": 30})";  // Simulating file loading
    }

    void parseData() override {
        std::cout << "Parsing JSON data..." << std::endl;
        // Simulate parsing JSON (this could be more complex in a real scenario)
    }

    void outputResults() override {
        std::cout << "Outputting JSON results: " << data << std::endl;
    }
};

// Step 3: Use the Template Method pattern in client code
int main() {
    std::unique_ptr<DataProcessor> processor;

    // Process a text file
    std::cout << "Processing text file:" << std::endl;
    processor = std::make_unique<TextFileProcessor>();
    processor->process();  // Output: Loading, parsing, and outputting text file data

    // Process a CSV file
    std::cout << "\nProcessing CSV file:" << std::endl;
    processor = std::make_unique<CSVFileProcessor>();
    processor->process();  // Output: Loading, parsing, and outputting CSV file data

    // Process a JSON file
    std::cout << "\nProcessing JSON file:" << std::endl;
    processor = std::make_unique<JSONFileProcessor>();
    processor->process();  // Output: Loading, parsing, and outputting JSON file data

    return 0;
}
