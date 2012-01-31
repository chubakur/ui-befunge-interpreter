#include <guiwidget.h>
GUIWidget::GUIWidget(){
    scripttable = new QTableWidget(this);
    console = new QTextEdit(this);
    console->setReadOnly(true);
    layout = new QHBoxLayout();
    vlayout = new QVBoxLayout();
    stackView = new QListWidget();
    vlayout->addLayout(layout,80);
    vlayout->addWidget(console,20);
    layout->addWidget(scripttable,90);
    layout->addWidget(stackView,10);
    setLayout(vlayout);
}
GUIWidget::~GUIWidget(){
    delete scripttable;
    delete stackView;
    delete layout;
    for(int i=0;i<tableValues.size();i++) delete tableValues[i];
    for(int i=0;i<stackValues.size();i++) delete stackValues[i];
}
void GUIWidget::print(const char* sentence){
    console->setPlainText(console->toPlainText() + QString(sentence));
    console->verticalScrollBar()->setValue(console->verticalScrollBar()->maximum());
}
void GUIWidget::print(char letter){
    console->setPlainText(console->toPlainText() + QString(letter));
    console->verticalScrollBar()->setValue(console->verticalScrollBar()->maximum());
}
void GUIWidget::print(QString string){
    console->setPlainText(console->toPlainText() + string);
    console->verticalScrollBar()->setValue(console->verticalScrollBar()->maximum());
}
void GUIWidget::push(char letter){
    QListWidgetItem* item = new QListWidgetItem(QString(letter) + QString("     ")+QString::number(static_cast<int>(letter)));
    stackValues.push_back(item);
    stackView->insertItem(0,item);
}
void GUIWidget::pop(){
    QListWidgetItem* item = stackValues.back();
    stackView->removeItemWidget(item);
    stackValues.pop_back();
    delete item;
}
