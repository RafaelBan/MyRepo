#ifndef RBLEXCEPTION_H
#define RBLEXCEPTION_H

#include <exception>
#include <string>


namespace rbl
{

    class UnknownException : public std::exception
    {
    private:
        std::string message;

    protected:
        UnknownException(std::string mainInfo, std::string optionalInfo);

    public:
        UnknownException(std::string optionalInfo = "") :
            UnknownException("Unknown exception.\n", optionalInfo)
        {
        }

        virtual const char *
        what() const noexcept;
    };

    class EndIteratorRead : public UnknownException
    {
    public:
        EndIteratorRead(std::string optionalInfo = "") :
            UnknownException("Reading of end iterator.", optionalInfo)
        {}
    };

    class IteratorOutOfRange : public UnknownException
    {
    public:
        IteratorOutOfRange(std::string optionalInfo = "") :
            UnknownException("Iterator out of range.", optionalInfo)
        {}
    };

    class StrangeIterator : public UnknownException
    {
    public:
        StrangeIterator(std::string optionalInfo = "") :
            UnknownException("Processing of strange origin iterator.", optionalInfo)
        {}
    };
}

#endif // RBLEXCEPTION_H
