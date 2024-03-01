#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include <set>
#include <memory>

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
    Object(const Rect RectParams);
    Rect Params;
    bool GroupedState;
};

class Slide
{
public:
    Slide() = default;
    virtual ~Slide() = default;
    virtual void addRect(const Rect& geometry) = 0;  //Добавить прямоугольник

    virtual void group(const std::vector<std::size_t>& indexesToGroup) = 0; //группировка элементов с индексами indexesToGroup
    virtual void ungroup(std::size_t groupIndex) = 0; //разгруппировать элемент groupIndex

    virtual void removeObject(std::size_t objectIndex) = 0;

    virtual void moveObject(std::size_t objectIndex, int xOffset, int yOffset) = 0; //Перемещение объекта по слайду
                                                                                    // (возможно объект выйдет из группы после перемещения

    virtual std::size_t getObjectsCount() const = 0;  //Возвращает количество объектов  
    virtual const Object& getObject(std::size_t objectIndex) const = 0;


};


class Page : public Slide
{
typedef uint64_t index;

public:
    virtual void addRect(const Rect& geometry) override;
    virtual void group(const std::vector<std::size_t>& indexesToGroup) override; //группировка элементов с индексами indexesToGroup
    virtual void ungroup(std::size_t groupIndex) override; //разгруппировать элемент groupIndex
    virtual void removeObject(std::size_t objectIndex) override;
    virtual void moveObject(std::size_t objectIndex, int xOffset, int yOffset) override; //Перемещение объекта по слайду
    virtual std::size_t getObjectsCount() const override;  //Возвращает количество объектов  
    virtual const Object& getObject(std::size_t objectIndex) const override;

    std::map<index, Object> _Objects;  //Объекты на странице

    static index cur_index;
};



void Page::addRect(const Rect& geometry)
{
    _Objects.emplace({++cur_index, *(std::make_unique<Object>(Object(geometry) });
}

void Page::group(const std::vector<std::size_t>& indexesToGroup)
{
    for (auto& elemIndex : indexesToGroup) {
        _Objects.at(elemIndex).GroupedState = true;
    }

}

void Page::ungroup(std::size_t groupIndex)
{
    for (auto& elemNum : indexesToGroup) {
        _Objects.at(elemNum).GroupedState = false;
    }
}

void Page::removeObject(std::size_t objectIndex)
{
    _Objects.erase(objectIndex);
}

void Page::moveObject(std::size_t objectIndex, int xOffset, int yOffset)
{
    _Objects.at(objectIndex).Params.x += xOffset;
    _Objects.at(objectIndex).Params.y += yOffset;
}

std::size_t Page::getObjectsCount() const
{
    return _Objects.size();
}

const Object& Page::getObject(std::size_t objectIndex) const
{
    auto it = _Objects.at(objectIndex);
    if (it != _Objects.end())
        return it;
    else {
        //возвращаем -1 чтобы понять что валидного объекта с таким индексом нет
        return -1;
    }
};



Object::Object(const Rect RectParams) : Params(RectParams)
{
}





int main() {
    std::unique_ptr<Page>pPage(std::make_unique(new Page())) ;
    

    return 0;
};