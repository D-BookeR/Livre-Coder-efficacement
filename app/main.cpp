#include <iostream>
#include <Game.h>
#include <ConsoleOutput.h>
#include <ConcreteInput.h>
int main()
{
    Game game;
    game.defineInputSystem(colorWhite, new ConcreteInput<ConsoleTag>(game));
    game.defineInputSystem(colorBlack, new ConcreteInput<ConsoleTag>(game));
    game.defineOutputSystem(new ConcreteOutput<ConsoleTag>(game.board()));
    game.run();
    return 0;
}
