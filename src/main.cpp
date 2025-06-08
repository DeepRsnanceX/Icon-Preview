#include <Geode/modify/GJGarageLayer.hpp>
#include "Geode/utils/cocos.hpp"
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>

// -- JETPACK PREVIEW INFO --
//X: +6 -------> 9
//Y: +4 -------> 6
//SCALE: 0.6 --> 0.9

using namespace geode::prelude;

auto doGlowFix = Mod::get()->getSettingValue<bool>("glow-fix");

$on_mod(Loaded) {
    listenForSettingChanges("glow-fix", [](bool value) {
        doGlowFix = value;
    });
}

class $modify(IPGarageLayer, GJGarageLayer){
    struct Fields {
        SimplePlayer* m_previewPlayer = SimplePlayer::create(0);
        SimplePlayer* m_secondPreview = SimplePlayer::create(0); //xdd
        SimplePlayer* fakeGlowDisplay = SimplePlayer::create(0);
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
        float jPosX = m_playerObject->getPositionX() + 9.f;
        float jPosY = m_playerObject->getPositionY() + 6.f;

        float jetpackCubeScale = 0.9f;

        if (lastSelectedIcon == IconType::Ship || lastSelectedIcon == IconType::Ufo || lastSelectedIcon == IconType::Jetpack) {
            fields->m_previewPlayer->setVisible(true);
        } else {
            fields->m_previewPlayer->setVisible(false);
        }

        if (lastSelectedIcon == IconType::Ship) {
            fields->m_previewPlayer->setPosition({posX, sPosY});
            fields->m_previewPlayer->setScale(0.88f);

        } else if (lastSelectedIcon == IconType::Ufo) {
            fields->m_previewPlayer->setPosition({posX, uPosY});
            fields->m_previewPlayer->setScale(0.88f);

        } else if (lastSelectedIcon == IconType::Jetpack) {
            fields->m_previewPlayer->setPosition({jPosX, jPosY});
            fields->m_previewPlayer->setScale(jetpackCubeScale);
            
        } else {
            fields->m_previewPlayer->setPosition({posX, posY + 20.f});
        }

        fields->m_previewPlayer->updatePlayerFrame(gameManager->getPlayerFrame(), IconType::Cube);
        MoreIcons::updateSimplePlayer(fields->m_previewPlayer, IconType::Cube);
        fields->m_previewPlayer->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
        fields->m_previewPlayer->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
        fields->m_previewPlayer->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        fields->m_previewPlayer->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
        if (!gameManager->getPlayerGlow()) {
            fields->m_previewPlayer->disableGlowOutline();
        }

