//
// Created by Pavel on 28.11.2023.
//

#include "Game_Controller.h"

#include <utility>
#include "../Entities/Operative.h"
#include "../Entities/Forager.h"

UI::GameController::GameController(const std::string &config_filename, std::shared_ptr<tgui::Gui> ptr_gui) : ptrGUI_(
        std::move(
                ptr_gui)) {
    // временное решение
    TeamNS::Team A("Operative");
    TeamNS::Team B("Creatures");
    auto operative_unit = std::make_shared<EntityNS::Operative>("default");
    operative_unit->setCurTime(10);
    operative_unit->setVisibilityRadius(1);
    InventoryNS::Inventory loaded_inventory_unit;
    loaded_inventory_unit.push_back(std::make_unique<WeaponNS::Weapon>("AK-47", 1, 1, 1));
    operative_unit->setInvetnory(std::move(loaded_inventory_unit));
    A.push_back(std::move(operative_unit));

    auto creature_unit = std::make_shared<EntityNS::Forager>("default");
    creature_unit->setCurHeatPoint(2);
    creature_unit->setAvaliableTime(3);
    creature_unit->setPos({1, 0});
    InventoryNS::Inventory loaded_inventory_creature;
    loaded_inventory_creature.push_back(std::make_unique<WeaponNS::Weapon>("MP4-A1", 1, 1, 1));
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
    Board_.setScale(ScaleX_, ScaleY);
    update_unit_sprite();
    update_visible_cells_sprite();
}

void UI::GameController::to_view(sf::RenderWindow &window) {
    window.draw(Board_);
    window.draw(ActiveUnitSprite_);
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

void UI::GameController::update_unit_sprite() {
    change_unit_texture(Game_.getPlayerType(), ActiveUnitSprite_);
    ActiveUnitSprite_.setScale(ScaleX_ * 0.75, ScaleY * 0.75);
    auto [i, j] = Game_.getActivePlayerCoord();
    std::cout << i << " " << j << "\n";
    ActiveUnitSprite_.setPosition(j * Board_.getTileSize().x * ScaleX_, i * Board_.getTileSize().y * ScaleY);
}

void UI::GameController::move_handler(GameNS::Game::MoveDirectionType moveDirection) {
    try {
        Game_.move_direction(moveDirection);
    } catch (std::exception &exception) {
        error_box(exception.what());
    }
    update_unit_sprite();
    update_visible_cells_sprite();
}

void UI::GameController::update_visible_cells_sprite() {
    Board_.to_default();
    auto cells_to_show = Game_.getVisibleCells();
    for (auto &cell: cells_to_show) {
        Board_.reset_type(Game_.getCellType(cell), cell);
    }
}

void closeWindow();

void UI::GameController::error_box(const std::string &msg) {
    auto messageBox = tgui::MessageBox::create("WARNING");
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

bool UI::GameController::isHandling() const {
    return !AnyWarning;
}
