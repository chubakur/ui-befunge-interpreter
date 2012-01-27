#ifndef GUINTERPRETER_H
#define GUINTERPRETER_H
#include <QtGui>
#include <interpreter.h>
class GUIWidget:public QWidget{
    Q_OBJECT
public:
    GUIWidget();
    ~GUIWidget();
    QList<QTableWidgetItem*> tableValues;
    QTableWidget* scripttable;
    QListWidget* stackView;
    QTextEdit* console;
private:
    QHBoxLayout* layout;
    QVBoxLayout* vlayout;
};

class GUInterpreter:public QMainWindow{
    Q_OBJECT
public:
    GUInterpreter();
    ~GUInterpreter();
private slots:
    void loadscript();
    void runscript();
private:
    QAction* loadscriptAction;
    QAction* quitAction;
    QAction* runScriptAction;
    QMenu* menu;
    QMenu* menu_runtime;
    GUIWidget* GUIEnvironment;
    BefungeInterpreter* interpreter;
};

#endif // GUINTERPRETER_H


