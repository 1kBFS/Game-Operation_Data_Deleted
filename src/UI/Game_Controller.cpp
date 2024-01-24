//
// Created by Pavel on 28.11.2023.
//

#include "Game_Controller.h"

#include <utility>
#include "../Game/GameConfig.h"
UI::GameController::GameController(const std::string &config_filename, std::shared_ptr<tgui::Gui> ptr_gui) : ptrGUI_(
        std::move(
                ptr_gui)) {

    GameNS::GameConfig gameLoader;
    Game_ = gameLoader.configure_game("../files/configs/test.json");
    auto [height, width] = Game_.getLevelSize();
    ScaleX_ = 10.0 / width;
    ScaleY_ = 10.0 / height;
    TileMap temp_map("../files/models/texture.png", sf::Vector2u(64, 64), width, height);
    SpriteTexture_.loadFromFile("../files/models/units.png");
    ActiveUnitSprite_.setTexture(SpriteTexture_);
    Board_ = std::move(temp_map);
    Board_.setScale(ScaleX_, ScaleY_);
    update_visible_units_sprite();
    update_sprite(ActiveUnitSprite_, Game_.getPlayerType(), Game_.getActivePlayerCoord());
    update_visible_cells_sprite();
    NextRoundButtonTexture_.loadFromFile("../files/models/NextRound.JPG");
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
    for (size_t i = 0; i < EnemySprite_.size(); i++) {
        window.draw(EnemySprite_[i].first);
        window.draw(EnemyHealthBarSprite_[i]);
    }
    for (size_t i = 0; i < TeamSprite_.size(); i++) {
        window.draw(TeamSprite_[i]);
        window.draw(TeamHealthBarSprite_[i]);
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
        if (!Game_.isCellEmpty(cell))
            Board_.add_point_of_interest(cell, {ScaleX_, ScaleY_});
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
    EnemyHealthBarSprite_.clear();
    TeamSprite_.clear();
    TeamHealthBarSprite_.clear();
    for (auto &unit: enemies) {
        sf::Sprite sprite;
        sprite.setTexture(SpriteTexture_);
        update_sprite(sprite, unit->getType(), unit->getPos());
        EnemySprite_.emplace_back(sprite, unit);
        // std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << "\n";
        EnemyHealthBarSprite_.push_back(HealthBar({unit->getCurHeatPoint(), unit->getMaxHeatPoint()}, {ScaleX_, ScaleY_},
                                                  sprite.getPosition()));

    }
    auto friends = Game_.getTeammates();
    for (auto &unit: friends) {
        sf::Sprite sprite;
        sprite.setTexture(SpriteTexture_);
        update_sprite(sprite, unit->getType(), unit->getPos());
        TeamSprite_.emplace_back(sprite);
        TeamHealthBarSprite_.push_back(HealthBar({unit->getCurHeatPoint(), unit->getMaxHeatPoint()}, {ScaleX_, ScaleY_},
                                                 sprite.getPosition(), sf::Color::Green));
    }


}

void UI::GameController::update_sprite(sf::Sprite &sprite, const EntityNS::EntityType &newEntityType,
                                       std::pair<int, int> new_pos) {
    change_unit_texture(newEntityType, sprite);
    sprite.setScale(ScaleX_ * 0.75, ScaleY_ * 0.75);
    auto [i, j] = new_pos;
    sprite.setPosition(j * Board_.getTileSize().x * ScaleX_, i * Board_.getTileSize().y * ScaleY_);
}

void UI::GameController::attack_handler(float mouse_x, float mouse_y) {
    for (auto &unit: EnemySprite_) {
        if (unit.first.getGlobalBounds().contains(mouse_x, mouse_y)) {
            try {
                Game_.attack(unit.second);
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






