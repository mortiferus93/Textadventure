#include "textadventure.h"
#include "ui_textadventure.h"
#include <ctime>
#include <bits/stdc++.h>

Textadventure::Textadventure(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Textadventure)
{
    ui->setupUi(this);

    srand((unsigned)time(NULL));
    connect(ui->cmd_links,SIGNAL(clicked(bool)),SLOT(Links()));
    connect(ui->cmd_rechts,SIGNAL(clicked(bool)),SLOT(Rechts()));
    connect(ui->cmd_look,SIGNAL(clicked(bool)),SLOT(Umsehen()));
    connect(ui->cmd_input,SIGNAL(clicked(bool)),SLOT(Eingabe()));
    connect(ui->list_actions,SIGNAL(itemClicked(QListWidgetItem*)),SLOT(Aktion()));

    stage = -2;

    has_bow = false;
    has_sword = false;

    hp = 5;
    keys = 0;

    bool_weapon = false;
    bool_name = false;
    bool_trait = false;
    bool_dirty = false;
    bool_stage_8_dirt = false;
    bool_has_copper_key = false;
    bool_has_iron_key = false;
    bool_has_brass_key = false;
    bool_used_copper_key = false;
    bool_used_iron_key = false;
    bool_used_brass_key = false;
    bool_stage_7_look = false;


    actions_stage_0_2 << "Kampferprobt" << "Akrobatisch" << "Tierlieb";
    actions_stage_0_1 << "Schwert" << "Bogen";
    actions_stage_1a << "Hände im Bach waschen";



    ui->cmd_links->setDisabled(true);
    ui->cmd_rechts->setDisabled(true);
    ui->cmd_look->setDisabled(true);
    ui->list_inventar->setDisabled(true);

    story();
}

Textadventure::~Textadventure()
{
    delete ui;
}

