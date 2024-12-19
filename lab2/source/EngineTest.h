#pragma once
#include <iostream>
#include <vector>
#include <engine/Engine.h>


class EngineTest {
public:
    static void testCommands() {
        Engine::inst().execute<void>(
            "replace",
            {{"with", std::string("hii~")}, {"what", std::string("Дети")}}
        );
        auto indices = Engine::inst().execute<std::vector<std::size_t> >(
            "find",
            {
                {"phrase", std::string("hii~")}
            });
        Engine::inst().execute<void>("capSentence", {{"pos", 180ull}});
        Engine::inst().execute<void>("capWords", {{"beginPos", 2ull}, {"endPos", 70ull}});
        Engine::inst().execute<void>("addSentenceNumbering", {});


        std::cout <<
                Engine::inst().execute<std::string>("getContent", {})
                << std::endl;

        for (int index: indices) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
};
