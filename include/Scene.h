#ifndef __SCENE_H
#define __SCENE_H
#include <vector>
#include <Object.h>
#include <Light.h>

class Scene
{
  private:
    std::vector<Object*> scene_objects;
    std::vector<Light*> scene_lights;

  public:
    Scene();
    ~Scene();
    std::vector<Object*> getSceneObjects();
    std::vector<Light*> getLightObjects();
    void clearSceneObjects();
    void clearLightObjects();
    void addSceneObjects(Object* object);
    void addLightObjects(Light* light);

};

#endif
