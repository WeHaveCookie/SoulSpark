#include "../include/Controller.hpp"

Controller::Controller(sf::RenderWindow* window, Character* character, Quadtree* world, FireWall* wall)
{
    m_window = window;
    m_player = character;
    m_world = world;
    m_fireWall = wall;
    m_menu = new Menu();
    m_displayMenu = false;
    m_view = m_window->getDefaultView();
    //ctor
}

Controller::~Controller()
{
    delete m_window;
    delete m_player;
    delete m_fireWall;
    delete m_menu;
    //dtor        sf::RenderWindow* m_window;
}

int Controller::start()
{

    bool move = false;//indicate whether motion is detected
	int turbo = 1;//indicate whether player is using button for turbo speed ;)
    //for movement
	sf::Vector2f speed = sf::Vector2f(0.f,0.f);

	//time
	sf::Clock tickClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time duration = sf::Time::Zero;

    while (m_window->isOpen())
    {
        // On catch les events
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    m_window->close();
                    break;
                case sf::Event::KeyPressed :
                    {
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape :
                                m_window->close();
                                break;
                            case sf::Keyboard::A :
                                m_displayMenu = true;
                                break;
                            default :
                                break;
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed :
                    {
                        switch(event.mouseButton.button)
                        {
                        case sf::Mouse::Left :
                                if(m_displayMenu)
                                {
                                    std::cout << "Catch click" << std::endl;
                                    sf::Vector2i cursor = sf::Mouse::getPosition(*m_window);
                                    sf::FloatRect rect;
                                    rect.left = cursor.x;
                                    rect.top = cursor.y;
                                    rect.width = 10.0f;
                                    rect.height = 10.0f;
                                    SelectedLevel level = m_menu->selectLevel(rect);
                                    if(level != SelectedLevel::NONE)
                                    {
                                        m_level = level;
                                        m_displayMenu = false;
                                        std::cout << "load level : " << m_level << std::endl;
                                    }
                                }
                            break;
                        case sf::Mouse::Right:
                            break;
                        default:
                            break;
                        }
                    }
                    break;
                default :
                    break;
            }
            if (event.type == sf::Event::JoystickMoved){
				move = true;
				//std::cout << "X axis: " << speed.x << std::endl;
				//std::cout << "Y axis: " << speed.y << std::endl;
            }
            else{
                move = false;
            }
        }

        /** AJOUT DE CODE**/


        if (sf::Joystick::isButtonPressed(0, 0)){//"A" button on the XBox 360 controller
            turbo = 2;
        }

        if (!sf::Joystick::isButtonPressed(0, 0)){
            turbo = 1;
        }

        if(sf::Joystick::isButtonPressed(0,1)){//"B" button on the XBox 360 controller
            m_window->close();
            return 0;
        }

        m_window->clear();
        if(m_displayMenu)
        {
            m_menu->draw(m_window);
        } else
        {

             //check state of joystick
            speed = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));

            timeSinceLastUpdate += tickClock.restart();
            while (timeSinceLastUpdate > TimePerFrame)
            {
                timeSinceLastUpdate -= TimePerFrame;

                //update the position of the square according to input from joystick
                //CHECK DEAD ZONES - OTHERWISE INPUT WILL RESULT IN JITTERY MOVEMENTS WHEN NO INPUT IS PROVIDED
                //INPUT RANGES FROM -100 TO 100
                //A 15% DEAD ZONE SEEMS TO WORK FOR ME - GIVE THAT A SHOT
                if (speed.x > 15.f || speed.x < -15.f || speed.y > 15.f || speed.y < -15.f)
                {
                    m_player->move(sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(), turbo*speed.y*TimePerFrame.asSeconds()),m_world);
                }
            }



            /** END **/

            float decPlayer = m_player->getSprite().getGlobalBounds().left - m_view.getCenter().x;
            if((m_view.getSize().x/2) + decPlayer > (m_view.getSize().x*0.66))
            {
                m_view.move(sf::Vector2f(sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(),0)));
                m_fireWall->move(sf::Vector2f(sf::Vector2f(turbo*speed.x*TimePerFrame.asSeconds(),0.0)));
            }
            m_view.move(1,0);
            m_window->setView(m_view);
            m_player->draw(m_window);
            m_world->draw(m_window);
            m_fireWall->draw(m_window);

        }
        m_window->display();
    }
}

void Controller::update()
{

}
