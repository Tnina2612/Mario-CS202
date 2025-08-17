#pragma once
#include<block/Item/AnimationItem.h>

class ItemAnimation {
    protected:
        AnimationItem* item;
    public:
        ItemAnimation(AnimationItem* item);
        virtual void update(void) = 0;
        virtual bool isDone(void) const = 0;
        virtual std::string getType(void) const = 0;
        virtual void saveToFile(ostream& os) const = 0;
        virtual ~ItemAnimation() = default;
};

class ItemDownAnimation : public ItemAnimation {
        const float velocityY = 64.f;
        const float targetY;
    public:
        ItemDownAnimation(AnimationItem* item, float targetY);
        void update(void) override;
        bool isDone(void) const override;
        std::string getType(void) const override;
        void saveToFile(ostream& os) const override;
};