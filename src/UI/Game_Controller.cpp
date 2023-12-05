//
// Created by Pavel on 28.11.2023.
//

#include "Game_Controller.h"

#include <utility>
#include "../Entities/Operative.h"
#include "../Entities/Wild_Creature.h"
#include "../Entities/Forager.h"
#include "../Entities/Intelligent_Creature.h"
#include "../Items/FirstAidKit.h"
#include "../Items/RoundContainer.h"

UI::GameController::GameController(const std::string &config_filename, std::shared_ptr<tgui::Gui> ptr_gui) : ptrGUI_(
        std::move(
                ptr_gui)) {
    // временное решение
    TeamNS::Team A("Operative");
    TeamNS::Team B("Creatures");
    auto operative_unit = std::make_shared<EntityNS::Operative>("default");
    operative_unit->setCurTime(10);
    operative_unit->setVisibilityRadius(1);
    WeaponNS::Weapon first_active_weapon("AK-47", 1, 5, 4);
    operative_unit->setActiveWeapon(first_active_weapon);
    InventoryNS::Inventory loaded_inventory_unit;
    loaded_inventory_unit.push_back(std::make_unique<FirstAidKitNS::FirstAidKit>("AID", 1, 1, 5));
    loaded_inventory_unit.push_back(std::make_unique<RoundNS::RoundContainer>("Ak-47 ammo", 1, 10, 7));
    loaded_inventory_unit.push_back(std::make_unique<WeaponNS::Weapon>("AK-47", 1, 1, 5));
    operative_unit->setInvetnory(std::move(loaded_inventory_unit));
    auto wild = std::make_shared<EntityNS::IntelligentCreature>("wild A");
    wild->setPos({2, 2});
    wild->setCurTime(10);
    wild->setAvaliableTime(100);
    wild->setVisibilityRadius(1);
    A.push_back(std::move(operative_unit));
    A.push_back(std::move(wild));

    auto creature_unit = std::make_shared<EntityNS::Forager>("default");
    creature_unit->setCurHeatPoint(2);
    creature_unit->setAvaliableTime(3);
    creature_unit->setPos({2, 0});
    InventoryNS::Inventory loaded_inventory_creature;
    loaded_inventory_creature.push_back(std::make_unique<WeaponNS::Weapon>("MP4-A1", 1, 1, 1));
    loaded_inventory_creature.push_back(std::make_unique<FirstAidKitNS::FirstAidKit>("AID", 1, 1, 5));
    creature_unit->setInvetnory(std::move(loaded_inventory_creature));
    B.push_back(std::move(creature_unit));
    std::vector<TeamNS::Team> teams;
    teams.push_back(std::move(A));
    teams.push_back(std::move(B));
    GameNS::Game temp(3, std::move(teams));
    ScaleX_ = 10.0 / 3;
    ScaleY = 10.0 / 3;
    TileMap temp_map("../models/texture.png", sf::Vector2u(64, 64), 3, 3);
    SpriteTexture_.loadFromFile("../models/units.png");
    ActiveUnitSprite_.setTexture(SpriteTexture_);
    Game_ = std::move(temp);
    Board_ = std::move(temp_map);
    Game_.setCellType({1, 1}, LevelNS::WALL);
    Game_.setCellType({1, 0}, LevelNS::WINDOW);
    Game_.setCellType({2, 0}, LevelNS::CONTAINER);
    Board_.setScale(ScaleX_, ScaleY);
    update_visible_units_sprite();
    update_sprite(ActiveUnitSprite_, Game_.getPlayerType(), Game_.getActivePlayerCoord());
    update_visible_cells_sprite();
    NextRoundButtonTexture_.loadFromFile("../models/NextRound.JPG");
    auto next_round_button = tgui::Button::create();
    next_round_button->setPosition(640, 640);
    next_round_button->setSize(260, 160);
    next_round_button->getRenderer()->setTexture(NextRoundButtonTexture_);
    next_round_button->onPress(&UI::GameController::next_round_button_callback, this);
    ptrGUI_->add(next_round_button);

}

void UI::GameController::to_view(sf::RenderWindow &window) {
    update_unit_info_block();
    window.draw(Board_);
    window.draw(ActiveUnitSprite_);
    for (auto &enemy_sprite: EnemySprite_) {
        window.draw(enemy_sprite.first);
    }
    for (auto &friend_sprite: TeamSprite_) {
        window.draw(friend_sprite);
    }
    ptrGUI_->draw();
}


