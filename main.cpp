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
    try {
        for (auto& elemIndex : indexesToGroup) {
            try {
                _Objects.at(elemIndex).GroupedState = true;
            }
            catch (std::exception& ex) {
                std::cout << "Got some issue with grouping at " << elemIndex << "index";
            }
    }
    catch (std::exception& ex) {
        std::cout << "Got some issue with grouping, err subscr: " << ex.what()
    }

}

void Page::ungroup(std::size_t groupIndex)
{
    try {
        _Objects.at(elemNum).GroupedState = false;
    }
    catch (std::exception& ex) {
        std::cout << "Got some issue with ungrouping elem with index" << groupIndex << ", err subscr : " << ex.what()

    }

void Page::removeObject(std::size_t objectIndex)
{
    try {
        _Objects.erase(objectIndex);
    }
    catch (std::exception& ex) {
        std::cout << "Got some issue with removing object at " << objectIndex << " index, err subscr: " << ex.what()
    }
}

void Page::moveObject(std::size_t objectIndex, int xOffset, int yOffset)
{
    try {
        _Objects.at(objectIndex).Params.x += xOffset;
        _Objects.at(objectIndex).Params.y += yOffset;
    }
    catch (std::exception& ex) {
        std::cout << "Got some issue with moving object at " << objectIndex << " index, offset (" << xOffset << ";" << yOffset << ")" << "err subscr :" << ex.what()

    }

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
        std::cout << "Got some issue with getting Object, at " << objectIndex << " index, err subscr :" << ex.what()
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