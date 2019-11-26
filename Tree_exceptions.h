#ifndef TREE_EXCEPTIONS_H
#define TREE_EXCEPTIONS_H
#include <stdexcept>

struct NullNode : public std::invalid_argument {
    NullNode() : invalid_argument(
        "Parametro nodo nullo.") {};
};

struct LastSibling : public std::domain_error {
    LastSibling() : domain_error(
        "Nodo è l'ultimo fratello.'") {};
};

struct FullSize : public std::invalid_argument {
    FullSize() : invalid_argument(
        "Dimensione massima raggiunta.") {};
};

struct RootExists : public std::domain_error {
    RootExists() : domain_error(
        "Radice gia presente.") {};
};

struct EmptyTree : public std::domain_error {
    EmptyTree() : domain_error(
        "Albero vuoto.") {};
};

struct NodeExists : public std::domain_error {
    NodeExists() : domain_error(
        "Nodo gia presente.") {};
};

struct NodeNotExists : public std::domain_error {
    NodeNotExists() : domain_error(
        "Nodo non presente.") {};
};
#endif
