cmake_minimum_required (VERSION 2.8.11)
project (GameLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")

set(sources 
	src/AppDelegate.cpp
	src/AppDelegate.h
	src/B2DebugDraw/B2DebugDrawLayer.cpp
	src/B2DebugDraw/B2DebugDrawLayer.h
	src/B2DebugDraw/GB2ShapeCacheX.cpp
	src/B2DebugDraw/GB2ShapeCacheX.h
	src/B2DebugDraw/GLESRender.cpp
	src/B2DebugDraw/GLESRender.h
	src/B2DebugDraw/VisibleRect.cpp	
	src/B2DebugDraw/VisibleRect.h
	src/GameObjects/GameObjectComposer.cpp
	src/GameObjects/GameObjectComposer.h
	src/GameObjects/GameObjectFactory.cpp
	src/GameObjects/GameObjectFactory.h
	src/GameObjects/IGameObject.h
	src/GameObjects/SimpleGameObject.cpp
	src/GameObjects/SimpleGameObject.h
	src/GameObjects/GameLevelGenerator.cpp
	src/GameObjects/GameLevelGenerator.h
	src/GameWorld.cpp
	src/GameWorld.h
	src/GameCamera.cpp
	src/GameCamera.h
	src/TestScene.cpp
	src/TestScene.h
	src/Utils/Convert.cpp
	src/Utils/Convert.h
	src/Utils/Environment.cpp
	src/Utils/Environment.h
	src/Utils/MacroCreate.h
	src/Utils/ITimeProvider.h
	src/Utils/TimeProvider.cpp
	src/Utils/TimeProvider.h
	src/Utils/b2Vec2Operators.h
	src/Particles/Particle.cpp
	src/Particles/Particle.h
	src/Particles/ParticlesCleaner.cpp
	src/Particles/ParticlesCleaner.h
	src/Particles/ParticlesGenerator.cpp
	src/Particles/ParticlesGenerator.h
	src/Particles/ParticlesMover.cpp
	src/Particles/ParticlesMover.h
	src/Particles/ParticlesReplacer.cpp
	src/Particles/ParticlesReplacer.h
	src/Particles/ParticlesSystem.cpp
	src/Particles/ParticlesSystem.h
	src/Particles/IParticlesReplacer.h
	src/Particles/IParticlesUpdater.h
	src/Particles/IParticlesCleaner.h
	src/Particles/ISystemUpdater.h
	src/ForceField/FieldMixer.cpp
	src/ForceField/FieldMixer.h
	src/ForceField/ForceFieldDebugDraw.cpp
	src/ForceField/ForceFieldDebugDraw.h
	src/ForceField/ForceFieldFactory.cpp
	src/ForceField/ForceFieldFactory.h
	src/ForceField/IForceField.h
	src/ForceField/GridForceField.cpp
	src/ForceField/GridForceField.h
	src/ForceField/StaticForceField.cpp
	src/ForceField/StaticForceField.h
	src/ForceField/Clamper.cpp
	src/ForceField/Clamper.h
)

set(includes
	$ENV{COCOS_X_ROOT}/cocos2d-x-3.13.1/cocos/audio/include
	$ENV{COCOS_X_ROOT}/cocos2d-x-3.13.1/external
	$ENV{COCOS_X_ROOT}/cocos2d-x-3.13.1/cocos
	$ENV{COCOS_X_ROOT}/cocos2d-x-3.13.1/external/glfw3/include/mac
	src
)

add_library(GameLib ${sources})
target_include_directories(GameLib PUBLIC ${includes})

foreach(source IN LISTS sources)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" file_group "${source_path}")
    source_group("${file_group}" FILES "${source}")
endforeach()