#pragma once

#include <exception>

class RepositoryException : public std::exception {
public:
    const char* what() const throw() override;
    RepositoryException();
    ~RepositoryException() override;
};

class TutorialAlreadyExists : public std::exception {
public:
    const char* what() const throw() override;
    TutorialAlreadyExists();
    ~TutorialAlreadyExists() override;
};

class IntegerError : public std::exception {
public:
    const char* what() const throw() override;
    IntegerError();
    ~IntegerError() override;
};

class LengthIsZero : public std::exception {
public:
    const char* what() const throw() override;
    LengthIsZero();
    ~LengthIsZero() override;
};
