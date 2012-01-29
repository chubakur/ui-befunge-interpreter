#ifndef GUINTERPRETER_H
#define GUINTERPRETER_H
#include <QtGui>
#include <interpreter.h>
#include <guiwidget.h>
class GUInterpreter:public QMainWindow{
    Q_OBJECT
public:
    GUInterpreter();
    ~GUInterpreter();
private slots:
    void loadscript();
    void runscript();
    void runscriptSbS();//Step by Step
    void stopDebug();
    void step();
private:
    int x,y,direction;
    bool debug;
    QAction* loadscriptAction;
    QAction* quitAction;
    QAction* runScriptAction;
    QAction* startDebugAction;
    QAction* stopDebugAction;
    QAction* stepAction;
    QMenu* menu;
    QMenu* menu_runtime;
    QMenu* menu_debug;
    GUIWidget* GUIEnvironment;
    BefungeInterpreter* interpreter;
};

#endif // GUINTERPRETER_H


