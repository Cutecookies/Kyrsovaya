#include "errorhandler.h"
#include <QMessageBox>

void ErrorHandler::handle(ErrorType type, const QString& details) {
    QString message = errorMessage(type);
    if (!details.isEmpty()) {
        message += "\nDetails: " + details;
    }

    QMessageBox::critical(nullptr, "Error", message);
}

QString ErrorHandler::errorMessage(ErrorType type) {
    switch (type) {
    case ADDRESS_ERROR: return "Invalid address format";
    case NETWORK_ERROR: return "Network connection error";
    case ROUTE_NOT_FOUND: return "No routes found";
    case API_ERROR: return "API service error";
    default: return "Unknown error";
    }
}
