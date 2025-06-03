#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(IPGarageLayer, GJGarageLayer){
    struct Fields {
        CCSprite* m_cubePreview = CCSprite::create("icon.png"_spr);
        CCSprite* m_guide = CCSprite::create("guide.png"_spr);
    };

    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto fields = m_fields.self();

        float posX = m_playerObject->getPositionX();
        float posY = m_playerObject->getPositionY();

        fields->m_cubePreview->setPosition({posX, posY});
        fields->m_cubePreview->setScale(0.88f);
        
        this->addChild(fields->m_cubePreview, -2);

        return true;
    }

    void onSelect(CCObject* iconSender) {
        GJGarageLayer::onSelect(iconSender);

        geode::log::debug("an icon was selected");

        auto fields = m_fields.self();

        float globalPosX = m_playerObject->getPositionX();
        float shipPosY = m_playerObject->getPositionY() + 16.f;
        float ufoPosY = m_playerObject->getPositionY() + 8.5f;

        auto moveToShipPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {globalPosX, shipPosY})
        );
        auto moveToUfoPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {globalPosX, ufoPosY})
        );

        if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo) {
            fields->m_cubePreview->setVisible(true);  
        } else {
            fields->m_cubePreview->setVisible(false);
        }

        if (m_selectedIconType == IconType::Ship) {
            fields->m_cubePreview->runAction(moveToShipPos);
        } else if (m_selectedIconType == IconType::Ufo) {
            fields->m_cubePreview->runAction(moveToUfoPos);
        }

    }
    
};