void Textadventure::story()
{
    ui->cmd_links->setDisabled(false);
    ui->cmd_rechts->setDisabled(false);
    ui->cmd_look->setDisabled(false);
    ui->cmd_input->setDisabled(false);
    ui->list_actions->setDisabled(false);
    ui->lbl_desc->clear();
    ui->lbl_place->clear();

//    ui->list_actions->blockSignals(true);
//    ui->list_actions->clear();
//    ui->list_actions->blockSignals(false);

    if(stage > 0)
    {
    ui->lbl_hp->setText(QString::number(hp));
    }

    //Charerstellung Name
   switch(stage)
   {
    case -2:
        ui->lbl_desc->setText("Hallo werter Abenteurer, ich brauche deine Hilfe! Wie heißt du eigentlich?");
        ui->cmd_links->setDisabled(true);
        ui->cmd_rechts->setDisabled(true);
        ui->cmd_look->setDisabled(true);
        ui->list_actions->setDisabled(true);
          break;

    //Charerstellung Trait
      case -1:
        ui->lbl_desc->setText("Wähle unter Aktionen deine Spezialisierung aus!");
        ui->list_actions->addItems(actions_stage_0_2);
        ui->cmd_links->setDisabled(true);
        ui->cmd_rechts->setDisabled(true);
        ui->cmd_look->setDisabled(true);
        ui->cmd_input->setDisabled(true);
          break;

 //Charerstellung Waffe
      case 0:
       ui->lbl_desc->setText("Du kommst an einem kleinen Waffenladen vorbei. Der Besitzer schaut dich mit seinem einen Auge seltsam an. Mit rauer Stimme sagt er zu dir: 'Du willst in den Wald gehen? Dann nimm eine von diesen hier mit, wenn du wieder herauskommen willst...' Vor ihm liegen ein Schwert sowie ein Bogen mit 10 Pfeilen. Was wirst du nehmen?");
       ui->lbl_place->setText("An einen seltsamen Ort...");
       ui->list_actions->addItems(actions_stage_0_1);
       ui->cmd_links->setDisabled(true);
       ui->cmd_rechts->setDisabled(true);
       ui->cmd_look->setDisabled(true);
       ui->cmd_input->setDisabled(true);
            break;


    case 1:
        ui->lbl_desc->setText("Hallo, ich heiße " + name + " und bin " + trait);
        ui->lbl_place->setText("Aktuelle Stage: " + QString::number(stage));
        if(bool_dirty == true)
        {
            ui->list_actions->addItems(actions_stage_1a);
        }

        //Temporärer Block
        ui->cmd_links->setDisabled(true);

    break;

    case 7:
        ui->lbl_desc->setText("Du stehst vor einem verschlossenen Tor.");

        if(bool_stage_7_look == true)
        {
            ui->lbl_desc->setText("Du stehst vor einem verschlossenen Tor. Dir fallen drei Schlösser an dem Tor auf. Eines aus Messing, eines aus Bronze und eines aus Eisen");
            ui->cmd_look->setDisabled(true);
        }

        if(keys > 0 && bool_stage_7_look == true)
        {
            ui->lbl_desc->setText("Du stehst vor einem verschlossenen Tor. Dir fallen drei Schlösser an dem Tor auf. Eines aus Messing, eines aus Bronze und eines aus Eisen. Du hast bereits " + QString::number(keys) + " von 3 Schlössern entriegelt!");
        }

        if(keys == 3)
        {
            ui->lbl_desc->setText("Du stehst vor einem Tor. Du hast alle 3 Schlösser entriegelt!");
        }

        if(bool_stage_7_look == true && bool_has_brass_key && bool_has_iron_key && bool_has_copper_key)
        {
            ui->list_actions->addItem("Das Tor öffnen und durchgehen");
        }

        //Temporärer Block
        ui->cmd_rechts->setDisabled(true);

    break;

    case 8:
        ui->lbl_place->setText("Aktuelle Stage: " + QString::number(stage));
        if(bool_stage_8_dirt == false && bool_has_brass_key == false)
        {
            ui->lbl_desc->setText("Du kommst auf eine Wiese.");
        }
        if(bool_stage_8_dirt == true && bool_has_brass_key == false)
        {
            ui->lbl_desc->setText("Dir fällt ein Fleck mit aufgewühlter Erde auf.");
            ui->list_actions->addItem("Graben");
        }
        if(bool_has_brass_key == true)
        {
            ui->lbl_desc->setText("Du kommst auf eine Wiese. Hier hast du einen Schlüssel aus Messing gefunden!");
            ui->cmd_look->setDisabled(true);
        }
    break;

    case 9:
        ui->list_actions->clear();
        ui->lbl_place->setText("Aktuelle Stage: " + QString::number(stage));
        if(bool_dirty == false)
        {
            ui->lbl_desc->setText("Glückwunsch! Du hast die Prinzessin gefunden und darfst jetzt lustige Bondagespielchen mit ihr machen!");
        }
        if(bool_dirty == true)
        {
            ui->lbl_desc->setText("Glückwunsch! Du hast die Prinzessin gefunden. Aber dank deiner schmutzigen Hände will sie nicht mit dir zu tun haben!");
        }
        ui->cmd_links->setDisabled(true);
        ui->cmd_rechts->setDisabled(true);
        ui->cmd_look->setDisabled(true);
    break;
    }

}

void Textadventure::Links()
{
    switch(stage)
        {
            case 1:
                stage = 4;
                story();
            break;

            case 7:
                stage = 8;
                story();
            break;

            case 8:
                stage = 1;
                story();
            break;
        }
}


void Textadventure::Rechts()
{
    switch(stage)
        {
            case 1:
                stage = 8;
                story();
            break;

            case 8:
                stage = 7;
                story();
            break;
        }
}

