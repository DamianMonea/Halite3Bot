#include "hlt/game.hpp"
#include "hlt/constants.hpp"
#include "hlt/log.hpp"

#include <random>
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;
using namespace hlt;

/*

    Reward list:
        -good move: + 1pt
        -bad move: -1pt
        -win: + nr halite
        -lost: -(nr halite of enemy)
        -dropoff: + (nr halite) / 100
    
*/

int main(int argc, char* argv[]) {
    unsigned int rng_seed;
    ofstream output;
    output.open("test.txt");

    if (argc > 1) {
        rng_seed = static_cast<unsigned int>(stoul(argv[1]));
    } else {
        rng_seed = static_cast<unsigned int>(time(nullptr));
    }
    mt19937 rng(rng_seed);

    Game game;
    int i, j;
    int n = game.game_map->width;
    int m = game.game_map->height;
    int bestClusterX, bestCluserY, scnBestCluserX, scndBestClusterY;
    int maxHalite = -1, scndMaxhalite = -1;
    int myX, myY, enemyX, enemyY;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            output<<game.game_map->cells[i][j].halite<<" ";
        }
        output<<endl;
    }

    // for (i = 0; i < n; i++) {
    //     for (j = 0; j < m; j++) {
    //         if (game.game_map->cells[i][j].structure->id == -1) {
    //             output<<game.game_map->cells[i][j].position.x<<" "<<game.game_map->cells[i][j].position.y<<endl;
    //         }
    //     }
    // }

    output.close();

    // At this point "game" variable is populated with initial map data.
    // This is a good place to do computationally expensive start-up pre-processing.
    // As soon as you call "ready" function below, the 2 second per turn timer will start.
    game.ready("MyCppBot");

    log::log("Successfully created bot! My Player ID is " + to_string(game.my_id) + ". Bot rng seed is " + to_string(rng_seed) + ".");

    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        unique_ptr<GameMap>& game_map = game.game_map;

        vector<Command> command_queue;

        for (const auto& ship_iterator : me->ships) {
            shared_ptr<Ship> ship = ship_iterator.second;
            if (game_map->at(ship)->halite < constants::MAX_HALITE / 10 || ship->is_full()) {
                Direction random_direction = Direction::NORTH;//ALL_CARDINALS[rng() % 4];
                command_queue.push_back(ship->move(random_direction));
            } else {
                command_queue.push_back(ship->stay_still());
            }
        }

        if (
            game.turn_number <= 200 &&
            me->halite >= constants::SHIP_COST &&
            !game_map->at(me->shipyard)->is_occupied())
        {
            command_queue.push_back(me->shipyard->spawn());
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }

    return 0;
}