        if (doGlowFix) {
            
            fields->fakeGlowDisplay->setPosition({posX, posY});
            fields->fakeGlowDisplay->setID("fake-glow-display"_spr);

            if (lastSelectedIcon == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(gameManager->getPlayerShip(), IconType::Ship);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ship);
                fields->fakeGlowDisplay->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                if (!gameManager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (lastSelectedIcon == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(gameManager->getPlayerBird(), IconType::Ufo);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ufo);
                fields->fakeGlowDisplay->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                if (!gameManager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (lastSelectedIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                fields->fakeGlowDisplay->updatePlayerFrame(gameManager->getPlayerJetpack(), IconType::Jetpack);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Jetpack);
                fields->fakeGlowDisplay->setColor(gameManager->colorForIdx(gameManager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(gameManager->colorForIdx(gameManager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(gameManager->colorForIdx(gameManager->getPlayerGlowColor()));
                if (!gameManager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            }

            fields->fakeGlowDisplay->m_firstLayer->setOpacity(0);
            fields->fakeGlowDisplay->m_secondLayer->setVisible(false);
            fields->fakeGlowDisplay->m_birdDome->setVisible(false);
            fields->fakeGlowDisplay->m_detailSprite->setVisible(false);

            if (lastSelectedIcon == IconType::Ship || lastSelectedIcon == IconType::Ufo || lastSelectedIcon == IconType::Jetpack) {
                if (gameManager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->setVisible(true);
                    fields->fakeGlowDisplay->m_outlineSprite->setVisible(true);
                    m_playerObject->m_outlineSprite->setVisible(false);
                } else {
                    fields->fakeGlowDisplay->setVisible(false);
                }
            }
            
            this->addChild(fields->fakeGlowDisplay, -2);
        }

        fields->m_previewPlayer->setID("preview-simpleplayer"_spr);
        this->addChild(fields->m_previewPlayer, -1);

        return true;
    }

    void updatePlayerColors() {
        GJGarageLayer::updatePlayerColors();
        // THANK FUCKING GOD FOR THIS FUNCTION I DON'T HAVE TO DO A BUNCH OF SHIT TO UPDATE ON PALETTE-MENU-THINGY-WHATEVER CLOSING :yas:

        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();
        auto lastChosenIcon = manager->m_playerIconType;

        fields->m_previewPlayer->updatePlayerFrame(manager->getPlayerFrame(), IconType::Cube);
        MoreIcons::updateSimplePlayer(fields->m_previewPlayer, IconType::Cube);
        fields->m_previewPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
        fields->m_previewPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
        fields->m_previewPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
        fields->m_previewPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
        if (!manager->getPlayerGlow()) {
            fields->m_previewPlayer->disableGlowOutline();
        }

        if (doGlowFix) {

            if (m_selectedIconType == IconType::Ship || lastChosenIcon == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerShip(), IconType::Ship);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ship);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (m_selectedIconType == IconType::Ufo || lastChosenIcon == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerBird(), IconType::Ufo);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ufo);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (m_selectedIconType == IconType::Jetpack || lastChosenIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerJetpack(), IconType::Jetpack);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Jetpack);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            }

            fields->fakeGlowDisplay->m_firstLayer->setOpacity(0);
            fields->fakeGlowDisplay->m_secondLayer->setVisible(false);
            fields->fakeGlowDisplay->m_birdDome->setVisible(false);
            fields->fakeGlowDisplay->m_detailSprite->setVisible(false);

            if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo || m_selectedIconType == IconType::Jetpack || lastChosenIcon == IconType::Ship || lastChosenIcon == IconType::Ufo || lastChosenIcon == IconType::Jetpack) {
                if (manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->setVisible(true);
                    fields->fakeGlowDisplay->m_outlineSprite->setVisible(true);
                    m_playerObject->m_outlineSprite->setVisible(false);
                }
            } else {
                fields->fakeGlowDisplay->setVisible(false);
                m_playerObject->m_outlineSprite->setVisible(manager->getPlayerGlow());
            }

            if (m_selectedIconType == IconType::Jetpack || lastChosenIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
            } else {
                fields->fakeGlowDisplay->setScale(1.6f);
            }

        }

    }

