#include "Entity.h"

class Cube :public Entity
{
public:
    CREATE_FUNC(Cube);
    virtual bool init();
    float resetX(int i);
    void initSize(int index);
    void reset();
    void resetSize();
};
