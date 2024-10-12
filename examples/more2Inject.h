#pragma once

namespace More2 {

class GameInstance {

public:
    static GameInstance &getInstance()
    {
        if(!instance)
            instance = new GameInstance;
        return *instance;
    }

    static const char *getTag() { return TAG; }
    
private:
    static const char *TAG;

    static GameInstance *instance;

};

} /* More2 */

