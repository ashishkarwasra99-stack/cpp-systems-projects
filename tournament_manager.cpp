#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

// Using fixed char array to avoid heap fragmentation as per Master_Resume.pdf
struct Team {
    char name[50]; 
    int seed;
    int exhaustion_factor; 
};Team playMatch(Team t1, Team t2) {
    // Basic probability calculation based on seed and fatigue
    int t1_chance = (10 - t1.seed) - t1.exhaustion_factor;
    int t2_chance = (10 - t2.seed) - t2.exhaustion_factor;
    if (t1_chance < 1) t1_chance = 1;
    if (t2_chance < 1) t2_chance = 1;

    int total = t1_chance + t2_chance;
    int roll = rand() % total;

    if (roll < t1_chance) {
        t1.exhaustion_factor += 2; // Increase fatigue after a win
        std::cout << t1.name << " DEFEATED " << t2.name << "\n";
        return t1;
    } else {
        t2.exhaustion_factor += 2;
        std::cout << t2.name << " DEFEATED " << t1.name << "\n";
        return t2;
    }
}int main() {
    srand(time(0));
    // Multi-dimensional queue array for rounds as per Master_Resume.pdf
    std::queue<Team> bracket[3]; 

    // Hardcode 4 quick mock teams for lightning simulation
    Team teams[4] = {
        {"Volleyball Titans", 1, 0},
        {"Hostel Warriors", 4, 0},
        {"Campus Kings", 2, 0},
        {"MSE Mavericks", 3, 0}
    };

    for(int i = 0; i < 4; i++) bracket[0].push(teams[i]);

    // Simulate Round 1 to Finals
    for (int round = 0; round < 2; round++) {
        std::cout << "\n--- SIMULATING ROUND " << round + 1 << " ---\n";
        while (bracket[round].size() >= 2) {
            Team t1 = bracket[round].front(); bracket[round].pop();
            Team t2 = bracket[round].front(); bracket[round].pop();
            Team winner = playMatch(t1, t2);
            bracket[round + 1].push(winner);
        }
    }

    std::cout << "\n🏆 TOURNAMENT CHAMPION: " << bracket[2].front().name << " 🏆\n";
    return 0;
}