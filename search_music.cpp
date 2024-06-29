#include "search_music.h"
#include "ui_search_music.h"

search_music::search_music(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::search_music)
{
    ui->setupUi(this);
}

search_music::~search_music()
{
    delete ui;
}
