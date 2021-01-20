#ifndef VIEWER_WIDGET_H
#define VIEWER_WIDGET_H

#include <QtWidgets/QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>

class ViewerWidget : public QWidget {
public:
    ViewerWidget();
    ~ViewerWidget();
private:
    Qt3DCore::QEntity *root;
    Qt3DExtras::Qt3DWindow *view;
};

#endif
