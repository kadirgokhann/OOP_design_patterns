//  Example Scenario: File System
//  Component Interface
//  This interface will represent both files and directories.

#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Component
class FileSystemEntity {
public:
    virtual void showDetails(int indentation = 0) const = 0;
    virtual ~FileSystemEntity() = default;
};

//  Leaf: File
//  A file is a single object with no children.

// Leaf
class File : public FileSystemEntity {
private:
    std::string name;

public:
    File(const std::string& fileName) : name(fileName) {}

    void showDetails(int indentation = 0) const override {
        std::string indent(indentation, ' ');
        std::cout << indent << "File: " << name << std::endl;
    }
};

//  Composite: Directory
//  A directory can contain files or other directories (i.e., it can contain other components).

// Composite
class Directory : public FileSystemEntity {
private:
    std::string name;
    std::vector<std::shared_ptr<FileSystemEntity>> contents;

public:
    Directory(const std::string& dirName) : name(dirName) {}

    void add(std::shared_ptr<FileSystemEntity> entity) {
        contents.push_back(entity);
    }

    void showDetails(int indentation = 0) const override {
        std::string indent(indentation, ' ');
        std::cout << indent << "Directory: " << name << std::endl;
        for (const auto& entity : contents) {
            entity->showDetails(indentation + 4);
        }
    }
};

int main() {
    // Create files
    std::shared_ptr<FileSystemEntity> file1 = std::make_shared<File>("file1.txt");
    std::shared_ptr<FileSystemEntity> file2 = std::make_shared<File>("file2.txt");
    std::shared_ptr<FileSystemEntity> file3 = std::make_shared<File>("file3.jpg");

    // Create directories
    std::shared_ptr<Directory> homeDir = std::make_shared<Directory>("home");
    std::shared_ptr<Directory> picturesDir = std::make_shared<Directory>("pictures");

    // Add files to directories
    homeDir->add(file1);
    homeDir->add(file2);
    picturesDir->add(file3);

    // Add directory inside another directory
    homeDir->add(picturesDir);

    // Display details of the file system
    homeDir->showDetails();

    return 0;
}

//  Advantages of Composite Pattern:
//		Tree Structure Representation: It allows you to work with tree-like hierarchical structures (such as file systems, organization charts, etc.).
//  Uniformity: You can treat individual objects (files) and compositions of objects (directories) in the same way, making your code more flexible and easier to maintain.
//  Simplifies Client Code: The client can operate on both individual and composite objects uniformly.
//  When to Use the Composite Pattern:
//		When you need to represent part-whole hierarchies (like files and directories, or UI components).
//		When you want to treat individual objects and compositions of objects in a uniform manner.
