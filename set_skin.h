#ifndef SET_SKIN_H
#define SET_SKIN_H

#include <QDialog>
#include<QMessageBox>
namespace Ui {
class set_skin;
}

class set_skin : public QDialog
{
    Q_OBJECT

public:
    explicit set_skin(QWidget *parent = nullptr);
    ~set_skin();
    void skin();
    void put_picture(QString a);
    QString a;
private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::set_skin *ui;

signals:
    void change_pifu_signals(QString s);
};

#endif // SET_SKIN_H
