#pragma once
#include <fstream>
#include <set>
#include <string>
#include <vector>


/**
 * Represents a text document editor with functionalities for modifying and analyzing document content.
 */
class DocumentEditor {
    static std::set<char> const sentenceDelimiters; ///< Set of characters used as sentence delimiters (e.g., '.', '!', '?').

    std::string const filename; ///< Name of the file associated with the document.
    std::string content; ///< The content of the document stored in memory.
    std::fstream document; ///< File stream for reading from and writing to the document file.
public:
    /**
     * This constructor initializes the `filename` and opens the associated file using an `fstream` object
     * for reading and writing. It allows the editor to work with the content of the specified document file.
     *
     * @param filename The name of the file to associate with the document editor.
     */
    explicit DocumentEditor(std::string filename) : filename(std::move(filename)), document(filename) {}

    /**
     * Check if the document is open for reading or writing.
     *
     * This method verifies whether the underlying document fstream is currently open.
     *
     * @return `true` if the document is open, or `false` otherwise.
     */
    bool isOpen() const { return document.is_open(); }

    /**
     * Load the content of an open document into memory.
     *
     * Reads the entire content of the document fstream into the `content` string.
     * This method requires the document to be open; otherwise, it returns `false`.
     *
     * @return `true` if the content was successfully loaded, or `false` if the document is not open.
     */
    bool load();

    /**
     * Save the content stored in memory back to the document.
     *
     * Writes the current value of the `content` string into the document fstream.
     * This method requires the document to be open; otherwise, it returns `false`.
     *
     * @return `true` if the content was successfully saved, or `false` if the document is not open.
     */
    bool save();

    /**
     * Close the document and clear its content.
     *
     * This method clears the content stored in the editor and closes the associated document file.
     * It ensures that no content remains in memory and the document is properly closed.
     */
    void close();

    /**
     * Replace all occurrences of a substring in the document content.
     *
     * This method searches the content of the document for all occurrences of the specified substring
     * and replaces them with another specified substring. The replacement is performed in-place.
     *
     * @param what The substring to search for in the content.
     * @param with The substring to replace the found occurrences with.
     */
    void replace(std::string const &what, std::string const &with);

    /**
     * Find all occurrences of a substring in the document content.
     *
     * This method searches for all occurrences of the specified substring within the document content
     * and returns their starting positions as a vector of indices.
     *
     * @param phrase The substring to search for in the content.
     * @return A vector containing the starting positions of all occurrences of the substring.
     *         If no occurrences are found, the vector will be empty.
     */
    std::vector<std::size_t> find(std::string const &phrase);

    /**
     * Capitalize the first letter of each word in a specified range of the document content,
     * expanding the range backward to include incomplete words.
     *
     * This method processes the document content within the specified range, adjusting the
     * starting position (`beginPos`) to include any partially included words. The first letter
     * of each word in the adjusted range is capitalized. A word is defined as a sequence of
     * alphabetic characters separated by non-alphabetic, non-numeric characters.
     *
     * @param beginPos The starting position of the range to process. If it falls within a word,
     *                 the method adjusts it backward to the word's beginning. Out-of-bound values
     *                 are clamped to 0.
     * @param endPos The ending position of the range to process. If out of bounds, it is clamped
     *               to the content size.
     */
    void capitalizeWords(std::size_t beginPos, std::size_t endPos);

    /**
     * Capitalize the first letter of a sentence starting at or containing the specified position.
     *
     * This method capitalizes the first letter of the sentence that starts at or contains the given
     * position in the document content. If the position points to a sentence delimiter, the method
     * exits without making changes. Otherwise, it moves backward to find the beginning of the sentence
     * and capitalizes the first character.
     *
     * @param pos The position within the document content to identify the sentence to capitalize.
     *            If out of bounds or pointing to a sentence delimiter, no changes are made.
     */
    void capitalizeSentence(std::size_t pos);

    /**
     * Add sentence numbering with newlines to the document content.
     *
     * This method processes the document content, adding a number at the beginning of each sentence.
     * Each sentence is numbered sequentially, and the number is followed by a period and a space.
     * The sentence is also appended with a newline character. Sentence boundaries are determined by
     * sentence delimiters (e.g., '.', '!', '?'). The numbering is inserted directly into the content.
     */
    void addSentenceNumbering();

    ~DocumentEditor() { close(); }
};
