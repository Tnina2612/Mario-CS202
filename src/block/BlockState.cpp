#include "block/BlockState.h"

Rectangle BlockState::getSourceRec() const { return rec_; }

bool BlockState::getIsDelete() const { return false; }