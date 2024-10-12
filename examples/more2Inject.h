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
    static bool saveToFile(const char *fileName, const char *buf, size_t size);
    static std::string abs2absCustomPath(std::string origin, std::string dstPath);
private:
    static const char *TAG;

    static GameInstance *instance;

};

} /* More2 */

