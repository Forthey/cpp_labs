#pragma once
#include <set>
#include <string>
#include <vector>

class DocumentEditor {
    static std::set<char> const sentenceDelimiters;

    std::string content;
public:
    explicit DocumentEditor(std::string content);

    void replace(std::string const &what, std::string const &with);

    std::vector<std::size_t> find(std::string const &phrase);

    void capitalizeWords(std::size_t beginPos, std::size_t endPos);

    void capitalizeSentence(std::size_t pos);

    std::string getContent() { return content; }

    void addSentenceNumbering();
};
