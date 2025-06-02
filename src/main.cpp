#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

class $modify(MyGarageLayer, GJGarageLayer){
    struct Fields {
        CCSprite* m_cubePreview = CCSprite::create("icon.png"_spr);
        CCSprite* m_guide = CCSprite::create("guide.png"_spr);
    };

    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto fields = m_fields.self();

        fields->m_cubePreview->setPosition({284.4f, 251.f});
        fields->m_cubePreview->setScale(0.88f);
        
        this->addChild(fields->m_cubePreview, -2);

        return true;
    }

    void onSelect(CCObject* sender) {
        GJGarageLayer::onSelect(sender);

        auto fields = m_fields.self();

        auto moveToShipPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {284.4f, 251.f})
        );
        auto moveToUfoPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {284.4f, 243.5f})
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

	void selectTab(IconType p0){
        GJGarageLayer::selectTab(p0);
        
    }
};