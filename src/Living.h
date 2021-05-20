#ifndef BIOLOGYN_LIVING_H
#define BIOLOGYN_LIVING_H

#include <vector>
#include <string>

constexpr int MAX_HEALTH = 500;

class Environment;

class Living {
public:
    static const int MAX_HEALTH {500};
    Living(std::string id, Environment& env, unsigned int decay_rate);

    std::string getId();
    unsigned int getAge();
    unsigned int getHealth();
    std::vector<unsigned int> getCurrentLocation();

    void transferHealth(Living& predator);
    void decay();

private:
    void setInitialPosition();

protected:
    const std::string _id {};
    Environment& _env;
    unsigned int _x;
    unsigned int _y;
    unsigned int _age {0};
    unsigned int _health {MAX_HEALTH};
    unsigned int _decay_rate {};

    void incrementAge();
    void setHealth(int health);
};


#endif //BIOLOGYN_LIVING_H
