//
// Created by Pavel on 28.11.2023.
//

#include "Tile_Map.h"

int UI::TileMap::type_to_number(const LevelNS::CellType &cell_type) {
    switch (cell_type) {

        case LevelNS::FLOOR:
            return 0;
            break;
        case LevelNS::WALL:
            return 1;
            break;
        case LevelNS::WINDOW:
            return 2;
            break;
        case LevelNS::BARRIER:
            return 5;
            break;
        case LevelNS::CONTAINER:
            return 3;
            break;
        case LevelNS::FOG:
            return 4;
            break;
    }
}

UI::TileMap::TileMap(const std::string &tileset_filename, sf::Vector2u tileSize, unsigned int width,
                     unsigned int height) : Width_(width), Height_(height), TileSize_(tileSize) {
    if (!TileSetTexture_.loadFromFile(tileset_filename))
        throw std::runtime_error("Unable to read texture.");
    Vertices_.setPrimitiveType(sf::Triangles);
    Vertices_.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j) {
            int tileNumber = 4;

            // find its position in the tileset texture
            int tu = tileNumber % (TileSetTexture_.getSize().x / tileSize.x);
            int tv = tileNumber / (TileSetTexture_.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            sf::Vertex *triangles = &Vertices_[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
            triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
}

void UI::TileMap::reset_type(const LevelNS::CellType &new_type, const std::pair<int, int> &cell) {
    auto [j, i] = cell;
    sf::Vertex *triangles = &Vertices_[(i + j * Width_) * 6];
    int tu = type_to_number(new_type) % (TileSetTexture_.getSize().x / TileSize_.x);
    int tv = type_to_number(new_type) / (TileSetTexture_.getSize().x / TileSize_.x);


    // define the 6 corners of the two triangles
    triangles[0].position = sf::Vector2f(i * TileSize_.x, j * TileSize_.y);
    triangles[1].position = sf::Vector2f((i + 1) * TileSize_.x, j * TileSize_.y);
    triangles[2].position = sf::Vector2f(i * TileSize_.x, (j + 1) * TileSize_.y);
    triangles[3].position = sf::Vector2f(i * TileSize_.x, (j + 1) * TileSize_.y);
    triangles[4].position = sf::Vector2f((i + 1) * TileSize_.x, j * TileSize_.y);
    triangles[5].position = sf::Vector2f((i + 1) * TileSize_.x, (j + 1) * TileSize_.y);

    // define the 6 matching texture coordinates
    triangles[0].texCoords = sf::Vector2f(tu * TileSize_.x, tv * TileSize_.y);
    triangles[1].texCoords = sf::Vector2f((tu + 1) * TileSize_.x, tv * TileSize_.y);
    triangles[2].texCoords = sf::Vector2f(tu * TileSize_.x, (tv + 1) * TileSize_.y);
    triangles[3].texCoords = sf::Vector2f(tu * TileSize_.x, (tv + 1) * TileSize_.y);
    triangles[4].texCoords = sf::Vector2f((tu + 1) * TileSize_.x, tv * TileSize_.y);
    triangles[5].texCoords = sf::Vector2f((tu + 1) * TileSize_.x, (tv + 1) * TileSize_.y);
}

const sf::Vector2u &UI::TileMap::getTileSize() const {
    return TileSize_;
}

void UI::TileMap::to_default() {
    for (int i = 0; i < Height_; i++) {
        for (int j = 0; j < Width_; j++) {
            reset_type(LevelNS::FOG, {j, i});
        }
    }
    reset_points_of_interest();
}

void UI::TileMap::add_point_of_interest(std::pair<int, int> cell, std::pair<int, int> scale) {
    auto sprite = sf::CircleShape(3);
    sprite.setFillColor(sf::Color::Yellow);
    sprite.setOutlineThickness(1);
    sprite.setOutlineColor(sf::Color::Black);
    sprite.setPosition((cell.second)*TileSize_.x, cell.first*TileSize_.y);
    std::cout << "POINT coords: " <<cell.first << " " << cell.second << "\n";
    std::cout << "POINT: " << sprite.getPosition().x << " " << sprite.getPosition().y << "\n";
    point_of_interest.push_back(sprite);
}

void UI::TileMap::reset_points_of_interest() {
    point_of_interest.clear();
}





