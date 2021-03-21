#ifndef TEXTADVENTURE_H
#define TEXTADVENTURE_H

#include <QMainWindow>

namespace Ui {
class Textadventure;
}

class Textadventure : public QMainWindow
{
    Q_OBJECT

public:
    explicit Textadventure(QWidget *parent = 0);
    ~Textadventure();

private:
    Ui::Textadventure *ui;
    int stage;
    int ammo;
    int hp;
    int keys;
    bool has_sword;
    bool has_bow;
    bool bool_weapon;
    bool bool_name;
    bool bool_trait;
    bool bool_dirty;
    bool bool_stage_8_dirt;
    bool bool_has_copper_key;
    bool bool_has_iron_key;
    bool bool_has_brass_key;
    bool bool_used_copper_key;
    bool bool_used_iron_key;
    bool bool_used_brass_key;
    bool bool_stage_7_look;
    QString name;
    QString weapon;
    QString trait;
    QStringList actions_stage_0_1;
    QStringList actions_stage_0_2;
    QStringList actions_stage_1a;
    QStringList actions_stage_1b;

public slots:
    void Links();
    void Rechts();
    void Eingabe();
    void Aktion();
    void Umsehen();
    void story();
};

#endif // TEXTADVENTURE_H
