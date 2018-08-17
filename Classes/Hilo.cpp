//
//  Hilo.cpp
//  ColorQueue
//
//  Created by Juan Casado Ballesteros on 8/2/18.
//

#include "Hilo.hpp"
#include <iostream>

Hilo::Hilo(){
    control.store(false,std::memory_order_seq_cst);
}

Hilo::~Hilo(){
}

bool Hilo::run(){
    if (!control.load(std::memory_order_seq_cst)){
        control.store(true,std::memory_order_seq_cst);
        hilo = std::thread(Hilo::action, this);
        return true;
    }
    return false;
}

void Hilo::action(Hilo * runnable){
    runnable->to_beguin();
    while (runnable->control.load()){
        runnable->to_do();
    }
}

void Hilo::end(){
    control.store(false,std::memory_order_seq_cst);
    to_end();
    hilo.join();
}
