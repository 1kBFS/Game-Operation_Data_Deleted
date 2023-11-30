//
// Created by Pavel on 28.11.2023.
//

#ifndef LAB3_TILE_MAP_H
#define LAB3_TILE_MAP_H

#include <SFML/Graphics.hpp>
#include "../Game/Game.h"

namespace UI {
    class TileMap : public sf::Drawable, public sf::Transformable {
    public:
        TileMap() = default;

        TileMap(const std::string &tileset_filename, sf::Vector2u tileSize, unsigned int width,
                unsigned int height);

        void reset_type(const LevelNS::CellType &new_type, const std::pair<int, int> &cell);

        void to_default();

        const sf::Vector2u &getTileSize() const;

    private:
        //! author method
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &TileSetTexture_;
            target.draw(Vertices_, states);
        }

        static int type_to_number(const LevelNS::CellType &cell_type);

        unsigned int Width_;
        unsigned int Height_;

        sf::VertexArray Vertices_;
        sf::Texture TileSetTexture_;
        sf::Vector2u TileSize_;
    };
}


#endif //LAB3_TILE_MAP_H
