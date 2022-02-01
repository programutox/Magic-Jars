#ifndef SRC_CHAP_ASSETS_MANAGER_HPP
#define SRC_CHAP_ASSETS_MANAGER_HPP

#include "raylib-cpp.hpp"

#include <map>
#include <memory>
#include <type_traits>
#include <string>

#include "Assets.hpp"
#include "Button.hpp"

namespace chap
{
    class AssetsManager
    {
    public:
        AssetsManager(const std::string &p_imgFolder, const std::string &p_sfxFolder, const std::string &p_musicFolder)
            : m_textures{ p_imgFolder, ".png" }, m_sounds{ p_sfxFolder, ".wav" }, m_musics{ p_musicFolder }
        {
            
        }

        template<typename T>
        void Add(const std::string &p_id, const std::string &p_fileName="")
        {
            if (std::is_same_v<T, rl::Texture2D>)
            {
                m_textures.Add(p_id, p_fileName);
            }
            else if (std::is_same_v<T, rl::Sound>)
            {
                m_sounds.Add(p_id, p_fileName);
            }
            else if (std::is_same_v<T, rl::Music>)
            {
                m_musics.Add(p_id, p_fileName);
                m_musics.Get(p_id).Seek(0);
            }
        }

        // Emplaces a rectangle (for a texture)
        void Add(const std::string &p_id, const rl::Rectangle &p_rect)
        {
            if (!this->Exists<rl::Rectangle>(p_id))
            {
                m_rects.emplace(p_id, p_rect);
            }
        }
        
        // Emplaces a button
        void AddButton(const std::string &p_id, const std::string &p_textureId, const rl::Vector2 &p_pos)
        {
            if (!this->Exists<Button>(p_id))
            {
                m_buttons.emplace(p_id, Button{ this->GetTexture(p_textureId), p_pos });
            }
        }

        void AddButton(const std::string &p_id, const std::string &p_textureId, const rl::Rectangle &p_srcRect, const rl::Vector2 &p_pos)
        {
            if (!this->Exists<Button>(p_id))
            {
                m_buttons.emplace(p_id, Button{ this->GetTexture(p_textureId), p_srcRect, p_pos });
            }
        }

        const rl::Texture2D &GetTexture(const std::string &p_id) const noexcept { return m_textures.Get(p_id); }
        rl::Texture2D &GetTexture(const std::string &p_id) noexcept             { return m_textures.Get(p_id); }

        const rl::Sound &GetSound(const std::string &p_id) const noexcept       { return m_sounds.Get(p_id); }
        rl::Sound &GetSound(const std::string &p_id) noexcept                   { return m_sounds.Get(p_id); }

        const rl::Music &GetMusic(const std::string &p_id) const noexcept       { return m_musics.Get(p_id); }
        rl::Music &GetMusic(const std::string &p_id) noexcept                   { return m_musics.Get(p_id); }

        const rl::Rectangle &GetRect(const std::string &p_id) const noexcept    { return m_rects.at(p_id); }
        rl::Rectangle &GetRect(const std::string &p_id) noexcept                { return m_rects.at(p_id); }

        const Button &GetButton(const std::string &p_id) const noexcept         { return m_buttons.at(p_id); }
        Button &GetButton(const std::string &p_id) noexcept                     { return m_buttons.at(p_id); }

        template<typename T>
        bool Exists(const std::string &p_id)
        {
            if (std::is_same_v<T, rl::Texture2D>)
            {
                return m_textures.Exists(p_id);
            }
            else if (std::is_same_v<T, rl::Sound>)
            {
                return m_sounds.Exists(p_id);
            }
            else if (std::is_same_v<T, rl::Music>)
            {
                return m_musics.Exists(p_id);
            }
            else if (std::is_same_v<T, rl::Rectangle>)
            {
                return m_rects.find(p_id) != m_rects.end();
            }
            else if (std::is_same_v<T, Button>)
            {
                return m_buttons.find(p_id) != m_buttons.end();
            }

            return false;
        }

    private:
        Assets<rl::Texture2D> m_textures;
        Assets<rl::Sound> m_sounds;
        Assets<rl::Music> m_musics;
        Dictionary<rl::Rectangle> m_rects;
        Dictionary<Button> m_buttons;
    };
} // namespace chap

#endif // SRC_CHAP_ASSETS_MANAGER_HPP
