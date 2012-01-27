#include <QtGui>
#include <GUInterpreter.h>
int main(int argc, char** args){
    QApplication app(argc, args);
    GUInterpreter g;
    g.show();
    return app.exec();
}
