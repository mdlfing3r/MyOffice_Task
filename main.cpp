#pragma once

#include <cstdint>
#include <vector>

struct Rect
{
    int x;  //координата геометриеческого центра
    int y;  //
    int width;  
    int height;
};

class Object
{
public:
    virtual ~Object() = default;
};

class Slide
{
public:
    Slide() = default;
    virtual ~Slide() = default;
public:
    virtual void addRect(const Rect& geometry) = 0;

    virtual void group(const std::vector<std::size_t>& indexesToGroup) = 0;
    virtual void ungroup(std::size_t groupIndex) = 0;

    virtual void removeObject(std::size_t objectIndex) = 0;

    virtual void moveObject(std::size_t objectIndex, int xOffset, int yOffset) = 0;

    virtual std::size_t getObjectsCount() const = 0;
    virtual const Object& getObject(std::size_t objectIndex) const = 0;
};


int main() {


    return 0;
};