void UI::GameController::change_unit_texture(const EntityNS::EntityType &newEntityType, sf::Sprite &sprite) {

    switch (newEntityType) {

        case EntityNS::OPERATIVE:
            sprite.setTextureRect(sf::IntRect(0, 96, 32, 32));
            break;
        case EntityNS::WILD_CREATURE:
            sprite.setTextureRect(sf::IntRect(0, 704, 32, 32));
            break;
        case EntityNS::INTELLIGENT_CREATURE:
            sprite.setTextureRect(sf::IntRect(0, 192, 32, 32));
            break;
        case EntityNS::FORAGER:
            sprite.setTextureRect(sf::IntRect(0, 224, 32, 32));
            break;
    }
}

void UI::GameController::move_handler(GameNS::Game::MoveDirectionType moveDirection) {
    try {
        Game_.move_direction(moveDirection);
        update_visible_units_sprite();
        update_sprite(ActiveUnitSprite_, Game_.getPlayerType(), Game_.getActivePlayerCoord());
        update_visible_cells_sprite();
    } catch (std::exception &exception) {
        message_box(exception.what());
    }
}

void UI::GameController::update_visible_cells_sprite() {
    Board_.to_default();
    auto cells_to_show = Game_.getVisibleCells();
    for (auto &cell: cells_to_show) {
        Board_.reset_type(Game_.getCellType(cell), cell);
    }
}


void UI::GameController::message_box(const std::string &msg, const std::string &title) {
    auto messageBox = tgui::MessageBox::create(title);
    messageBox->setText(msg);
    messageBox->addButton("OK");
    messageBox->setPosition(320, 320);
    auto &ref = AnyWarning;
    ref = true;
    messageBox->onButtonPress([msgBox = messageBox.get(), &ref](const tgui::String &button) {
        msgBox->getParent()->remove(msgBox->shared_from_this());
        ref = false;
    });
    ptrGUI_->add(messageBox);
}


void UI::GameController::show_inventory(UI::GameController::InventoryViewType type) {
    auto panel = tgui::ScrollablePanel::create();
    panel->setSize(640, 160);
    panel->setPosition(0, 640);
    std::vector<const ItemNS::Item *> items_to_view;
    std::string text_to_throw;
    try {
        switch (type) {
            case GROUND:
                panel->getRenderer()->setBackgroundColor(tgui::Color(162, 101, 62, 200));
                items_to_view = Game_.show_items_ground();
                text_to_throw = "Take";
                break;
            case CONTAINER:
                panel->getRenderer()->setBackgroundColor(tgui::Color(170, 169, 173, 200));
                items_to_view = Game_.show_items_container();
                text_to_throw = "Take";
                break;
            case PERSON:
                panel->getRenderer()->setBackgroundColor(tgui::Color(255, 223, 196, 200));
                items_to_view = Game_.show_items_player();
                text_to_throw = "Throw";
                break;
        }
        int i = 0;
        for (auto &item: items_to_view) {
            auto horiWrap = tgui::Grid::create();

            auto label = tgui::Label::create(item->GetTitle());
            horiWrap->addWidget(label, 0, 0);
            auto button_info = tgui::Button::create("description");
            button_info->onPress(&UI::GameController::message_box, this, item->toString(), "DESCRIPTION");
            horiWrap->addWidget(button_info, 0, 1);

            auto button_throw_ground = tgui::Button::create(text_to_throw);
            button_throw_ground->onPress(&UI::GameController::remove_from_inventory_menu, this, type, i, 1);
            horiWrap->addWidget(button_throw_ground, 0, 2);

            if (type == PERSON) {
                if (Game_.getMyCell() == LevelNS::CONTAINER) {
                    auto button_throw_container = tgui::Button::create(text_to_throw + " in container");
                    button_throw_container->onPress(&UI::GameController::remove_from_inventory_menu, this, type, i, 0);
                    horiWrap->addWidget(button_throw_container, 0, 3);
                }
                auto button_use = tgui::Button::create("use");
                horiWrap->addWidget(button_use, 0, 4);
                button_use->onPress(&UI::GameController::use_button_callback, this, i);
            }

            horiWrap->setPosition(0, i * 30);
            panel->add(horiWrap);
            i++;
        }
        ptrGUI_->add(panel);
        CurrentInventory_ = panel;
        InventoryOpen = true;
    } catch (std::exception &exception) {
        message_box(exception.what());
    }

}

bool UI::GameController::isHandling() const {
    return !AnyWarning;
}


void UI::GameController::update_visible_units_sprite() {
    auto visible_cells = Game_.getVisibleCells();
    auto enemies = Game_.find_enemy(visible_cells);
    EnemySprite_.clear();
    TeamSprite_.clear();
    for (auto &unit: enemies) {
        sf::Sprite sprite;
        sprite.setTexture(SpriteTexture_);
        update_sprite(sprite, unit->getType(), unit->getPos());
        EnemySprite_.emplace_back(sprite, unit);
    }
    auto friends = Game_.getTeammates();
    for (auto &[pos, type]: friends) {
        sf::Sprite sprite;
        sprite.setTexture(SpriteTexture_);
        update_sprite(sprite, type, pos);
        TeamSprite_.emplace_back(sprite);
    }

}

