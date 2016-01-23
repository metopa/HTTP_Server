//
// Created by metopa on 4/22/15.
//

#ifndef HTTP_SERVER_EXCEPTIONS_H
#define HTTP_SERVER_EXCEPTIONS_H

#include "exceptions/network/socket/PortInitializationException.h"
#include "exceptions/network/socket/SocketReceiverException.h"
#include "exceptions/network/socket/SocketSenderException.h"

#include "exceptions/startup/ini_file/INIParserException.h"
#include "exceptions/startup/ini_file/ParamUndefinedException.h"
#include "exceptions/startup/ini_file/BlockUndefinedException.h"

#include "exceptions/filesystem/FileNotFoundException.h"
#include "exceptions/filesystem/FileErrorException.h"
#include "exceptions/filesystem/FilesystemException.h"
#include "exceptions/filesystem/InternalErrorException.h"
#include "exceptions/filesystem/PermissionDeniedException.h"

#include "exceptions/request/MethodProhibitedException.h"
#include "exceptions/request/RequestParserException.h"
#include "exceptions/request/ServiceUnavailableException.h"
#include "exceptions/request/EmptyDataException.h"

#endif //HTTP_SERVER_EXCEPTIONS_H
