# Biologyn
Biologyn is an environment survival simulator, where an environment is created an different groups of individuals are
added to it. These individuals move around - if they have the ability to - in search of nutrition. When individuals
cross paths, they need to fight to survive, until no individuals are left.

### How to install
- Install nlohmann_json library for handling JSON files (https://github.com/nlohmann/json)

### How to run
 

Initialize Environment with dimensions
- Generate random number for flora and fauna
    - Iterate through using the random number
    - Generate initial position within environment
    - Generate Flora/Fauna instance initializing with initial position
    - Move instance into Environment vector
- Call Environment simulate method
    - On loop:
        - Iterate through Fauna vector
        - Call move method of each individual
            - Generate a position as long as inside environment
            - Update current position
    - 