void UI::GameController::update_sprite(sf::Sprite &sprite, const EntityNS::EntityType &newEntityType,
                                       std::pair<int, int> new_pos) {
    change_unit_texture(newEntityType, sprite);
    sprite.setScale(ScaleX_ * 0.75, ScaleY * 0.75);
    auto [i, j] = new_pos;
    sprite.setPosition(j * Board_.getTileSize().x * ScaleX_, i * Board_.getTileSize().y * ScaleY);
}

void UI::GameController::attack_handler(float mouse_x, float mouse_y) {
    for (auto &unit: EnemySprite_) {
        if (unit.first.getGlobalBounds().contains(mouse_x, mouse_y)) {
            try {
                Game_.shot(unit.second->getPos(), unit.second);
            } catch (std::exception &exception) {
                message_box(exception.what());
            }
            break;
        }
    }
    update_visible_cells_sprite();
    update_visible_units_sprite();
}

bool UI::GameController::isInventoryOpen() const {
    return InventoryOpen;
}

void UI::GameController::close_inventory() {
    ptrGUI_->remove(CurrentInventory_);
    InventoryOpen = false;
}

void UI::GameController::remove_from_inventory_menu(UI::GameController::InventoryViewType type, int index, int flag) {
    try {
        switch (type) {
            case UI::GameController::GROUND:
                Game_.take_item_ground(index);
                break;
            case UI::GameController::CONTAINER:
                Game_.take_item_container(index);
                break;
            case UI::GameController::PERSON:
                (flag) ? Game_.throw_item_ground(index) : Game_.throw_item_container(index);
                break;
        }
        close_inventory();
        show_inventory(type);
    } catch (std::exception &ex) {
        message_box(ex.what());
    }
}

void UI::GameController::update_unit_info_block() {
    ptrGUI_->remove(CurrentUnitInfo_);
    auto panel = tgui::ScrollablePanel::create();
    panel->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 0));
    panel->getRenderer()->setTextSize(20);
    panel->setSize(260, 640);
    panel->setPosition(637, 0);
    auto health_bar = create_progress_bar(Game_.getActivePlayerHealth(), "Health: ", tgui::Color::Red);
    auto time_bar = create_progress_bar(Game_.getActivePlayerTime(), "Time: ", tgui::Color::Green);
    time_bar->setPosition(0, 30);
    auto info = tgui::RichTextLabel::create();
    info->setHorizontalAlignment(tgui::RichTextLabel::HorizontalAlignment::Center);
    info->setText("<b><u>Description:</u></b>\n" + Game_.getActivePlayerDesc());
    info->setPosition(0, 90);
    info->setSize(260, 400);
    panel->add(health_bar);
    panel->add(time_bar);
    panel->add(info);
    ptrGUI_->add(panel);
    CurrentUnitInfo_ = panel;
}

tgui::ProgressBar::Ptr
UI::GameController::create_progress_bar(std::pair<int, int> data, const std::string &text, tgui::Color color) {
    auto bar = tgui::ProgressBar::create();
    auto [cur, max] = data;
    bar->setText(text + std::to_string(cur) + "/" + std::to_string(max));
    bar->getRenderer()->setFillColor(color);
    bar->setMinimum(0);
    bar->setMaximum(max);
    bar->setValue(cur);
    return bar;
}

void UI::GameController::use_button_callback(int index) {
    try {
        Game_.use(index);
        close_inventory();
        show_inventory(InventoryViewType::PERSON);
    }
    catch (std::exception &ex) {
        message_box(ex.what());
    }
}

void UI::GameController::change_player_handler(bool next) {
    if (next) {
        Game_.next_player();
    } else {
        Game_.prev_player();
    }
    update_visible_units_sprite();
    update_sprite(ActiveUnitSprite_, Game_.getPlayerType(), Game_.getActivePlayerCoord());
    update_visible_cells_sprite();
}

void UI::GameController::enemy_info_handler(float mouse_x, float mouse_y) {
    for (auto &unit: EnemySprite_) {
        if (unit.first.getGlobalBounds().contains(mouse_x, mouse_y)) {
            message_box(unit.second->toString(), "Enemy description");
            break;
        }
    }

}

void UI::GameController::next_round_button_callback() {
    if (isInventoryOpen()) close_inventory();
    bool isGameOver = Game_.next_team();
    if (isGameOver) {
        message_box("Game over. Your team win!", "WIN");
    } else {
        update_visible_units_sprite();
        update_sprite(ActiveUnitSprite_, Game_.getPlayerType(), Game_.getActivePlayerCoord());
        update_visible_cells_sprite();
    }

}










