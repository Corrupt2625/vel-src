#pragma once
#import <iostream>

class state(){
  private:
    uintptr_t rbxstate
  public:
    uintptr_t return_state(){
      return rbxstate();
    }
    void set_state(uintptr_t rbx){
      rbx=rbx;
    }
}

void CALLCHECK_INSTANTIATED(state rbx);
