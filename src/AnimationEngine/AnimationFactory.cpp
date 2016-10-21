//
//  AnimationFactory.cpp
//  Wanderer
//
//  Created by Luda on 05/12/15.
//
//

#include "json/document.h"
#include "platform/CCFileUtils.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "2d/CCSprite.h"
#include "2d/CCSpriteFrame.h"
#include "AnimationFactory.h"
#include "AnimationEngine.h"
#include "Animation.h"
#include "IndexedAnimation.h"

using namespace cocos2d;

AnimationEnginePtr AnimationFactory::getHeroAnimationEngine()
{
    std::map<std::string, IAnimationPtr> anims = getAnimationsFromJson("config/hero_animations.json");
    AnimationEnginePtr engine(new AnimationEngine());
    
    // run loop
    //engine->addRule(anims["run_from_right_leg"], 5, "AUTO_TRANSITION", anims["run_from_left_leg"]);
    //engine->addRule(anims["run_from_left_leg"], 5, "AUTO_TRANSITION", anims["run_from_right_leg"]);
    
    // run -> jump
    //engine->addRule(anims["run_from_right_leg"], 0, 5, "jump", anims["jump_from_right_leg"]);
    //engine->addRule(anims["run_from_left_leg"], 0, 5, "jump", anims["jump_from_left_leg"]);
    
    // jump -> run
    //engine->addRule(anims["jump_from_right_leg"], 0, 10, "run", anims["run_from_left_leg"]);
    //engine->addRule(anims["jump_from_left_leg"], 0, 10, "run", anims["run_from_right_leg"]);
    
    // jump -> run auto transition
    //engine->addRule(anims["jump_from_right_leg"], 0, 10, "AUTO_TRANSITION", anims["run_from_left_leg"]);
    //engine->addRule(anims["jump_from_left_leg"], 0, 10, "AUTO_TRANSITION", anims["run_from_right_leg"]);

    engine->addFallback("jump", anims["jump_from_left_leg"]);
    engine->addFallback("run", anims["run_from_left_leg"]);
    
    return engine;
}

AnimationEnginePtr AnimationFactory::getEngine(const std::string &fileName)
{
    std::map<std::string, IAnimationPtr> anims = getAnimationsFromJson(fileName);
    AnimationEnginePtr engine(new AnimationEngine());

    std::string content = FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    
    const rapidjson::Value &jTransitions = doc["transitions"];
    
    for (auto it = jTransitions.MemberBegin(); it != jTransitions.MemberEnd(); ++it)
    {
        const rapidjson::Value &jGroup = it->value;
        std::string desiredGroupId = it->name.GetString();
        
        for (auto i = jGroup.MemberBegin(); i != jGroup.MemberEnd(); ++i)
        {
            std::string fromAnimation = i->name.GetString();
            std::string transitionAnimation = i->value["transition"].GetString();
            
            engine->addRule(anims[fromAnimation], desiredGroupId, anims[transitionAnimation]);
        }
    }
    
    const rapidjson::Value &jFallbacks = doc["fallbacks"];
    
    for (auto it = jFallbacks.MemberBegin(); it != jFallbacks.MemberEnd(); ++it)
    {
        std::string groupName = it->name.GetString();
        std::string animation = it->value.GetString();
        
        engine->addFallback(groupName, anims[animation]);
    }
    
    return engine;
}

IAnimationPtr AnimationFactory::getAnimation(const std::string &prefix,
                                             int startFrame,
                                             int endFrame,
                                             int fps,
                                             bool isCycled)
{
    Vector<SpriteFrame*> frames;
    
    for (int i = startFrame; i <= endFrame; ++i)
    {
        std::string fileName = getFileName(prefix, i);
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(fileName);
        Rect rect;
        rect.origin.set(0, 0);
        rect.size = texture->getContentSize();
        SpriteFrame *frame = SpriteFrame::createWithTexture(texture, rect);
        assert(frame);
        frames.pushBack(frame);
    }
    
    ::Animation* animation = new ::Animation(frames, fps, isCycled);
    
    return IAnimationPtr(animation);
}

std::string AnimationFactory::getFileName(const std::string &fileName, int i) const
{
    std::string index = std::to_string(i);
    std::string name = fileName + index + ".png";
    
    return name;
}

std::map<std::string, IAnimationPtr> AnimationFactory::getAnimationsFromJson(const std::string &fileName)
{
    std::string content = FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document doc;
    doc.Parse(content.c_str());
    
    std::map<std::string, IAnimationPtr> animations;
    
    const rapidjson::Value &jAnimations = doc["animations"];
    
    for (auto it = jAnimations.MemberBegin(); it != jAnimations.MemberEnd(); ++it)
    {
        const rapidjson::Value &jAnimation = it->value;
        
        bool isCycled  = jAnimation["cyclic"].GetBool();
        int fps = jAnimation["fps"].GetInt();
        
        const rapidjson::Value &jFramePattern = jAnimation["frame_pattern"];
        std::string prefix = jFramePattern["prefix"].GetString();
        std::string extention = jFramePattern["extension"].GetString();
        
        const rapidjson::Value &jRange = jFramePattern["range"];
        int first = jRange["first"].GetInt();
        int last = jRange["last"].GetInt();
        
        std::string animationName = it->name.GetString();
        IAnimationPtr animation = getAnimation(prefix, first, last, fps, isCycled);
        
        animations[animationName] = animation;
    }
    
    
    
    return animations;
}


