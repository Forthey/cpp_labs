#include "Engine.h"

#include <fstream>
#include <sstream>
#include <document/DocumentEditor.h>


std::string getFileContent(std::string const &filePath) {
    std::ifstream testFile(filePath);

    if (!testFile.is_open()) {
        throw std::runtime_error("Test file not found");
    }

    std::stringstream sstream;
    sstream << testFile.rdbuf();
    return sstream.str();
}

DocumentEditor editor(getFileContent("test.txt"));
Wrapper replaceWrapper(&editor, &DocumentEditor::replace, {"what", "with"});
Wrapper findWrapper(&editor, &DocumentEditor::find, {"phrase"});
Wrapper capSentenceWrapper(&editor, &DocumentEditor::capitalizeSentence, {"pos"});
Wrapper capWordsWrapper(&editor, &DocumentEditor::capitalizeWords, {"beginPos", "endPos"});
Wrapper addSentenceNumberingWrapper(&editor, &DocumentEditor::addSentenceNumbering, {});
Wrapper getContentWrapper(&editor, &DocumentEditor::getContent, {});

void registerCommands(Engine &engine) {
    engine
            .registerCommand("replace", &replaceWrapper)
            .registerCommand("find", &findWrapper)
            .registerCommand("capSentence", &capSentenceWrapper)
            .registerCommand("capWords", &capWordsWrapper)
            .registerCommand("addSentenceNumbering", &addSentenceNumberingWrapper)
            .registerCommand("getContent", &getContentWrapper);
}


Engine::Engine() {
    registerCommands(*this);
}


Engine &Engine::inst() {
    static Engine engine;

    return engine;
}
