#include <iostream>
#include "../include/Parser.h"
#include "../include/Tokenizer.h"
#include "../include/ASTVisitor.h"

int main() {
    std::string filename;
    std::cin >> filename;
    Midi midi = MidiReader::read(filename);
    Tokenizer tokenizer(*midi.begin());

    ASTPrinter printer;

    Parser parser(tokenizer);
    Parser::ParserIterator it = parser.begin();
    while(it) {
        auto result = *it;
        if (_check(result)) {
            std::cout << "WTFFF" << std::endl;
            ErrorHandler::printError(std::get<Error>(result));
            break;
        }

        std::get<Statement_t>(result)->accept(printer);
        ++it;
    }

    std::cout << "--------------- FINAL PRINT ---------------" << std::endl;
    parser.program->accept(printer);
    return 0;
}