//
//  Hilo.hpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/2/18.
//

#ifndef Hilo_hpp
#define Hilo_hpp

#include <thread>
#include <atomic>

class Hilo{
public:
    Hilo();
    ~Hilo();
    bool run(void);
    void end();
private:
    std::thread hilo;
    static void action(Hilo * runnable);
    std::atomic_bool control;
protected:
    virtual void to_do() = 0;
    virtual void to_end() = 0;
    virtual void to_beguin() = 0;
};

#endif /* Hilo_hpp */
