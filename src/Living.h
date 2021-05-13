#ifndef BIOLOGYN_LIVING_H
#define BIOLOGYN_LIVING_H

#include <vector>

class Environment;

class Living {
public:
    Living(Environment& env, float decay_rate);

    const int getHealth();
    std::vector<unsigned int> getCurrentLocation();
private:
    Environment& _env;
    unsigned int _x;
    unsigned int _y;
    unsigned int _health {100};
    float _decay_rate {};

    void setHealth(int health);
    void setInitialPosition();
};


#endif //BIOLOGYN_LIVING_H
