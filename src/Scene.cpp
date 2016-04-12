#include <iostream>
#include "Scene.h"
#include "Light.h"
#include "Object.h"

Scene::Scene()
{

}

Scene::~Scene()
{
  //std::cout << "Scene has been deleted" << std::endl;
}

std::vector<Object*> Scene::getSceneObjects()
{
  return scene_objects;
}

std::vector<Light*> Scene::getLightObjects()
{
  return scene_lights;
}

void Scene::clearSceneObjects()
{
  scene_objects.clear();
}

void Scene::clearLightObjects()
{
  scene_lights.clear();
}

void Scene::addSceneObjects(Object* object)
{
  scene_objects.push_back(object);
}

void Scene::addLightObjects(Light *light)
{
  scene_lights.push_back(light);
}
