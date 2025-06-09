#include <Geode/modify/GJGarageLayer.hpp>
#include "Geode/utils/cocos.hpp"
#include <Geode/binding/GameManager.hpp>
#include <Geode/binding/SimplePlayer.hpp>
#include <hiimjustin000.more_icons/include/MoreIcons.hpp>
#include "helper.hpp"

// -- JETPACK PREVIEW INFO --
//X: +6 -------> 9
//Y: +4 -------> 6
//SCALE: 0.6 --> 0.9

using namespace geode::prelude;

// ------------------------------------
// FUNCTIONS FOR VANILLA/MORE ICONS FUNCTIONALITY
// ------------------------------------
void IconPreview::updatePreviewCube(SimplePlayer* player) {
    auto manager = GameManager::sharedState();

    player->updatePlayerFrame(manager->getPlayerFrame(), IconType::Cube);
    MoreIcons::updateSimplePlayer(player, IconType::Cube);
    player->setColor(manager->colorForIdx(manager->getPlayerColor()));
    player->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
    player->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
    player->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
    if (!manager->getPlayerGlow()) {
        player->disableGlowOutline();
    }
}
void IconPreview::updateShipGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();

    glowPlayer->updatePlayerFrame(manager->getPlayerShip(), IconType::Ship);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Ship);
    glowPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
    glowPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
    glowPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
    if (!manager->getPlayerGlow()) {
        glowPlayer->disableGlowOutline();
    }
}
void IconPreview::updateBirdGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();

    glowPlayer->updatePlayerFrame(manager->getPlayerBird(), IconType::Ufo);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Ufo);
    glowPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
    glowPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
    glowPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
    if (!manager->getPlayerGlow()) {
        glowPlayer->disableGlowOutline();
    }
}
void IconPreview::updateJetpackGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();

    glowPlayer->updatePlayerFrame(manager->getPlayerJetpack(), IconType::Jetpack);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Jetpack);
    glowPlayer->setColor(manager->colorForIdx(manager->getPlayerColor()));
    glowPlayer->setSecondColor(manager->colorForIdx(manager->getPlayerColor2()));
    glowPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
    if (!manager->getPlayerGlow()) {
        glowPlayer->disableGlowOutline();
    }
}

// ------------------------------------
// FUNCTIONS FOR SEPARATE DUAL ICONS FUNCTIONALITY
// ------------------------------------




auto doGlowFix = Mod::get()->getSettingValue<bool>("glow-fix");

$on_mod(Loaded) {
    listenForSettingChanges("glow-fix", [](bool value) {
        doGlowFix = value;
    });
}

class $modify(IPGarageLayer, GJGarageLayer){
    struct Fields {
        SimplePlayer* m_previewPlayer = SimplePlayer::create(0);
        SimplePlayer* m_dualPreview = SimplePlayer::create(0); //xdd
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

        SimplePlayer* playerToSend = fields->m_previewPlayer;

        IconPreview::updatePreviewCube(playerToSend);

        if (doGlowFix) {
            
            fields->fakeGlowDisplay->setPosition({posX, posY});
            fields->fakeGlowDisplay->setID("fake-glow-display"_spr);

            if (lastSelectedIcon == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateShipGlow(fields->fakeGlowDisplay);

            } else if (lastSelectedIcon == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateBirdGlow(fields->fakeGlowDisplay);

            } else if (lastSelectedIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                IconPreview::updateJetpackGlow(fields->fakeGlowDisplay);

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

        IconPreview::updatePreviewCube(fields->m_previewPlayer);

        if (doGlowFix) {

            if (m_selectedIconType == IconType::Ship || lastChosenIcon == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateShipGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Ufo || lastChosenIcon == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateBirdGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Jetpack || lastChosenIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                IconPreview::updateJetpackGlow(fields->fakeGlowDisplay);
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
        IconPreview::updatePreviewCube(fields->m_previewPlayer);

        if (doGlowFix) {

            if (m_selectedIconType == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateShipGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateBirdGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                IconPreview::updateJetpackGlow(fields->fakeGlowDisplay);
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