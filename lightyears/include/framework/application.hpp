#include <string>
#include <SFML/Graphics.hpp>

namespace ly{
    class Application{
        public:
            Application(std::string title,unsigned int width,unsigned int height);
            void run();
        private:
            sf::RenderWindow m_window;
    };
}