#ifndef GUIWIDGET_H
#define GUIWIDGET_H
#include <QtGui>
class GUIWidget:public QWidget{
    Q_OBJECT
public:
    GUIWidget();
    ~GUIWidget();
    QList<QTableWidgetItem*> tableValues;
    QList<QListWidgetItem*> stackValues;
    QTableWidget* scripttable;
    QListWidget* stackView;
    QTextEdit* console;
    void print(const char* sentence);
    void print(char letter);
    void print(QString string);
    void push(char item);
    void pop();
private:
    QHBoxLayout* layout;
    QVBoxLayout* vlayout;
};
#endif // GUIWIDGET_H
