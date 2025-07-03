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
    glowPlayer->setGlowOutline(manager->colorForIdx(manager->getPlayerGlowColor()));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(manager->getPlayerGlowColor()));
    if (!manager->getPlayerGlow()) {
        glowPlayer->disableGlowOutline();
    }
}

// ------------------------------------
// FUNCTIONS FOR SEPARATE DUAL ICONS FUNCTIONALITY
// ------------------------------------
void IconPreview::updateDualPreviewCube(SimplePlayer* player) {
    auto manager = GameManager::sharedState();
    auto dualMod = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    int dualColor1 = dualMod->getSavedValue<int64_t>("color1");
    int dualColor2 = dualMod->getSavedValue<int64_t>("color2");
    bool dualHasGlow = dualMod->getSavedValue<bool>("glow");
    int glowColor = dualMod->getSavedValue<int64_t>("colorglow");

    int dualCubeFrame = dualMod->getSavedValue<int64_t>("cube");

    player->updatePlayerFrame(dualCubeFrame, IconType::Cube);
    MoreIcons::updateSimplePlayer(player, IconType::Cube, true);
    player->setColor(manager->colorForIdx(dualColor1));
    player->setSecondColor(manager->colorForIdx(dualColor2));
    player->setGlowOutline(manager->colorForIdx(glowColor));
    player->enableCustomGlowColor(manager->colorForIdx(glowColor));
    if (!dualHasGlow) {
        player->disableGlowOutline();
    }
}
void IconPreview::updateDualShipGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();
    auto dualMod = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    bool dualHasGlow = dualMod->getSavedValue<bool>("glow");
    int glowColor = dualMod->getSavedValue<int64_t>("colorglow");
    int dualShipFrame = dualMod->getSavedValue<int64_t>("ship");

    glowPlayer->updatePlayerFrame(dualShipFrame, IconType::Ship);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Ship, true);
    glowPlayer->setGlowOutline(manager->colorForIdx(glowColor));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(glowColor));
    if (!dualHasGlow) {
        glowPlayer->disableGlowOutline();
    }
}
void IconPreview::updateDualBirdGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();
    auto dualMod = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    bool dualHasGlow = dualMod->getSavedValue<bool>("glow");
    int glowColor = dualMod->getSavedValue<int64_t>("colorglow");
    int dualBirdFrame = dualMod->getSavedValue<int64_t>("bird");

    glowPlayer->updatePlayerFrame(dualBirdFrame, IconType::Ufo);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Ufo, true);
    glowPlayer->setGlowOutline(manager->colorForIdx(glowColor));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(glowColor));
    if (!dualHasGlow) {
        glowPlayer->disableGlowOutline();
    }
}
void IconPreview::updateDualJetpackGlow(SimplePlayer* glowPlayer) {
    auto manager = GameManager::sharedState();
    auto dualMod = Loader::get()->getLoadedMod("weebify.separate_dual_icons");

    bool dualHasGlow = dualMod->getSavedValue<bool>("glow");
    int glowColor = dualMod->getSavedValue<int64_t>("colorglow");
    int dualJetpackFrame = dualMod->getSavedValue<int64_t>("jetpack");

    glowPlayer->updatePlayerFrame(dualJetpackFrame, IconType::Jetpack);
    MoreIcons::updateSimplePlayer(glowPlayer, IconType::Jetpack, true);
    glowPlayer->setGlowOutline(manager->colorForIdx(glowColor));
    glowPlayer->enableCustomGlowColor(manager->colorForIdx(glowColor));
    if (!dualHasGlow) {
        glowPlayer->disableGlowOutline();
    }
}

auto doGlowFix = Mod::get()->getSettingValue<bool>("glow-fix");
auto enableReloadBtn = Mod::get()->getSettingValue<bool>("reload-btn");

$on_mod(Loaded) {
    listenForSettingChanges("glow-fix", [](bool value) {
        doGlowFix = value;
    });
    listenForSettingChanges("reload-btn", [](bool value) {
        enableReloadBtn = value;
    });
}

