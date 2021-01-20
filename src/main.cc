#include <QApplication>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QTabWidget>

#include "src/viewer/widget.h"

#include "deps/Qt-Ribbon-Widget/ribbon.h"

auto hline() {
    auto line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    return line;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto tabs = new Ribbon();
    auto addButtonToTabs = [&](const QString &tab, const QString &group, const QString &text, const QString &icon) {
        auto button = new QToolButton();
        button->setText(text);
        button->setIcon(QIcon(icon));
        tabs->addButton(tab, group, button);
        button->setMinimumSize(100, 80);
        button->setIconSize(QSize(64, 64));
        return button;
    };

    tabs->addTab(QIcon("deps/Qt-Ribbon-Widget/icons/briefcase_1.svg"), "Home");
    addButtonToTabs("Home", "Project", "Open", "deps/Qt-Ribbon-Widget/icons/live_folder_2.svg");
    addButtonToTabs("Home", "Project", "New", "deps/Qt-Ribbon-Widget/icons/create_new_2.svg");
    addButtonToTabs("Home", "Import", "File", "deps/Qt-Ribbon-Widget/icons/add_folder_2.svg");
    addButtonToTabs("Home", "Import", "Blabla", "deps/Qt-Ribbon-Widget/icons/add_database_2.svg");

    tabs->addTab("Definition");
    tabs->addTab("Geometry");
    tabs->addTab("Physics");
    tabs->addTab("Cranchers");
    tabs->addTab("Results");

    auto widget = new QWidget();
    auto layout = new QVBoxLayout(widget);
    layout->addWidget(tabs, 0);
    layout->addWidget(hline(), 0);
    layout->addWidget(new ViewerWidget(), 1);
    layout->setMargin(0);

    widget->resize(1024, 768);
    widget->show();
    return app.exec();
}
