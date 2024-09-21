#include <iostream>
#include <thread>
#include <mutex>

class Singleton
{
	static std::mutex mutex_;
    static Singleton* singleton_;

protected:
    Singleton(const std::string value): value_(value)
    {}

    std::string value_;
public:
    Singleton(Singleton &other) = delete;
    void operator=(const Singleton &) = delete;
    static Singleton *GetInstance(const std::string& value);
    void SomeBusinessLogic()
    {}
    std::string value() const
	{
        return value_;
    }
};

Singleton* Singleton::singleton_= nullptr;
std::mutex Singleton::mutex_;

/**
 * Static methods should be defined outside the class.
 */
Singleton *Singleton::GetInstance(const std::string& value)
{
	// thread-safe way
	std::lock_guard<std::mutex> lock(mutex_);
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if(singleton_==nullptr){
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}


int main()
{
    std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
                "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
                "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}
