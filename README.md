# Biologyn
Biologyn is an environment survival simulator. In Biologyn, fauna and flora individuals with different
characteristics are created and added to the environment, where they need to fight for survival. Fauna individuals
move around the environment in search of nutrition sources and mating partners. Some they find competitors and may
need to fight to defend their territory. There are two major groups of individuals:
- Flora (plants)
- Fauna (animals)

The fauna grops is further subdivided into:
- Carnivores
- Herbivores

These can be `male` or `female`.

Given the characteristics you give to the individuals and the environment, individuals will try to survive. Your
objective should be to create a sustainable environment, which would exist for a long period of time. At the end of
the run, you will see a report containing:
- How long the environment lasted for (in days)
- Who was the last surviving fauna individual and when they perished
- Who was the last surviving flora individual and when they perished

Note that you do not have to follow the objective above. You can simply run the environments to see how different
characteristics affect the outcome (e.g. what happens if carnivores are given too much striking power relative to
herbivores defend power, and does that environment lasts longer than some different configuration).

### Requirements
- CMake (>=3.18)
- Make (>=3.81)
- Nlohmann JSON (https://github.com/nlohmann/json)

### How to run
**Compiling**
1. In a terminal window the project's root directory, run `cmake .`
2. Ensure that a `Makefile` was created, then run `make`
3. Ensure an executable file called `biologyn` was created, then run `./biologyn`

**Loading environment**

Once the application is running, you should see in your terminal a welcome message, and a prompt to type the name of
your environment file - you simply need to enter the name of the file you created (only JSON files allowed and you
do not need to enter the extension `.json`). To run Biologyn, you have to create your own environment. This is done
by creating a JSON file in the environments directory and adding the required environment characteristics:

**JSON format/schema)**

```
{
  "axesLimits": [200, 200],
  "floraPopulation": {
    "total": 40,
    "maxDecayRate": 10
  },
  "faunaPopulation": {
    "male": {
      "herbivores": {
        "total": 20,
        "maxDecayRate": 10,
        "minAttackRate": 50,
        "minDefendRate": 50
      },
      "carnivores": {
        "total": 20,
        "maxDecayRate": 10,
        "minAttackRate": 50,
        "minDefendRate": 50
      }
    },
    "female": {
      "herbivores": {
        "total": 20,
        "maxDecayRate": 10,
        "minAttackRate": 50,
        "minDefendRate": 50
      },
      "carnivores": {
        "total": 20,
        "maxDecayRate": 10,
        "minAttackRate": 50,
        "minDefendRate": 50
      }
    }
  }
}
```

#### Parameters
Below you will find a description of each parameter contained in the JSON schema:
- `axesLimits` *(min: 1 | max: 2000)* - represents the boundaries of the environment, determining the area that
 individuals can move or be
 placed in. Larger environments/worlds mean that individuals may need to travel longer distances to find nutrition
 , making it perhaps harder to survive (this depends on invidual count as well, see below)
 - `floraPopulation`/ `faunaPopulation` - parameters pertaining to the flora/fauna populations. In the case of fauna
 , the parameters are further divided by gender (`male` / `female`) and nutrition type (`herbivore` / `carnivore`):
    - `total` *(min: 1 | max: 2000)* - represents the total count of individuals to be included in the environment
    ; higher numbers
     mean more individuals of a particular kind in the environment.
    - `maxDecayRate` *(min: 1 | max: 100)* - represents the max amount of health points that an individual will lose
     between two
     consecutive days. When an individual is created, its decay rate is determined using this parameter. You are
     able to determine the maximum decay rate, but the actual decay rate is left to chance. For example, an individual
     is created with decay `5`, which means if it started with health `100`, on the environment's second day, its
     health will be `95`; if you defined `10` as the maximum decay rate, you know that no individual can decay by
     more than `10` between two consecutive rounds (assuming no interaction with other individuals happened).
    - `minAttackRate` *(fauna only - min: 1 | max: 100)* - a number between `1` and `100` that represents
     the minimum
     striking power of an
     individual. Again, you can determine the minimum power, but during a battle, the strike is left to chance.
    - `minDefendRate` *(fauna only - min: 1 | max: 100)* - a number between `1` and `100` that represents the minimum
     defensive power of an
     individual. As it is the case with attacking rates, you determine the minimum, but the actual defensive power
      will be determine in batlle.
      
      
#### Future Features
##### Functionalities
- Fully implement mating, where offsprings are generated and added to fauna population, while inheriting
  characteristics from parents
- Add relationship between health and attacking/defending rates (lower health leading to lower ability to attack
 /defend)
- Implement water features and the concept of the need for flora/fauna individuals to search for water as part of
 nutrition cycles
- Allow flora individuals to reproduce according to some rules regarding the population of fauna available
- Allow for more variety (with perhaps defense mechanisms) for flora individuals
- Add more variation to fauna, allowing for more species with different characteristics
- Allow for irregular environment with multiple features (e.g. water)
- Add environmental characteristics determine each day, which in turn affect individuals abilities to survive (e.g
. weather, climate, soil characteristics, events)
- Implement smarter movement patterns for individuals, where perhaps they can spot other individuals and resources at
 greater distances, which would affect their movement patterns
- Add additional characteristic to individuals to make interactions more complex (e.g. cooperation between species
, grouping of same species individuals)
- Implement O2/CO2 cycles, where flora consume C02 and fauna produces it; while flora produces O2 and fauna consumes it

##### Technical
- Multithreaded application where fauna simulation happens within individual thread, and the environment class
 maintains the state to the world
- Implement GUI to allow users to see individuals moving around the environment
- Reorganize project folder structure

 
