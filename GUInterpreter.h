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
    void step();
    void trace();
private:
    int x,y,direction;
    bool debug;
    bool skipvoidsteps;
    QAction* loadscriptAction;
    QAction* quitAction;
    QAction* runScriptAction;
    QAction* startDebugAction;
    QAction* stepAction;
    QAction* traceAction;
    QTimer* traceTimer;
    QMenu* menu;
    QMenu* menu_runtime;
    QMenu* menu_debug;
    GUIWidget* GUIEnvironment;
    BefungeInterpreter* interpreter;
};

#endif // GUINTERPRETER_H


