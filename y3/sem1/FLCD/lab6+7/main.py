from grammar import Grammar
from parser_algorithm import ParserAlgorithm
import os


def main():
    grammar_file_path = "g3.txt"
    output_file_path = os.path.splitext(os.path.basename(grammar_file_path))[0] + ".out.txt"
    word = ["a", "a", "c", "b", "c"]

    grammar = Grammar.from_file(grammar_file_path)
    parser_algorithm = ParserAlgorithm(grammar, word)
    parser_algorithm.execute(output_file_path)


if __name__ == "__main__":
    main()
