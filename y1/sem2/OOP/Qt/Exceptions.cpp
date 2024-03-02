#include "Exceptions.h"



const char* RepositoryException::what() const throw()
{
    return "problem here";
}

RepositoryException::RepositoryException() {}
RepositoryException::~RepositoryException() {}


const char* IntegerError::what() const throw()
{
    return "problem here";
}

IntegerError::IntegerError() {}

IntegerError::~IntegerError() {}

const char* TutorialAlreadyExists::what() const throw() {
    return "Tutorial already exists.";
}

TutorialAlreadyExists::TutorialAlreadyExists() {}

TutorialAlreadyExists::~TutorialAlreadyExists() {}

const char* LengthIsZero::what() const throw() {
    return "The length is zero.";
}

LengthIsZero::~LengthIsZero() {}

LengthIsZero::LengthIsZero() {}