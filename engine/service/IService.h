#ifndef ENGINE_SERVICE_H
#define ENGINE_SERVICE_H

class IService {
public:
    virtual ~IService() = default;

    virtual void update(int dt) = 0;
};


#endif //ENGINE_SERVICE_H