#include <iostream>

#include "wrapper/Wrapper.h"
#include "document/DocumentEditor.h"

int main() {
    DocumentEditor editor("На улице светило яркое зимнее солнце, отражаясь от белого снега. Дети катались на санках с небольшой горки, смеясь и радуясь каждому мгновению. Ветер приносил с собой запах сосен и далёкого костра, где кто-то грел руки. Птицы кружили над деревьями, выискивая что-то съестное среди ветвей. Этот день казался идеальным, чтобы оставить все заботы и просто наслаждаться моментом.");

    Wrapper wrapper(&editor, &DocumentEditor::addSentenceNumbering, {});
    Wrapper wrapper2(&editor, &DocumentEditor::getContent, {});

    wrapper({}, true);
    std::cout << wrapper2({});
}
