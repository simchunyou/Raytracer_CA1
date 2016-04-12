#ifndef __RENDERER_H
#define __RENDERER_H
#include "Object.h"
#include "Scene.h"
#include <vector>
#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <QImage>
#include <QColor>
#include <string>

class Renderer
{
  friend class NGLScene;
  private:
    int imageHeight;
    int imageWidth;
    int index_winning_intersection(std::vector <float> intersections);
    ngl::Vec3 multVecMatrix(const ngl::Vec3 &src, const ngl::Mat4 &MVP);
    ngl::Colour RenderPixel(Object *winning_object,
                            int winningIndex,
                            std::vector<Light *> light_objects,
                            std::vector<Object *> scene_objects,
                            ngl::Vec3 PointOfIntersection,
                            ngl::Mat4 ViewMatrix,
                            Ray IncidentRay,
                            int reflectionbouncelimit,
                            int *reflectionbouncepointer,
                            int refractionbouncelimit,
                            int *refractionbouncepointer,
                            std::vector<int> *ray_in_index,
                            std::vector<float> *ray_in_refractionIndex);
    int reflection_bounce_limit;
    int refraction_bounce_limit;
    QImage image;
    bool saveimage;
    std::string saveimagename;
    ngl::Camera* camera;
    Scene* scene;
    template <class t>
    void MVPPosition(std::vector<t *> Scene, ngl::Mat4 ViewMatrix);

  public:
    //Constructor and Destructor
    Renderer();
    ~Renderer();
    //Getter Functions
    int getHeight();
    int getWidth();
    float getAspectRatio();
    int getReflectionBounce();
    int getRefractionBounce();
    bool getsaveimage();
    //Setter Functions
    void setHeight(int height);
    void setWidth(int width);
    void setReflectionBounce(int ReflectionBounce);
    void setRefractionBounce(int RefractionBounce);
    void setSaveImage(bool saveimage);
    void setSaveImage(bool saveimage, std::string saveimagename);
    void setSceneCamera(ngl::Camera* camera);
    void setSceneScene(Scene* scene);
    //Method Functions
    void render();

};

#endif
