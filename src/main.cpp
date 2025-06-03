#include <Geode/modify/GJGarageLayer.hpp>
#include "Geode/utils/cocos.hpp"
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

using namespace geode::prelude;

class $modify(IPGarageLayer, GJGarageLayer){
    struct Fields {
        SimplePlayer* m_previewPlayer = SimplePlayer::create(0);
    };

    static void onModify(auto& self) {
        (void) self.setHookPriorityBeforePre("GJGarageLayer::onSelect", "hiimjustin000.more_icons");
    }

    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto fields = m_fields.self();
        auto gameManager = GameManager::sharedState();
        auto lastSelectedIcon = gameManager->m_playerIconType;

        float posX = m_playerObject->getPositionX();
        float posY = m_playerObject->getPositionY();
        float sPosY = m_playerObject->getPositionY() + 16.f;
        float uPosY = m_playerObject->getPositionY() + 8.5f;

        if (lastSelectedIcon == IconType::Ship || lastSelectedIcon == IconType::Ufo) {
            fields->m_previewPlayer->setVisible(true);
        } else {
            fields->m_previewPlayer->setVisible(false);
        }

        if (lastSelectedIcon == IconType::Ship) {
            fields->m_previewPlayer->setPosition({posX, sPosY});
        } else if (lastSelectedIcon == IconType::Ufo) {
            fields->m_previewPlayer->setPosition({posX, uPosY});
        } else {
            fields->m_previewPlayer->setPosition({posX, posY + 20.f});
        }

        fields->m_previewPlayer->setScale(0.88f);

        fields->m_previewPlayer->updatePlayerFrame(gameManager->getPlayerFrame(), IconType::Cube);
        MoreIcons::updateSimplePlayer(fields->m_previewPlayer, IconType::Cube);
        fields->m_previewPlayer->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
        fields->m_previewPlayer->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
        fields->m_previewPlayer->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        fields->m_previewPlayer->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        if (!gameManager->getPlayerGlow()) {
            fields->m_previewPlayer->disableGlowOutline();
        }
        
        this->addChild(fields->m_previewPlayer, -1);

        return true;
    }

    void onSelect(CCObject* iconSender) {
        GJGarageLayer::onSelect(iconSender);

        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();
        auto btn = static_cast<CCMenuItemSpriteExtra*>(iconSender);

        if (m_selectedIconType == IconType::Cube) {
            fields->m_previewPlayer->updatePlayerFrame(manager->getPlayerFrame(), IconType::Cube);
            MoreIcons::updateSimplePlayer(fields->m_previewPlayer, IconType::Cube);
            fields->m_previewPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
            fields->m_previewPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
            fields->m_previewPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
            fields->m_previewPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
            if (!manager->getPlayerGlow()) {
                fields->m_previewPlayer->disableGlowOutline();
            }
        }

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
            fields->m_previewPlayer->setVisible(true);  
        } else {
            fields->m_previewPlayer->setVisible(false);
        }

        if (m_selectedIconType == IconType::Ship) {
            fields->m_previewPlayer->runAction(moveToShipPos);
        } else if (m_selectedIconType == IconType::Ufo) {
            fields->m_previewPlayer->runAction(moveToUfoPos);
        }

    }
    
};