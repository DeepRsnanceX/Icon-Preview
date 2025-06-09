#pragma once
#include "cocos2d.h"
#include <Geode/binding/SimplePlayer.hpp>

class IconPreview {
public:
    // ------------------------------------
    // VANILLA MOD
    // ------------------------------------
    static void updatePreviewCube(SimplePlayer* player);
    static void updateShipGlow(SimplePlayer* glowPlayer);
    static void updateBirdGlow(SimplePlayer* glowPlayer);
    static void updateJetpackGlow(SimplePlayer* glowPlayer);
    // ------------------------------------
    // SEPARATE DUAL ICONS FUNCTIONS
    // ------------------------------------
    static void updateDualPreviewCube(SimplePlayer* player);
    static void updateDualShipGlow(SimplePlayer* glowPlayer);
    static void updateDualBirdGlow(SimplePlayer* glowPlayer);
    static void updateDualJetpackGlow(SimplePlayer* glowPlayer);
};
