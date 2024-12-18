#include "DocumentEditor.h"

#include <set>
#include <sstream>


std::set<char> const DocumentEditor::sentenceDelimiters = {'.', '!', '?'};


DocumentEditor::DocumentEditor(std::string content) : content(std::move(content)) {
}


void DocumentEditor::replace(std::string const &what, std::string const &with) {
    size_t currentPos = 0;
    while ((currentPos = content.find(what, currentPos)) != std::string::npos) {
        content.replace(currentPos, what.length(), with);
        currentPos += with.length();
    }
}


std::vector<std::size_t> DocumentEditor::find(std::string const &phrase) {
    std::vector<std::size_t> phrasesBeginPos;
    size_t currentPos = 0;

    while ((currentPos = content.find(phrase, currentPos)) != std::string::npos) {
        phrasesBeginPos.push_back(currentPos);
        currentPos += phrase.length();
    }

    return phrasesBeginPos;
}


void DocumentEditor::capitalizeWords(std::size_t beginPos, std::size_t endPos) {
    beginPos = std::max(beginPos, 0ull);
    endPos = std::min(endPos, content.size());

    while (beginPos > 0 && (std::isalpha(content[beginPos - 1]) || std::isdigit(content[beginPos - 1]))) {
        beginPos--;
    }

    bool capitalizeNext = true;

    for (std::size_t i = beginPos; i < endPos; i++) {
        char &c = content[i];
        if (std::isalpha(c) && capitalizeNext) {
            c = static_cast<char>(std::toupper(c));
            capitalizeNext = false;
        } else if (!std::isalpha(c) && !std::isdigit(c)) {
            capitalizeNext = true;
        }
    }
}


void DocumentEditor::capitalizeSentence(std::size_t pos) {
    if (sentenceDelimiters.contains(content[pos]) || pos >= content.size()) {
        return;
    }

    while (pos > 0 && !sentenceDelimiters.contains(content[pos - 1])) {
        pos--;
    }
    content[pos] = static_cast<char>(std::toupper(content[pos]));
}


void DocumentEditor::addSentenceNumbering() {
    static auto findPredicate = [&](char c) -> bool { return sentenceDelimiters.contains(c); };

    auto sentenceBegin = content.begin(), sentenceEnd = content.begin();
    std::size_t number = 1;

    while ((sentenceEnd = std::find_if(sentenceEnd, content.end(), findPredicate)) != content.end()) {
        ++sentenceEnd;
        if (!sentenceDelimiters.contains(*sentenceBegin)) {
            auto prevCharIter = (sentenceBegin == content.begin() ? sentenceBegin : std::prev(sentenceBegin));

            std::string formattedSentence = std::format("{}. {}\n", number, std::string(sentenceBegin, sentenceEnd));
            content.replace(sentenceBegin, sentenceEnd, formattedSentence);

            if (prevCharIter == sentenceBegin) {
                sentenceBegin = content.begin();
            } else {
                sentenceBegin = std::next(prevCharIter);
            }
            sentenceEnd = sentenceBegin + formattedSentence.length();
            number++;
        }
        sentenceBegin = sentenceEnd;
    }

    if (sentenceBegin != content.end() && !sentenceDelimiters.contains(*sentenceBegin)) {
        std::string formattedSentence = std::format("{}. {}", number, std::string(sentenceBegin, sentenceEnd));
        content.replace(sentenceBegin, sentenceEnd, formattedSentence);
    }
}
