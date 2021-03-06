#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

#include "Engine.hpp"
#include "Character.hpp"
#include "DarkSoul.hpp"
#include "Menu.hpp"
#include "Structure.hpp"
#include "Level.hpp"
#include "Sprint.hpp"

class Character;
class Engine;
class Menu;

class Controller
{
    public:
        Controller(sf::RenderWindow* window);
        virtual ~Controller();

        // Function
        int start();
        void setLevel(std::string path);
        void getRune(int pos);
        void displayRune();
        void growSpeed();
        void displayDarkSouls();
        void moveSouls(sf::Vector2f motion);

        // Inline
        inline sf::RenderWindow* getWindow() {return m_window;}
        inline void displayMenu(bool b) {m_displayMenu = b;}
        inline Level* getLevel() {return m_level;}

    protected:
    private:
        // Function
        void update();
        void updateMusic();
        void reload();
        void init();
        void drawViewGame();
        void drawViewHUD();
        void drawViewMenu();


        // Attribut
        sf::RenderWindow* m_window;
        Character* m_player;
        std::vector<DarkSoul*> m_darksouls;
        Menu* m_menu;
        Sprint* m_sprint;
        bool m_displayMenu;
        bool m_displayPause;
        sf::View m_viewGame;
        sf::View m_viewHUD;
        sf::View m_viewMenu;

        Level* m_level;
        Engine* m_engine;

        //Sound
        sf::Music m_mainThemeMusic;
        sf::Music m_menuMusic;
        sf::Music m_creditsMusic;
        sf::Music m_endMusic;

        std::vector<Rune*> m_runes;
        bool m_victory;
        sf::Sprite m_filterPause;
        sf::Texture m_textureFilterPause;
        std::vector<sf::Sprite> m_runeHUD;
        sf::Texture m_runeTexture;
        bool m_transitionMusic;
        int m_counterTransitionMusic;
        sf::Music m_pickupRuneSound;

        float m_viewSpeed;
        float m_darksoulsSpeed;
        float m_speedPlayer;
        float m_pitchMainTheme;
        float m_pitchEnd;
        float m_exhaust;
};

#endif // CONTROLLER_HPP
