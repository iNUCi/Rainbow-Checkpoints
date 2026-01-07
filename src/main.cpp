#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "Utils.h"

using namespace geode::prelude;

class $modify(PlayLayer) {

    void updateCheckpoints() {
		
		if (CheckpointObject* obj = static_cast<CheckpointObject*>(m_checkpointArray->lastObject())) {

			if (obj->m_physicalCheckpointObject->getChildByID("outer"_spr) || obj->m_physicalCheckpointObject->getChildByID("inner"_spr)) return;

			ccColor3B color = Mod::get()->getSettingValue<ccColor3B>("starting-color"); 

			if (m_checkpointArray->count() >= 2) {
				if (CheckpointObject* obj2 = static_cast<CheckpointObject*>(m_checkpointArray->objectAtIndex(m_checkpointArray->count() - 2))) {
					color = static_cast<CCSprite*>(obj2->m_physicalCheckpointObject->getChildByID("inner"_spr))->getColor();
				}
			}

			obj->m_physicalCheckpointObject->m_addToNodeContainer = true;

			CCSprite* outer = CCSprite::create("checkpoint_outer.png"_spr);
			outer->setID("outer"_spr);
			CCSprite* inner = CCSprite::create("checkpoint_inner.png"_spr);
			inner->setID("inner"_spr);
			CCSprite* blank = CCSprite::create();

			outer->setPosition(obj->m_physicalCheckpointObject->getContentSize()/2);
			inner->setPosition(obj->m_physicalCheckpointObject->getContentSize()/2);

			CCSize origSize = obj->m_physicalCheckpointObject->getContentSize();

			obj->m_physicalCheckpointObject->setTexture(blank->getTexture());
			obj->m_physicalCheckpointObject->setTextureRect(blank->getTextureRect());
			obj->m_physicalCheckpointObject->setContentSize(origSize);
			obj->m_physicalCheckpointObject->setCascadeOpacityEnabled(true);
			obj->m_physicalCheckpointObject->setCascadeColorEnabled(true);

			ccHSVValue hsv = Utils::rgbToHsv(color);
			hsv.h += Mod::get()->getSettingValue<int64_t>("hue-shift");
			if (hsv.h >= 360) hsv.h -= 360;

			inner->setColor(Utils::hsvToRgb(hsv));

			obj->m_physicalCheckpointObject->addChild(outer);
			obj->m_physicalCheckpointObject->addChild(inner);
		}
	}

	void storeCheckpoint(CheckpointObject* p0) {
		PlayLayer::storeCheckpoint(p0);
		updateCheckpoints();
	}
};
