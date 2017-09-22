TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += lfreetype

SOURCES += main.cpp \
    application.cpp \
    context.cpp \
    glad.c \
    States/stateplaying.cpp \
    Renderer/masterrenderer.cpp \
    Renderer/Modules/basemodel.cpp \
    Renderer/Modules/textrenderer.cpp \
    Renderer/Modules/lightsource.cpp \
    ResourceManager/gtexture.cpp \
    ResourceManager/resourcemanager.cpp \
    ResourceManager/textureatlas.cpp \
    camera.cpp \
    shader.cpp \
    MathFunctions/matrixfunctions.cpp \
    player.cpp \
    ResourceManager/texturebase.cpp \
    ResourceManager/fonttexture.cpp \
    Util/fpscounter.cpp \
    World/world.cpp \
    MathFunctions/simplex.cpp \
    MathFunctions/mathfunctions.cpp \
    MathFunctions/hash.cpp \
    Renderer/Modules/Debug/debugelements.cpp \
    Util/Collisions/plane.cpp \
    Util/Collisions/collisioncheckfunc.cpp \
    Renderer/Modules/BasicObjects/basicobjects.cpp \
    Renderer/Modules/terrainrenderer.cpp \
    Renderer/Modules/dynamicobject.cpp \
    World/TerrainV1_Sections/terrain.cpp \
    World/TerrainV1_Sections/terraindata.cpp \
    World/TerrainV1_Sections/terrainsection.cpp \
    World/TerrainV1_Sections/terrainmap.cpp \
    World/TerrainV1_Sections/water.cpp \
    ResourceManager/cubemap.cpp \
    Renderer/Modules/skyboxrenderer.cpp \
    Renderer/Modules/framebuffer.cpp \
    Renderer/Modules/guirenderer.cpp


HEADERS += \
    application.h \
    States/GameStateBase.h \
    config.h \
    context.h \
    States/stateplaying.h \
    Renderer/masterrenderer.h \
    Renderer/Modules/basemodel.h \
    Renderer/Modules/textrenderer.h \
    Renderer/Modules/lightsource.h \
    ResourceManager/gtexture.h \
    ResourceManager/resourcemanager.h \
    ResourceManager/textureatlas.h \
    camera.h \
    entity.h \
    glm.h \
    shader.h \
    MathFunctions/matrixfunctions.h \
    player.h \
    States/Events/event.h \
    ResourceManager/texturebase.h \
    ResourceManager/fonttexture.h \
    Util/fpscounter.h \
    World/world.h \
    World/worldconstants.h \
    MathFunctions/simplex.h \
    MathFunctions/perlin.hpp \
    Util/array_2d.h \
    MathFunctions/mathfunctions.h \
    MathFunctions/hash.h \
    glheader.h \
    Renderer/Modules/Debug/debugelements.h \
    Util/Collisions/plane.h \
    Util/Collisions/collisionpacket.h \
    Util/Collisions/collisioncheckfunc.h \
    Renderer/Modules/renderobject.h \
    Renderer/Modules/BasicObjects/basicobjects.h \
    Renderer/Modules/BasicObjects/rectcw.h \
    Renderer/Modules/BasicObjects/cube.h \
    Renderer/Modules/BasicObjects/pyramid.h \
    Renderer/Modules/terrainrenderer.h \
    Renderer/Modules/dynamicobject.h \
    World/TerrainV1_Sections/terrain.h \
    World/TerrainV1_Sections/terraindata.h \
    World/TerrainV1_Sections/terrainsection.h \
    World/TerrainV1_Sections/terrainmap.h \
    World/TerrainV1_Sections/water.h \
    Renderer/Modules/BasicObjects/skybox.h \
    ResourceManager/cubemap.h \
    Renderer/Modules/skyboxrenderer.h \
    Renderer/Modules/framebuffer.h \
    Renderer/Modules/guirenderer.h \
    Renderer/Modules/BasicObjects/rectTopLeft.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../1DevTools/_LIBRARIES/lib/ -lglfw3dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../1DevTools/_LIBRARIES/lib/ -lglfw3dll

win32: LIBS += -L$$PWD/../../../1DevTools/_LIBRARIES/lib/ -llibfreetype.dll

INCLUDEPATH += $$PWD/../../../1DevTools/_LIBRARIES/include
DEPENDPATH += $$PWD/../../../1DevTools/_LIBRARIES/include

DISTFILES += \
    res/img/container.jpg \
    res/img/container6.jpg \
    res/img/atlas.png \
    res/img/awesomeface.png \
    res/img/dirt.png \
    res/shader/basicShaders/basic.frag \
    res/shader/basicShaders/basicColor.frag \
    res/shader/basicShaders/basicTexture.frag \
    res/shader/shader.frag \
    res/shader/shaderLight.frag \
    res/shader/basicShaders/basic.vert \
    res/shader/basicShaders/basicColor.vert \
    res/shader/basicShaders/basicTexture.vert \
    res/shader/shader.vert \
    res/shader/shaderLight.vert \
    res/shader/basicShaders/basicFont.frag \
    res/shader/basicShaders/basicFont.vert \
    res/shader/basicShaders/basicTextureLight.frag \
    res/shader/basicShaders/basicTextureLight.vert \
    res/shader/GameShaders/TerrainShader.frag \
    res/shader/GameShaders/TerrainShader.vert \
    res/shader/GameShaders/TerrainShaderColor.frag \
    res/shader/GameShaders/TerrainShaderColor.vert \
    res/shader/GameShaders/WaterShader.frag \
    res/shader/GameShaders/WaterShader.vert \
    res/shader/GameShaders/SkyBoxShader.frag \
    res/shader/GameShaders/SkyBoxShader.vert \
    res/shader/GameShaders/GUIShader.frag \
    res/shader/GameShaders/GUIShader.vert

RESOURCES += \
    res/resources.qrc








