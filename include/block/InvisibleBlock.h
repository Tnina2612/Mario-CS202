#include<block/BlockState.h>
#include<block/Block.h>

class InvisibleBlock : public BlockState {
private:
    Block &m_block;
    bool changeState_;
    void changeState();
public:
    InvisibleBlock(Block &m_block);
    void draw_() override;
    void update_() override;
    void onHit(Character &character) override;
    bool getJiggle() override;
    std::string getStateName() const override;
    Rectangle getDrawRec() const override;
};