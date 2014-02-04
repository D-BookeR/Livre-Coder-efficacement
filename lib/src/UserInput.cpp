#include <UserInput.h>
#include <CommandSender.h>
UserInput::UserInput(Game & game): InputSystem(game){
}
Command const & UserInput::selectCommand(){
    return selectSender().emitCommand();
}
