#ifndef YIBOFANG_H
#define YIBOFANG_H

#include <QWidget>

namespace Ui {
class yibofang;
}

class yibofang : public QWidget
{
    Q_OBJECT

public:
    explicit yibofang(QWidget *parent = nullptr, QStringList data = QStringList());
    ~yibofang();
    QStringList lstdata;
    void list_bofang();
    QString wantplay;
    void picture();
signals:
    void close_yibo_signal();
    void play_haveplayed_signal(QString s);
private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::yibofang *ui;

};

#endif // YIBOFANG_H
