/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current configuration
 * has already been generated. If this is the case, the game has reached stability and
 * must stop.
 */

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream>
#include <iomanip>
#include <string>

#include "life.cpp"

int main(int argc, char* argv[])
{   
    life::SimulationManager s;
    int r{s.readConfig()};
    if(!r){
        s.print();
        std::string reason = s.play();
        std::cout << "Fim de Jogo: " << reason << std::endl;
    }

    return r;
}