    void onSelect(CCObject* iconSender) {
        GJGarageLayer::onSelect(iconSender);

        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();

        auto lastIcon = manager->m_playerIconType;
        bool dontHideOnSpecials = m_selectedIconType == IconType::Special || m_selectedIconType == IconType::DeathEffect || m_selectedIconType == IconType::ShipFire;
        bool validLastIcon = lastIcon == IconType::Ship || lastIcon == IconType::Ufo || lastIcon == IconType::Jetpack;

        float globalPosX = m_playerObject->getPositionX();
        float globalPosY = m_playerObject->getPositionY();
        float shipPosY = m_playerObject->getPositionY() + 16.f;
        float ufoPosY = m_playerObject->getPositionY() + 8.5f;
        float jetpackPosX = m_playerObject->getPositionX() + 9.f;
        float jetpackPosY = m_playerObject->getPositionY() + 6.f;
        float jetpackScale = 0.9f;

        // this runs on selecting any mode just to make sure it updates properly
        fields->m_previewPlayer->updatePlayerFrame(manager->getPlayerFrame(), IconType::Cube);
        MoreIcons::updateSimplePlayer(fields->m_previewPlayer, IconType::Cube);
        fields->m_previewPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
        fields->m_previewPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
        fields->m_previewPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
        fields->m_previewPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
        if (!manager->getPlayerGlow()) {
            fields->m_previewPlayer->disableGlowOutline();
        }

        if (doGlowFix) {

            if (m_selectedIconType == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerShip(), IconType::Ship);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ship);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (m_selectedIconType == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerBird(), IconType::Ufo);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Ufo);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            } else if (m_selectedIconType == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                fields->fakeGlowDisplay->updatePlayerFrame(manager->getPlayerJetpack(), IconType::Jetpack);
                MoreIcons::updateSimplePlayer(fields->fakeGlowDisplay, IconType::Jetpack);
                fields->fakeGlowDisplay->setColor(manager->colorForIdx(manager->getPlayerColor()));
                fields->fakeGlowDisplay->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
                fields->fakeGlowDisplay->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
                fields->fakeGlowDisplay->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
                if (!manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->disableGlowOutline();
                }
            }

            fields->fakeGlowDisplay->m_firstLayer->setOpacity(0);
            fields->fakeGlowDisplay->m_secondLayer->setVisible(false);
            fields->fakeGlowDisplay->m_birdDome->setVisible(false);
            fields->fakeGlowDisplay->m_detailSprite->setVisible(false);

            if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo || m_selectedIconType == IconType::Jetpack) {
                if (manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->setVisible(true);
                    fields->fakeGlowDisplay->m_outlineSprite->setVisible(true);
                    m_playerObject->m_outlineSprite->setVisible(false);
                }
            } else if (dontHideOnSpecials && validLastIcon) {
                if (manager->getPlayerGlow()) {
                    fields->fakeGlowDisplay->setVisible(true);
                    fields->fakeGlowDisplay->m_outlineSprite->setVisible(true);
                    m_playerObject->m_outlineSprite->setVisible(false);
                }
            } else {
                fields->fakeGlowDisplay->setVisible(false);
                m_playerObject->m_outlineSprite->setVisible(manager->getPlayerGlow());
            }
        
        }

        // Positions for SHIP and UFO, as well as a scale
        auto moveToShipPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {globalPosX, shipPosY})
        );
        auto moveToUfoPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {globalPosX, ufoPosY})
        );
        auto scaleToBasicSize = CCEaseBackInOut::create(
            CCScaleTo::create(0.3f, 0.88f)
        );

        // Positions and scaling for JETPACK
        auto moveToJetpackPos = CCEaseBackInOut::create(
            CCMoveTo::create(0.3f, {jetpackPosX, jetpackPosY})
        );
        auto scaleToJetpackSize = CCEaseBackInOut::create(
            CCScaleTo::create(0.3f, jetpackScale)
        );

        if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo || m_selectedIconType == IconType::Jetpack) {
            fields->m_previewPlayer->setVisible(true);
        } else if (dontHideOnSpecials && validLastIcon) {
            fields->m_previewPlayer->setVisible(true);
        } else {
            fields->m_previewPlayer->setVisible(false);
        }

        if (m_selectedIconType == IconType::Ship) {
            fields->m_previewPlayer->runAction(moveToShipPos);
            fields->m_previewPlayer->runAction(scaleToBasicSize);
        } else if (m_selectedIconType == IconType::Ufo) {
            fields->m_previewPlayer->runAction(moveToUfoPos);
            fields->m_previewPlayer->runAction(scaleToBasicSize);
        } else if (m_selectedIconType == IconType::Jetpack) {
            fields->m_previewPlayer->runAction(moveToJetpackPos);
            fields->m_previewPlayer->runAction(scaleToJetpackSize);
        }

    }
    
};