class $modify(IPGarageLayer, GJGarageLayer){
    struct Fields {
        SimplePlayer* m_previewPlayer = SimplePlayer::create(0);
        SimplePlayer* fakeGlowDisplay = SimplePlayer::create(0);
        // separate dual icons
        SimplePlayer* m_dualPreview = SimplePlayer::create(0);
        SimplePlayer* m_dualGlowDisplay = SimplePlayer::create(0);
    };

    static void onModify(auto& self) {
        (void) self.setHookPriorityBeforePre("GJGarageLayer::onSelect", "hiimjustin000.more_icons");
        (void) self.setHookPriorityBeforePre("GJGarageLayer::updatePlayerColors", "weebify.separate_dual_icons");
    }

    void onReloadButton(CCObject* sender) {
        
        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();
        auto lastChosenIcon = manager->m_playerIconType;

        bool isSeparateLoaded = Loader::get()->isModLoaded("weebify.separate_dual_icons");
        auto SDL = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
        int lastDualMode = 0;
        bool dualHasGlow = false;

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
        
        if (isSeparateLoaded) {
            lastDualMode = SDL->getSavedValue<int64_t>("lastmode");

            dualHasGlow = SDL->getSavedValue<bool>("glow");
            SimplePlayer* p2Icon = as<SimplePlayer*>(this->getChildByID("player2-icon"));

            IconPreview::updateDualPreviewCube(fields->m_dualPreview);

            if (doGlowFix) {
                if (lastDualMode == 1) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualShipGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 3) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualBirdGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 8) {
                    fields->m_dualGlowDisplay->setScale(1.5f);
                    IconPreview::updateDualJetpackGlow(fields->m_dualGlowDisplay);
                }

                fields->m_dualGlowDisplay->m_firstLayer->setOpacity(0);
                fields->m_dualGlowDisplay->m_secondLayer->setVisible(false);
                fields->m_dualGlowDisplay->m_birdDome->setVisible(false);
                fields->m_dualGlowDisplay->m_detailSprite->setVisible(false);

                if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                    if (dualHasGlow) {
                        fields->m_dualGlowDisplay->setVisible(true);
                        fields->m_dualGlowDisplay->m_outlineSprite->setVisible(true);
                        if (p2Icon){
                            p2Icon->m_outlineSprite->setVisible(false);
                        }
                    }
                } else {
                    fields->m_dualGlowDisplay->setVisible(false);
                    if (p2Icon) {
                        p2Icon->m_outlineSprite->setVisible(dualHasGlow);
                    }
                }

