#pragma once

#include <string>
#include <vector>
#include <cinttypes>
#include <memory>
#include <ostream>
#include <utility>
#include <cstring>
#include <array>
#include <functional>

namespace gameanalytics
{
    /*!
     @enum
     @discussion
     This enum is used to specify flow in resource events
     @constant GAResourceFlowTypeSource
     Used when adding to a resource currency
     @constant GAResourceFlowTypeSink
     Used when subtracting from a resource currency
     */
    enum EGAResourceFlowType
    {
        Source = 1,
        Sink = 2
    };

    /*!
     @enum
     @discussion
     this enum is used to specify status for progression event
     @constant GAProgressionStatusStart
     User started progression
     @constant GAProgressionStatusComplete
     User succesfully ended a progression
     @constant GAProgressionStatusFail
     User failed a progression
     */
    enum EGAProgressionStatus
    {
        Start = 1,
        Complete = 2,
        Fail = 3
    };

    /*!
     @enum
     @discussion
     this enum is used to specify severity of an error event
     @constant GAErrorSeverityDebug
     @constant GAErrorSeverityInfo
     @constant GAErrorSeverityWarning
     @constant GAErrorSeverityError
     @constant GAErrorSeverityCritical
     */
    enum EGAErrorSeverity
    {
        Debug       = 1,
        Info        = 2,
        Warning     = 3,
        Error       = 4,
        Critical    = 5
    };

    enum EGALoggerMessageType
    {
        LogError    = 0,
        LogWarning  = 1,
        LogInfo     = 2,
        LogDebug    = 3,
        LogVerbose  = 4
    };

    using StringVector = std::vector<std::string>;

    using LogHandler = std::function<void(std::string const&, EGALoggerMessageType)>;
    using FPSTracker = std::function<float()>;

    struct IRemoteConfigsListener
    {
        virtual void onRemoteConfigsUpdated(std::string const& remoteConfigs) = 0;
    };
}
