#include <InputSystem.h>
#include <Game.h>
InputSystem::~InputSystem(){
}
void InputSystem::clear(){
}
Color InputSystem::playerColor() const {
    return game().currentColor();
}
