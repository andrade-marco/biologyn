#ifndef BIOLOGYN_LIVING_H
#define BIOLOGYN_LIVING_H

#include <vector>
#include <string>

constexpr int MAX_HEALTH = 500;

class Environment;

class Living {
public:
    static const unsigned int MAX_HEALTH {500};
    Living(std::string id, Environment& env, unsigned int decay_rate);

    const int getHealth();
    const std::string getId();
    std::vector<unsigned int> getCurrentLocation();
    void decay();

private:
    void setInitialPosition();

protected:
    const std::string _id {};
    Environment& _env;
    unsigned int _x;
    unsigned int _y;
    unsigned int _health {MAX_HEALTH};
    unsigned int _decay_rate {};

    void setHealth(int health);
};


#endif //BIOLOGYN_LIVING_H
