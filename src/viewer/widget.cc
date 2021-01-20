#include "src/viewer/widget.h"

#include <QtWidgets/QHBoxLayout>

#include <Qt3DCore/QTransform>

#include <Qt3DRender/QCamera>
#include <Qt3DRender/QPointLight>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>

ViewerWidget::ViewerWidget() {
    this->view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    this->root = new Qt3DCore::QEntity();
    view->setRootEntity(root);

    auto input = new Qt3DInput::QInputAspect();
    view->registerAspect(input);

    auto camera = view->camera();
    camera->lens()->setPerspectiveProjection(45, 16./9., 0.1, 1000);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0, 0, 0));

    auto light = new Qt3DCore::QEntity(root);
    auto pointLight = new Qt3DRender::QPointLight(light);
    pointLight->setColor("white");
    pointLight->setIntensity(1);
    light->addComponent(pointLight);

    auto transform = new Qt3DCore::QTransform(light);
    transform->setTranslation(camera->position());
    light->addComponent(transform);

    auto controller = new Qt3DExtras::QOrbitCameraController(root);
    controller->setCamera(camera);

    auto widget = QWidget::createWindowContainer(view);
    auto layout = new QHBoxLayout(this);
    layout->addWidget(widget, 1);
    layout->setMargin(0);

    {
        auto mesh = new Qt3DExtras::QTorusMesh();
        mesh->setRadius(1);
        mesh->setMinorRadius(.4);
        mesh->setRings(100);
        mesh->setSlices(20);

        auto transform = new Qt3DCore::QTransform();
        transform->setScale(2);

        auto material = new Qt3DExtras::QPhongMaterial();
        material->setDiffuse(QColor(QRgb(0xbeb32b)));

        auto ent = new Qt3DCore::QEntity(root);
        ent->addComponent(mesh);
        ent->addComponent(material);
        ent->addComponent(transform);
    }
}

ViewerWidget::~ViewerWidget() {
    delete root;
    delete view;
}
