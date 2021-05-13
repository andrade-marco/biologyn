#include "Fauna.h"

Fauna::Fauna(Environment &env, NutritionType type, Gender gender, float decay_rate, float fertility)
    : Living(env, decay_rate), _type{type}, _gender{gender}, _fertility{fertility} {};