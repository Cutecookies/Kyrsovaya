#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QString>

class ErrorHandler {
public:
    enum ErrorType {
        ADDRESS_ERROR,
        NETWORK_ERROR,
        ROUTE_NOT_FOUND,
        API_ERROR
    };

    static void handle(ErrorType type, const QString& details = "");
    static QString errorMessage(ErrorType type);
};

#endif // ERRORHANDLER_H