void Textadventure::Umsehen()
{
switch(stage)
    {
        case 1:
            ui->lbl_desc->setText("Du stehst am Rand eines hübschen Waldes, aus dem ein kleiner Bach fließt. Von links hörst du ein leises grunzenden Schnarchen");
        break;

        case 7:
            bool_stage_7_look = true;
            story();
        break;


        case 8:
            if(bool_stage_8_dirt == false)
            {
                 ui->list_actions->addItem("Graben");
                 bool_stage_8_dirt = true;
                 ui->lbl_desc->setText("Dir fällt ein Fleck aufgewühlter Erde auf");
                 ui->list_actions->clear();
                 story();
            }
        break;



    }
}

void Textadventure::Aktion()
{
switch(stage)
{

    case -1:
        if(ui->list_actions->currentItem()->text() == "Kampferprobt")
        {
            trait = "Kampferprobt";
        }

        if(ui->list_actions->currentItem()->text() == "Akrobatisch")
        {
            trait = "Akrobatisch";
        }

        if(ui->list_actions->currentItem()->text() == "Tierlieb")
        {
            trait = "Tierlieb";
        }
        bool_trait = true;
        ui->lbl_trait->setText(trait);
        stage = 0;
        ui->list_actions->clear();
        story();
    break;

case 0:
    if(ui->list_actions->currentItem()->text() == "Schwert")
    {
        has_sword = true;
        ui->lbl_weapon->setText("Schwert");
    }

    if(ui->list_actions->currentItem()->text() == "Bogen")
    {
       has_bow = true;
       ammo = 10;
       ui->lbl_weapon->setText("Bogen - Anzahl Pfeile: " + QString::number(ammo));
    }
    bool_weapon = true;
    stage = 1;
    ui->list_actions->clear();
    story();
break;

    case 1:
        if(ui->list_actions->currentItem()->text() == "Hände im Bach waschen")
        {
            bool_dirty = false;
            ui->lbl_desc->setText("Du hast deine Hände im Bach gewaschen");
            story();
        }
    break;

    case 7:

        if(ui->list_actions->currentItem()->text() == "Das Tor öffnen und durchgehen")
        {
            stage = 9;
            ui->list_actions->clear();
            story();
        }
    break;

    case 8:
        if(ui->list_actions->currentItem()->text() == "Graben")
        {
            bool_has_brass_key = true;
            ui->lbl_desc->setText("Du hast einen Schlüssel aus Messing gefunden! Aber deine Hände sind jetzt voller Dreck...");
            ui->list_inventar->addItem("Schlüssel aus Messing");
            keys++;
            bool_dirty = true;
            ui->list_actions->clear();
            story();
        }
    break;

}
}

void Textadventure::Eingabe()
{
if(stage == -2)
{
    name = ui->textinput->text();
    ui->cmd_input->setDisabled(true);

    bool_name = true;
    stage = -1;
    ui->textinput->clear();
    story();
}


//hier Cheatcodes einbauen
else
{
    if(ui->textinput->text() == "kesi")
    {
        bool_has_copper_key = true;
        bool_has_iron_key = true;
        keys = keys + 2;
        ui->list_inventar->addItem("Schlüssel aus Bronze");
        ui->list_inventar->addItem("Schlüssel aus Eisen");
        ui->textinput->clear();
    }

    if(ui->textinput->text() == "semako")
    {
        ui->cmd_links->setDisabled(true);
        ui->cmd_rechts->setDisabled(true);
        ui->cmd_look->setDisabled(true);
        ui->list_actions->setDisabled(true);
        ui->lbl_place->setText("In der Hölle");
        ui->lbl_desc->setText("Warum der?!?!?!");
    }

    if(ui->textinput->text() == "unicorn")
    {
        ui->cmd_links->setDisabled(false);
        ui->cmd_rechts->setDisabled(false);
        ui->cmd_look->setDisabled(false);
        ui->list_actions->setDisabled(false);
        ui->lbl_desc->setText("Ein Regenbogen erscheint vor dir und ein wunderhübsches Einhorn reitet davon herab");
        story(); // secret ende?
    }


}
}
