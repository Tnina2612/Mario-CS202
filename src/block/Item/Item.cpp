#include "block/Item/Item.h"

const float scale_screen = 3.0f;
Item::Item(Vector2 pos)
    : itemTexture(LoadTexture("assets/images/items.png")), pos_(pos), frame_(0.0f), type_(0), appearAnimation(1), isDelete_(0) {}

Vector2 Item::getPos() const { return pos_; }

void Item::setPos(Vector2 pos) { pos_ = pos; }

Rectangle Item::getSourceRec() const { return rec_; }

Rectangle Item::getDrawRec() const { return {pos_.x - rec_.width * 3.0f / 2.0f, pos_.y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }

bool Item::isAppearAnimation() const { return appearAnimation; }

bool Item::isDelete() const { return isDelete_; }

void Item::draw()
{
    Rectangle dest_rec = {pos_.x, pos_.y, rec_.width * scale_screen, rec_.height * scale_screen};
    DrawTexturePro(itemTexture, rec_, dest_rec, {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);
}
