#include "pch.h"
#include "Game.h"

int main(int argc, char* args[])
{   
    std::unique_ptr<Application> game = std::make_unique<Game>();
    game->Run();

    return 0;
}
