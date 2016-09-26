cmake_minimum_required (VERSION 2.8.11)
project (GameLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")

set(sources 
	src/AppDelegate.cpp
	src/AppDelegate.h
	src/GameObjects/GameObjectComposer.cpp
	src/GameObjects/GameObjectComposer.h
	src/GameObjects/GameObjectFactory.cpp
	src/GameObjects/GameObjectFactory.h
	src/GameObjects/IGameObject.h
	src/GameObjects/SimpleGameObject.cpp
	src/GameObjects/SimpleGameObject.h
	src/GameWorld.cpp
	src/GameWorld.h
	src/TestScene.cpp
	src/TestScene.h
	src/Utils/Convert.cpp
	src/Utils/Convert.h
	src/Utils/Environment.cpp
	src/Utils/Environment.h
	src/Utils/MacroCreate.h
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
