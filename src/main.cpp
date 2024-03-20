#define DO_STACK_QUEUE_UNIT_TESTS 0
#if DO_STACK_QUEUE_UNIT_TESTS
#include <gtest/gtest.h>
#else
#include <SFML/Graphics.hpp>
#include <text_circle.h>
#include <iostream>
#include <word_drawer.h>
#endif

int main()
{
#if DO_STACK_QUEUE_UNIT_TESTS
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else

    printf("hi :)");
    /*const unsigned int win_width = 1000, win_height = 800;
    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "SFML works!");
    sf::Font circle_font;
    if (!circle_font.loadFromFile("../../../media/fonts/Lato/Lato-Black.ttf"))
        std::cout << "Error opening font file\n";
    
    misc::WordDrawer WD("../../../media/SCOWL/final/american-words.80", circle_font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!WD.handle_event(event))
                window.close();
        }

        window.clear();
        WD.draw(window);
        window.display();
    }

    return 0;*/
#endif
}