
#include <iostream>
#include <memory>
#include <string>

// Product class
class House {
public:
    std::string walls;
    std::string roof;
    std::string windows;
    std::string doors;

    void show() {
        std::cout << "House with " << walls << " walls, " 
                  << roof << " roof, " 
                  << windows << " windows, and " 
                  << doors << " doors." << std::endl;
    }
};

// Builder interface
class HouseBuilder {
public:
    virtual ~HouseBuilder() = default;
    virtual void buildWalls() = 0;
    virtual void buildRoof() = 0;
    virtual void buildWindows() = 0;
    virtual void buildDoors() = 0;
    virtual std::unique_ptr<House> getHouse() = 0;
};

// Concrete builder for wooden houses
class WoodenHouseBuilder : public HouseBuilder {
private:
    std::unique_ptr<House> house;
public:
    WoodenHouseBuilder() {
        house = std::make_unique<House>();
    }

    void buildWalls() override {
        house->walls = "Wooden";
    }

    void buildRoof() override {
        house->roof = "Wooden Shingles";
    }

    void buildWindows() override {
        house->windows = "Wooden framed";
    }

    void buildDoors() override {
        house->doors = "Wooden doors";
    }

    std::unique_ptr<House> getHouse() override {
        return std::move(house);
    }
};

// Concrete builder for stone houses
class StoneHouseBuilder : public HouseBuilder {
private:
    std::unique_ptr<House> house;
public:
    StoneHouseBuilder() {
        house = std::make_unique<House>();
    }

    void buildWalls() override {
        house->walls = "Stone";
    }

    void buildRoof() override {
        house->roof = "Slate";
    }

    void buildWindows() override {
        house->windows = "Stone framed";
    }

    void buildDoors() override {
        house->doors = "Stone doors";
    }

    std::unique_ptr<House> getHouse() override {
        return std::move(house);
    }
};

// Director class that uses the builder
class HouseDirector {
public:
    void constructHouse(HouseBuilder& builder) {
        builder.buildWalls();
        builder.buildRoof();
        builder.buildWindows();
        builder.buildDoors();
    }
};

// Client code
int main() {
    HouseDirector director;

    // Build a wooden house
    WoodenHouseBuilder woodenBuilder;
    director.constructHouse(woodenBuilder);
    std::unique_ptr<House> woodenHouse = woodenBuilder.getHouse();
    woodenHouse->show();

    // Build a stone house
    StoneHouseBuilder stoneBuilder;
    director.constructHouse(stoneBuilder);
    std::unique_ptr<House> stoneHouse = stoneBuilder.getHouse();
    stoneHouse->show();

    return 0;
}