                if (lastDualMode == 8) {
                    fields->m_dualGlowDisplay->setScale(1.5f);
                } else {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                }
            }
        }

    }

    bool init() {
        if (!GJGarageLayer::init()) return false;

        auto fields = m_fields.self();
        auto gameManager = GameManager::sharedState();
        auto lastSelectedIcon = gameManager->m_playerIconType;
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        float posX = m_playerObject->getPositionX();
        float posY = m_playerObject->getPositionY();
        float sPosY = m_playerObject->getPositionY() + 16.f;
        float uPosY = m_playerObject->getPositionY() + 8.5f;
        float jPosX = m_playerObject->getPositionX() + 9.f;
        float jPosY = m_playerObject->getPositionY() + 6.f;

        float screenCenterX = winSize.width / 2;
        float player1PosWhenDualIcons = screenCenterX - winSize.width / 12;

        // dual icons stuff
        bool isSeparateLoaded = Loader::get()->isModLoaded("weebify.separate_dual_icons");
        auto SDL = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
        int lastDualMode = 0;
        float dualPosX = 0.f;
        float dualPosY = 0.f;
        float dualShipPosY = 0.f;
        float dualUfoPosY = 0.f;
        float dualJetpackPosX = 0.f;
        float dualJetpackPosY = 0.f;
        bool dualHasGlow = false;

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
            fields->m_previewPlayer->setScale(0.9f);
            
        } else {
            fields->m_previewPlayer->setPosition({posX, posY + 20.f});
        }

        IconPreview::updatePreviewCube(fields->m_previewPlayer);

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

        if (isSeparateLoaded) {
            lastDualMode = SDL->getSavedValue<int64_t>("lastmode");

            SimplePlayer* p2Icon = as<SimplePlayer*>(this->getChildByID("player2-icon"));
            dualPosX = player1PosWhenDualIcons + winSize.width / 6;
            dualPosY = m_playerObject->getPositionY();
            dualShipPosY = m_playerObject->getPositionY() + 16.f;
            dualUfoPosY = m_playerObject->getPositionY() + 8.5f;
            dualJetpackPosX = dualPosX + 9.f;
            dualJetpackPosY = m_playerObject->getPositionY() + 6.f;
            dualHasGlow = SDL->getSavedValue<bool>("glow");

            fields->m_previewPlayer->setPositionX(player1PosWhenDualIcons);
            fields->fakeGlowDisplay->setPositionX(player1PosWhenDualIcons);

            if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                fields->m_dualPreview->setVisible(true);
            } else {
                fields->m_dualPreview->setVisible(false);
            }

            if (lastDualMode == 1) { // SHIP
                fields->m_dualPreview->setPosition({dualPosX, dualShipPosY});
                fields->m_dualPreview->setScale(0.88f);
            } else if (lastDualMode == 3) { // UFO
                fields->m_dualPreview->setPosition({dualPosX, dualUfoPosY});
                fields->m_dualPreview->setScale(0.88f);
            } else if (lastDualMode == 8) { // JETPACK
                fields->m_dualPreview->setPosition({dualJetpackPosX, dualJetpackPosY});
                fields->m_dualPreview->setScale(0.96f);
            } else {
                fields->m_dualPreview->setPosition({dualPosX, dualPosY + 20.f});
            }

            IconPreview::updateDualPreviewCube(fields->m_dualPreview);

            if (doGlowFix) {
                fields->m_dualGlowDisplay->setPosition({dualPosX, dualPosY});
                fields->m_dualGlowDisplay->setID("fake-dual-glow-display"_spr);

                if (lastDualMode == 1) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualShipGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 3) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualBirdGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 8) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualJetpackGlow(fields->m_dualGlowDisplay);
                }

                fields->m_dualGlowDisplay->m_firstLayer->setOpacity(0);
                fields->m_dualGlowDisplay->m_secondLayer->setVisible(false);
                fields->m_dualGlowDisplay->m_birdDome->setVisible(false);
                fields->m_dualGlowDisplay->m_detailSprite->setVisible(false);

                if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                    if (dualHasGlow) {
                        fields->m_dualGlowDisplay->setVisible(true);
                        fields->m_dualGlowDisplay->m_outlineSprite->setVisible(true);
                        if (p2Icon){
                            p2Icon->m_outlineSprite->setVisible(false);
                        } else {
                            geode::log::warn("p2 icon not found! something went wrong, sorry. are you on android/ios by any chance LOL");
                        }
                    } else {
                        fields->m_dualGlowDisplay->setVisible(false);
                    }
                }

                this->addChild(fields->m_dualGlowDisplay, -2);
            }

            fields->m_dualPreview->setID("dual-preview-simpleplayer"_spr);
            this->addChild(fields->m_dualPreview, -1);

        }

        if (enableReloadBtn) {
            auto spr = CircleButtonSprite::createWithSprite("reload.png"_spr, 1.25f, CircleBaseColor::Green, CircleBaseSize::Small);
            auto reloadButton = CCMenuItemSpriteExtra::create(
                spr,
                this,
                menu_selector(IPGarageLayer::onReloadButton)
            );
            reloadButton->setID("reload-button"_spr);

            auto sexito = as<CCMenu*>(this->getChildByID("shards-menu"));
            sexito->addChild(reloadButton);
        }

        return true;
    }

    void updatePlayerColors() {
        GJGarageLayer::updatePlayerColors();

        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();
        auto lastChosenIcon = manager->m_playerIconType;

        // dual icons stuff
        bool isSeparateLoaded = Loader::get()->isModLoaded("weebify.separate_dual_icons");
        auto SDL = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
        int lastDualMode = 0;
        bool dualHasGlow = false;

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
        
        if (isSeparateLoaded) {
            lastDualMode = SDL->getSavedValue<int64_t>("lastmode");

            dualHasGlow = SDL->getSavedValue<bool>("glow");
            SimplePlayer* p2Icon = as<SimplePlayer*>(this->getChildByID("player2-icon"));

            IconPreview::updateDualPreviewCube(fields->m_dualPreview);

            if (doGlowFix) {
                if (lastDualMode == 1) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualShipGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 3) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualBirdGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 8) {
                    if (p2Icon) {
                        fields->m_dualGlowDisplay->setScale(p2Icon->getScale());
                    } else {
                        fields->m_dualGlowDisplay->setScale(1.5f);
                    }
                    IconPreview::updateDualJetpackGlow(fields->m_dualGlowDisplay);
                }

                fields->m_dualGlowDisplay->m_firstLayer->setOpacity(0);
                fields->m_dualGlowDisplay->m_secondLayer->setVisible(false);
                fields->m_dualGlowDisplay->m_birdDome->setVisible(false);
                fields->m_dualGlowDisplay->m_detailSprite->setVisible(false);

                if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                    if (dualHasGlow) {
                        fields->m_dualGlowDisplay->setVisible(true);
                        fields->m_dualGlowDisplay->m_outlineSprite->setVisible(true);
                        if (p2Icon){
                            p2Icon->m_outlineSprite->setVisible(false);
                        } else {
                            geode::log::warn("p2 icon not found! glow enabled, something went wrong");
                        }
                    }
                } else {
                    fields->m_dualGlowDisplay->setVisible(false);
                    if (p2Icon) {
                        p2Icon->m_outlineSprite->setVisible(dualHasGlow);
                    } else {
                        geode::log::warn("p2 icon not found! glow disabled, something went wrong");
                    }
                }

            }

        }

    }

    void onSelect(CCObject* iconSender) {
        GJGarageLayer::onSelect(iconSender);

        auto fields = m_fields.self();
        auto manager = GameManager::sharedState();
        auto winSize = CCDirector::sharedDirector()->getWinSize();

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

        float winCenterX = winSize.width / 2;
        float player1PosWhenDualIcons = winCenterX - winSize.width / 12;

        // dual icons stuff
        bool isSeparateLoaded = Loader::get()->isModLoaded("weebify.separate_dual_icons");
        auto SDL = Loader::get()->getLoadedMod("weebify.separate_dual_icons");
        int lastDualMode = 0;
        float dualPosX = 0.f;
        float dualPosY = 0.f;
        float dualShipPosY = 0.f;
        float dualUfoPosY = 0.f;
        float dualJetpackPosX = 0.f;
        float dualJetpackPosY = 0.f;
        bool dualHasGlow = false;
        SimplePlayer* p2Icon = nullptr;

        // this runs on selecting any mode just to make sure it updates properly
        IconPreview::updatePreviewCube(fields->m_previewPlayer);

        if (doGlowFix) {

            if (m_selectedIconType == IconType::Ship || lastIcon == IconType::Ship) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateShipGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Ufo || lastIcon == IconType::Ufo) {
                fields->fakeGlowDisplay->setScale(1.6f);
                IconPreview::updateBirdGlow(fields->fakeGlowDisplay);

            } else if (m_selectedIconType == IconType::Jetpack || lastIcon == IconType::Jetpack) {
                fields->fakeGlowDisplay->setScale(1.5f);
                IconPreview::updateJetpackGlow(fields->fakeGlowDisplay);
            }

            fields->fakeGlowDisplay->m_firstLayer->setOpacity(0);
            fields->fakeGlowDisplay->m_secondLayer->setVisible(false);
            fields->fakeGlowDisplay->m_birdDome->setVisible(false);
            fields->fakeGlowDisplay->m_detailSprite->setVisible(false);

            if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo || m_selectedIconType == IconType::Jetpack || lastIcon == IconType::Ship || lastIcon == IconType::Ufo || lastIcon == IconType::Jetpack) {
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

        if (m_selectedIconType == IconType::Ship || m_selectedIconType == IconType::Ufo || m_selectedIconType == IconType::Jetpack || lastIcon == IconType::Ship || lastIcon == IconType::Ufo || lastIcon == IconType::Jetpack) {
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


        if (isSeparateLoaded) {
            lastDualMode = SDL->getSavedValue<int64_t>("lastmode");

            p2Icon = static_cast<SimplePlayer*>(this->getChildByID("player2-icon"));
            dualPosX = player1PosWhenDualIcons + winSize.width / 6;
            dualPosY = m_playerObject->getPositionY();
            dualShipPosY = m_playerObject->getPositionY() + 16.f;
            dualUfoPosY = m_playerObject->getPositionY() + 8.5f;
            dualJetpackPosX = dualPosX + 9.f;
            dualJetpackPosY = m_playerObject->getPositionY() + 6.f;
            dualHasGlow = SDL->getSavedValue<bool>("glow");

            IconPreview::updateDualPreviewCube(fields->m_dualPreview);

            if (doGlowFix) {
                if (lastDualMode == 1) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualShipGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 3) {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                    IconPreview::updateDualBirdGlow(fields->m_dualGlowDisplay);

                } else if (lastDualMode == 8) {
                    fields->m_dualGlowDisplay->setScale(1.5f);
                    IconPreview::updateDualJetpackGlow(fields->m_dualGlowDisplay);
                }

                fields->m_dualGlowDisplay->m_firstLayer->setOpacity(0);
                fields->m_dualGlowDisplay->m_secondLayer->setVisible(false);
                fields->m_dualGlowDisplay->m_birdDome->setVisible(false);
                fields->m_dualGlowDisplay->m_detailSprite->setVisible(false);

                if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                    if (dualHasGlow) {
                        fields->m_dualGlowDisplay->setVisible(true);
                        fields->m_dualGlowDisplay->m_outlineSprite->setVisible(true);
                        p2Icon->m_outlineSprite->setVisible(false);
                    }
                } else {
                    fields->m_dualGlowDisplay->setVisible(false);
                    p2Icon->m_outlineSprite->setVisible(dualHasGlow);
                }                
            }

            if (lastDualMode == 1 || lastDualMode == 3 || lastDualMode == 8) {
                fields->m_dualPreview->setVisible(true);
            } else {
                fields->m_dualPreview->setVisible(false);
            }

            if (lastDualMode == 1) { // SHIP
                fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                    CCMoveTo::create(0.3f, {dualPosX, dualShipPosY})
                ));
                fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                    CCScaleTo::create(0.3f, 0.88f)
                ));
            } else if (lastDualMode == 3) { // UFO
                fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                    CCMoveTo::create(0.3f, {dualPosX, dualUfoPosY})
                ));
                fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                    CCScaleTo::create(0.3f, 0.88f)
                ));
            } else if (lastDualMode == 8) { // JETPACK
                if (p2Icon->getScale() != 1.6f) {
                    fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                        CCMoveTo::create(0.3f, {dualJetpackPosX, dualJetpackPosY})
                    ));
                    fields->m_dualPreview->runAction(CCEaseBackInOut::create(
                        CCScaleTo::create(0.3f, 0.9f)
                    ));
                } else {
                    fields->m_dualGlowDisplay->setScale(1.6f);
                }
                
            }

        }

    }
    
};