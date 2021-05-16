#ifndef BIOLOGYN_LIVING_H
#define BIOLOGYN_LIVING_H

#include <vector>
#include <string>

class Environment;

class Living {
public:
    Living(std::string id, Environment& env, float decay_rate);

    const int getHealth();
    const std::string getId();
    std::vector<unsigned int> getCurrentLocation();

private:
    void setInitialPosition();

protected:
    const std::string _id {};
    Environment& _env;
    unsigned int _x;
    unsigned int _y;
    unsigned int _health {100};
    float _decay_rate {};

    void setHealth(int health);
};


#endif //BIOLOGYN_LIVING_H
